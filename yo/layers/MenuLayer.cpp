#include "MenuLayer.hpp"
bool seenWarn = false;
int kills;
CCLabelTTF* killsLbl;
void MenuLayerExt::hideContent(cocos2d::CCObject* pSender) {
    for (int i = 0; i < me->getChildrenCount(); ++i) {
        if (i != 0) {
            /*me->removeChild*/(reinterpret_cast<CCNode*>(me->getChildren()->objectAtIndex(i)))->runAction(CCEaseExponentialIn::create(CCMoveBy::create(0.5, { 1000.f + (i * 500.f), 0 })));
            if (reinterpret_cast<CCNode*>(me->getChildren()->objectAtIndex(1))->getPositionX() > 500) me->removeChild(reinterpret_cast<CCNode*>(me->getChildren()->objectAtIndex(i)));
        }
    }
    CCMenu* Menu = CCMenu::create();
    Menu->setPosition(CCPoint());
    me->addChild(Menu);
    //resetBtn
    auto resetBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_backBtn_001.png"), me, menu_selector(CreatorLayer::onBack));
    resetBtn->setPosition({ -0.f,-100.f });
    resetBtn->runAction(CCEaseExponentialInOut::create(CCMoveTo::create(1.0, CCPoint(32.f, 32.f))));
    Menu->addChild(resetBtn, 5);
    //resetSongBtn
    auto resetSongBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_musicOnBtn_001.png"), me, menu_selector(MenuLayerExt::resetSong));
    resetSongBtn->setPosition({ -0.f,-100.f });
    resetSongBtn->runAction(CCEaseExponentialInOut::create(CCMoveTo::create(1.0, CCPoint(82.f, 32.f))));
    Menu->addChild(resetSongBtn, 5);
    //optionsBtn
    auto optionsBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_optionsBtn02_001.png"), me, menu_selector(MenuLayerExt::onOptions));
    optionsBtn->setPosition({ -0.f,-100.f });
    optionsBtn->runAction(CCEaseExponentialInOut::create(CCMoveTo::create(1.0, CCPoint(126.f, 32.f))));
    Menu->addChild(optionsBtn, 5);
    //kills
    kills = 0;
    killsLbl = CCLabelTTF::create("0x", "Comic Sans MS", 32.f);
    killsLbl->setAnchorPoint({ -0.3f, 1.f });
    killsLbl->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentLeft);
    killsLbl->setPosition({ -100.f, CCDirector::sharedDirector()->getScreenTop() });
    killsLbl->runAction(CCEaseExponentialInOut::create(CCMoveTo::create(1.0, CCPoint(0.f, CCDirector::sharedDirector()->getScreenTop()))));
    Menu->addChild(killsLbl, 5);
}
void MenuLayerExt::resetSong(cocos2d::CCObject* pSender) {
    GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
}
void MenuLayerExt::versionsLink(cocos2d::CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(versionsUrl);
}
void MenuLayerExt::onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
    dontAlertVerAgain = true;
    std::vector<char>* responseData = response->getResponseData();
    std::string responseString(responseData->begin(), responseData->end());
    if (responseString != "") versionLabel->setColor({ 255, 255, 255 });
    else if(dontAlertVerAgain != true) CCMessageBox("Response string from server is empty, \nmaybe something wrong with server or your device!", "Response from server is empty");
    if (responseString != version && responseString != "") {
        if (dontAlertVerAgain != true) AchievementNotifier::sharedState()->notifyAchievement("Update available!", ("You can download new " + responseString + " version on the website.").c_str(), "GJ_downloadsIcon_001.png", true);
        versionLabel->setColor({ 255, 60, 60 });
        versionLabel->runAction(CCRepeatForever::create(CCSequence::create(
            CCEaseSineIn::create(CCScaleTo::create(0.3f, versionLabel->getScale() + 0.1f)),
            CCEaseBounceOut::create(CCScaleTo::create(0.5f, versionLabel->getScale())),
            CCDelayTime::create(1.0),
            nullptr)));
        CCMenuItem* versionItem = CCMenuItem::create(versionLabel, menu_selector(MenuLayerExt::versionsLink));
        versionItem->setContentSize(versionLabel->getContentSize());
        versionItem->setAnchorPoint(versionLabel->getAnchorPoint());
        versionItem->setPosition(versionLabel->getPosition());
        versionItem->setScale(versionLabel->getScale());
        MenuLayer* MenuLayerSelf = (MenuLayer*)versionLabel->getParent();
        CCMenu* versionsLinkMenu = CCMenu::createWithItem(versionItem);
        versionsLinkMenu->setPosition({ 0,0 });
        MenuLayerSelf->addChild(versionsLinkMenu);
    }
}

inline MenuLayerExt* (__cdecl* MenuLayer_init)(MenuLayerExt*);
bool __fastcall MenuLayer_init_H(MenuLayerExt* self) {
    if (!MenuLayer_init(self)) return false;
    twoTimesLayerInitHookEscape(self);
    self->me = self;

    MenuLayerExt::versionLabel = CCLabelBMFont::create(MenuLayerExt::version, "chatFont.fnt");
    MenuLayerExt::versionLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width, 0 });
    MenuLayerExt::versionLabel->setAnchorPoint({ 1.1f, 0 });
    MenuLayerExt::versionLabel->setScale({ 0.6f });
    MenuLayerExt::versionLabel->setColor({ 0, 0, 0 });
    MenuLayerExt::versionLabel->setOpacity({ 110 });
    MenuLayerExt::versionLabel->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(3, 180), CCFadeTo::create(3, 110), nullptr)));
    self->addChild(MenuLayerExt::versionLabel);

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setUrl(MenuLayerExt::upadateInfoUrl);
    request->setResponseCallback(self, httpresponse_selector(MenuLayerExt::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();

    //Menu
    CCMenu* menu = CCMenu::create();//geode wtf reinterpret_cast<CCMenu*>(self->m_profileBtn->getParent());
    self->addChild(menu, reinterpret_cast<CCMenu*>(self->m_profileBtn->getParent())->getZOrder());
    //centerNode
    CCNode* centerNode = CCNode::create();
    centerNode->setPosition(CCMenu::create()->getPosition());
    self->addChild(centerNode);

    //hideContentBtn, killsLbl
    CCMenuItemSpriteExtra* hideContentBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_deleteAllIcon_001.png"), menu, menu_selector(MenuLayerExt::hideContent));
    hideContentBtn->setPositionY(-68.000);
    menu->addChild(hideContentBtn);
    killsLbl = CCLabelTTF::create();
    killsLbl->setAnchorPoint({ -110.3f, 111.f });
    self->addChild(killsLbl);

    //flyinamopgus!!!
    CCSprite* flyinAmogus = CCSprite::create("flyinAmogus.png");
    flyinAmogus->setPosition({ CCDirector::sharedDirector()->getScreenRight(), CCDirector::sharedDirector()->getScreenTop() });
    flyinAmogus->runAction(CCRepeatForever::create(CCRotateBy::create(0.1, 1)));
    if (rand() % 3 == 2) flyinAmogus->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));
    if (rand() % 3 == 1) flyinAmogus->setColor(GameManager::sharedState()->colorForIdx(rand() % 22));
    self->addChild(flyinAmogus);

    //warn lbl bg
    CCScale9Sprite* warnlblbg = CCScale9Sprite::create("square02_001.png");
    if (!seenWarn) { seenWarn = true; centerNode->addChild(warnlblbg); }
    warnlblbg->setPositionY(-68.f);
    warnlblbg->setOpacity(120);
    //warn lbl
    auto warnlbl = CCLabelTTF::create("Game may contain explicit lyrics and offensive jokes - don't take it seriously!\n Also its buggy shit. Have a good game, man, thanks for playin <3",
        "Comic Sans MS", 10.f);
    warnlbl->setScale(2.f);
    warnlbl->setAnchorPoint(CCPoint(-0.015f, -0.15f));
    //more bg setups when
    warnlblbg->setContentSize({ warnlbl->getContentSize().width * 2 + 30, warnlbl->getContentSize().height * 2 + 20 });
    warnlblbg->setScale(0.5f);
    warnlblbg->addChild(warnlbl);
    //fadeanim
    warnlblbg->runAction(CCSequence::create(CCDelayTime::create(10.0f), CCFadeTo::create(0.5f, 0), nullptr));
    warnlbl->runAction(CCSequence::create(CCDelayTime::create(10.0f), CCFadeTo::create(0.5f, 0), nullptr));

    return true;
}

inline MenuLayerExt* (__cdecl* MenuLayer_onFacebook)(void*, CCObject*);
void __fastcall MenuLayer_onFacebook_H(void*, CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(MenuLayerExt::onFacebook);
}
inline MenuLayerExt* (__cdecl* MenuLayer_onTwitter)(void*, CCObject*);
void __fastcall MenuLayer_onTwitter_H(void*, CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(MenuLayerExt::onTwitter);
}
inline MenuLayerExt* (__cdecl* MenuLayer_onYouTube)(void*, CCObject*);
void __fastcall MenuLayer_onYouTube_H(void*, CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(MenuLayerExt::onYouTube);
}

inline MenuGameLayer* (__cdecl* MenuGameLayer_destroyPlayer)(MenuGameLayer* self);//= win 0x190100;
void __fastcall MenuGameLayer_destroyPlayer_H(MenuGameLayer* self, void*) {
    MenuGameLayer_destroyPlayer(self);
    if (!killsLbl) return;
    killsLbl->runAction(CCSequence::create(
        CCScaleTo::create(0.03, 1.8),
        CCEaseExponentialOut::create(CCScaleTo::create(0.15, 1.0)),
        nullptr
    ));
    ++kills;
    killsLbl->setString((std::to_string(kills)+"x").c_str());
}

MenuGameLayer* (__thiscall* MenuGameLayer_create)();
CCLayer* __fastcall MenuGameLayer_create_H() {
    auto level = GameLevelManager::sharedState()->getMainLevel(rand() % 25, false);
    //level->m_sTempName = "isPreviewThing";
    level->m_sLevelName = "isPreviewThing6380";
    //"Always level MainMenu", "98549", "always show level instead deafult main menu bg"
    if (!GameManager::sharedState()->getGameVariable("52905") && (rand() % 3 == 2 || GameManager::sharedState()->getGameVariable("98549"))) return PlayLayer::create(level);
    else MenuGameLayer_create();
}

void CreateMenuLayerHooks() {
    HOOK(base + 0x1907B0, MenuLayer_init);
    HOOK(base + 0x191960, MenuLayer_onFacebook);
    HOOK(base + 0x191980, MenuLayer_onTwitter);
    HOOK(base + 0x1919A0, MenuLayer_onYouTube);

    HOOK(base + 0x190100, MenuGameLayer_destroyPlayer);
    HOOK(base + 0x18e6d0, MenuGameLayer_create);
}