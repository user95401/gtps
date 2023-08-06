#include "MenuLayer.hpp"
bool seenWarn = false;
void MenuLayerMod::versionsLink(cocos2d::CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(versionsUrl);
}
void MenuLayerMod::onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
    std::vector<char>* responseData = response->getResponseData();
    std::string responseString(responseData->begin(), responseData->end());
    if (responseString != "") versionLabel->setColor({ 255, 255, 255 });
    if (responseString != version) {
        AchievementNotifier::sharedState()->notifyAchievement("Update available!", ("You can download new " + responseString + " version on the website.").c_str(), "GJ_downloadsIcon_001.png", true);
        versionLabel->setColor({ 255, 60, 60 });
        versionLabel->runAction(CCRepeatForever::create(CCSequence::create(
            CCEaseSineIn::create(CCScaleTo::create(0.3, versionLabel->getScale() + 0.1)),
            CCEaseBounceOut::create(CCScaleTo::create(0.5, versionLabel->getScale())),
            CCDelayTime::create(1.0),
            nullptr)));
        CCMenuItem* versionItem = CCMenuItem::create(versionLabel, menu_selector(MenuLayerMod::versionsLink));
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

inline MenuLayer* (__cdecl* MenuLayer_init)(MenuLayer*);
bool __fastcall MenuLayer_init_H(MenuLayer* self) {
    if (!MenuLayer_init(self)) return false;
    MenuLayerMod::versionLabel = CCLabelBMFont::create(MenuLayerMod::version, "chatFont.fnt");
    MenuLayerMod::versionLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width, 0 });
    MenuLayerMod::versionLabel->setAnchorPoint({ 1.1f, 0 });
    MenuLayerMod::versionLabel->setScale({ 0.6f });
    MenuLayerMod::versionLabel->setColor({ 0, 0, 0 });
    MenuLayerMod::versionLabel->setOpacity({ 110 });
    MenuLayerMod::versionLabel->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(3, 180), CCFadeTo::create(3, 110), nullptr)));
    self->addChild(MenuLayerMod::versionLabel);

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setUrl(MenuLayerMod::upadateInfoUrl);
    request->setResponseCallback(self, httpresponse_selector(MenuLayerMod::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();

    CCNode* centerNode = CCNode::create();
    centerNode->setPosition(CCMenu::create()->getPosition());
    self->addChild(centerNode);

    auto warnlbl = CCLabelTTF::create("This game contains flash lights, loud noises and jumpscares.\n Also its buggy shit. Have a good game, man, thanks for playin <3", 
        "Comic Sans MS", 10);
    warnlbl->setPositionY(-60.f);
    warnlbl->runAction(CCSequence::create(CCDelayTime::create(3.0), CCFadeOut::create(0.5), nullptr));
    if (!seenWarn) { seenWarn = true; centerNode->addChild(warnlbl); }

    return true;
}

inline MenuLayer* (__cdecl* MenuLayer_onFacebook)(MenuLayer*, void*, CCObject*);
void __fastcall MenuLayer_onFacebook_H(MenuLayer* self, void*, CCObject* pSender) { 
    CCApplication::sharedApplication()->openURL(MenuLayerMod::onFacebook);
}
inline MenuLayer* (__cdecl* MenuLayer_onTwitter)(MenuLayer*, void*, CCObject*);
void __fastcall MenuLayer_onTwitter_H(MenuLayer* self, void*, CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(MenuLayerMod::onTwitter);
}
inline MenuLayer* (__cdecl* MenuLayer_onYouTube)(MenuLayer*, void*, CCObject*);
void __fastcall MenuLayer_onYouTube_H(MenuLayer* self, void*, CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(MenuLayerMod::onYouTube);
}

void MenuLayerHook() {
    HOOK(base + 0x1907B0, MenuLayer_init, false);
    HOOK(base + 0x191960, MenuLayer_onFacebook, true);
    HOOK(base + 0x191980, MenuLayer_onTwitter, true);
    HOOK(base + 0x1919A0, MenuLayer_onYouTube, true);
}