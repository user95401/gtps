#include "RandomMeme.hpp"
#include "mod_utils.hpp"
#include "jute.h"

RandomMeme* RandomMeme::create() {
    auto ret = new RandomMeme();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void RandomMeme::switchOut(CCObject* sender) {
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.01f, MenuLayer::scene(0)));
};

void RandomMeme::fastSwitchOut(CCObject* sender) {
    if (!this->isRunning()) return;
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.01f, MenuLayer::scene(0)));
};

void RandomMeme::keyDown(enumKeyCodes key) {
    this->fastSwitchOut(CCNode::create());
}

bool RandomMeme::init() {
    this->setKeyboardEnabled(true);
    this->setTouchEnabled(true);
    CCMenu* m_pButtonMenu = CCMenu::create();
    this->addChild(m_pButtonMenu);
    CCMenuItem* MenuItem = CCMenuItem::create(this, menu_selector(RandomMeme::fastSwitchOut));
    MenuItem->setContentSize({ 9999,9999 });
    m_pButtonMenu->addChild(MenuItem);
    std::remove("gtps/Resources/UserContent/.RandomMemeJsn");
    std::remove("gtps/Resources/UserContent/.RandomMeme");
    if (S_OK == URLDownloadToFile(NULL, "http://meme-api.com/gimme", "gtps/Resources/UserContent/.RandomMemeJsn", 0, NULL))
    {   
        std::ifstream file("gtps/Resources/UserContent/.RandomMemeJsn");
        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        if (S_OK == URLDownloadToFile(NULL, (jute::parser::parse(content)["url"].as_string()).c_str(), "gtps/Resources/UserContent/.RandomMeme", 0, NULL))
        {
            std::remove("gtps/Resources/UserContent/.RandomMemeJsn");
            CCTextureCache::sharedTextureCache()->reloadTexture(".RandomMeme");
            CCSprite* RandomMeme = ModUtils::createSprite(".RandomMeme");
            RandomMeme->setAnchorPoint(CCPoint());
            RandomMeme->setScaleX(CCDirector::sharedDirector()->getWinSize().width / RandomMeme->getContentSize().width);
            RandomMeme->setScaleY(CCDirector::sharedDirector()->getWinSize().height / RandomMeme->getContentSize().height);
            addChild(RandomMeme, 0, 57281);
            runAction(CCSequence::create(CCDelayTime::create(3.0f), CCCallFuncO::create(this, callfuncO_selector(RandomMeme::switchOut), this), nullptr));
        }
        else {
            CCLabelTTF* imageDownloadFail = CCLabelTTF::create(("Failed download image from \"" + jute::parser::parse(content)["url"].as_string() + "\"").c_str(), "Comic Sans MS", 12.f);
            imageDownloadFail->setPosition(CCMenu::create()->getPosition());
            addChild(imageDownloadFail);
        }
    }
    else {
        CCLabelTTF* jsonDownloadFail = CCLabelTTF::create(("Failed download json from http://meme-api.com/gimme"), "Comic Sans MS", 12.f);
        jsonDownloadFail->setPosition(CCMenu::create()->getPosition());
        addChild(jsonDownloadFail);
    }
    return true;
}