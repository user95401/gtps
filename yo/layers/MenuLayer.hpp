#pragma once
#include "hooks.hpp"
#include "mod_utils.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class MenuLayerExt : public MenuLayer {
public:
    inline static MenuLayerExt* me;
    inline static bool dontAlertVerAgain;
    inline CCLabelBMFont static* versionLabel;
    const char static* version;
    const char static* versionsUrl;
    const char static* upadateInfoUrl;
    const char static* onFacebook;
    const char static* onTwitter;
    const char static* onYouTube;
    void versionsLink(cocos2d::CCObject*);
    void onUpdateHttpResponse(CCHttpClient*, CCHttpResponse*);
    void hideContent(cocos2d::CCObject*);
    void resetSong(cocos2d::CCObject*);
};

void CreateMenuLayerHooks();
