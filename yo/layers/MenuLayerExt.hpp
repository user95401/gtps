#pragma once
#include "hooks.hpp"
#include "mod_utils.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

#include "SoundRelated.hpp"

class MenuLayerExt : public MenuLayer {
public:
    inline static MenuLayerExt* me;
    inline static bool dontAlertVerAgain;
    inline CCLabelBMFont static* versionLabel;
    CCSprite* checkNewVer;
    const char static* version;
    const char static* versionsUrl;
    const char static* upadateInfoUrl;
    const char static* onFacebook;
    const char static* onTwitter;
    const char static* onYouTube;
    void versionsLink(CCObject*);
    void onVersionCheckResponse(CCHttpClient*, CCHttpResponse*);
    void onProfileUpdateHttpResponse(CCHttpClient*, CCHttpResponse*);
    void hideContent(CCObject*);
    void resetSong(CCObject*);
    void onReload(CCObject*);
    static void CreateHooks();
};

