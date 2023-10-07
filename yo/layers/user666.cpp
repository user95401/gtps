#include "user666.h"
#include "mod_utils.hpp"

using namespace gd;
using namespace cocos2d;

user666* user666::create() {
    auto ret = new user666();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void user666::switchOut(CCObject* sender) {
    if (!this->isRunning()) return;
    GameSoundManager::sharedState()->stopBackgroundMusic();
    auto transition = CCTransitionFade::create(0.01f, MenuLayer::scene(false));
    CCDirector::sharedDirector()->pushScene(transition);
}

void user666::keyDown(enumKeyCodes key) {
    this->switchOut(CCNode::create());
}

bool user666::init() {
    this->setKeyboardEnabled(true);
    this->setTouchEnabled(true);
    CCMenu* m_pButtonMenu = CCMenu::create();
    this->addChild(m_pButtonMenu);
    CCMenuItem* MenuItem = CCMenuItem::create(this, menu_selector(user666::switchOut));
    MenuItem->setContentSize({ 9999,9999 });
    m_pButtonMenu->addChild(MenuItem);

    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("user666.plist", "user666.png");
    CCSprite* sprite = ModUtils::createSprite("user666_frame_0.png");
    CCArray* animFrames = CCArray::createWithCapacity(10);
    char str[164] = { 0 };
    for (int i = 0; i < 164; ++i) {
        sprintf(str, "user666_frame_%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.031f);
    sprite->runAction(CCAnimate::create(animation));

    //sprite->setAnchorPoint(CCPoint());
    //sprite->setScaleX(CCDirector::sharedDirector()->getWinSize().width / sprite->getContentSize().width);
    sprite->setScale({ CCDirector::sharedDirector()->getWinSize().width / sprite->getContentSize().width });
    sprite->setPosition(ModUtils::getCenterPoint());
    addChild(sprite, 0, 57281);

    runAction(CCSequence::create(CCDelayTime::create(3.8f), CCCallFuncO::create(sprite, callfuncO_selector(user666::switchOut), sprite), nullptr));
    GameSoundManager::sharedState()->stopBackgroundMusic();
    GameManager::sharedState()->fadeInMusic("user666.mp3");
    return true;
}