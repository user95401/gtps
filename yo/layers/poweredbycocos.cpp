#include "poweredbycocos.h"
#include "user666.h"
#include "mod_utils.hpp"

using namespace gd;
using namespace cocos2d;

poweredbycocos* poweredbycocos::create() {
    auto ret = new poweredbycocos();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void poweredbycocos::switchOut(CCObject* sender) {
    auto scene = CCScene::create();
    scene->addChild(user666::create());
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
};

void poweredbycocos::fastSwitchOut(CCObject* sender) {
    if (!this->isRunning()) return;
    auto scene = CCScene::create();
    scene->addChild(user666::create());
    auto transition = CCTransitionFade::create(0.01f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
};

void poweredbycocos::keyDown(enumKeyCodes key) {
    this->fastSwitchOut(CCNode::create());
}

bool poweredbycocos::init() {
    this->setKeyboardEnabled(true);
    this->setTouchEnabled(true);
    CCMenu* m_pButtonMenu = CCMenu::create();
    this->addChild(m_pButtonMenu);
    CCMenuItem* MenuItem = CCMenuItem::create(this, menu_selector(poweredbycocos::fastSwitchOut));
    MenuItem->setContentSize({ 9999,9999 });
    m_pButtonMenu->addChild(MenuItem);

    GameManager::sharedState()->fadeInMusic("fnbvjksd.lsd");
    CCSprite* randomBackGround = ModUtils::createSprite("cocos2dx.jpg");
    randomBackGround->setAnchorPoint(CCPoint());
    randomBackGround->setScaleX(CCDirector::sharedDirector()->getWinSize().width / randomBackGround->getContentSize().width);
    randomBackGround->setScaleY(CCDirector::sharedDirector()->getWinSize().height / randomBackGround->getContentSize().height);
    addChild(randomBackGround, 0, 57281);
    runAction(CCSequence::create(CCDelayTime::create(1.5f), CCCallFuncO::create(randomBackGround, callfuncO_selector(poweredbycocos::switchOut), randomBackGround), nullptr));
    return true;
}