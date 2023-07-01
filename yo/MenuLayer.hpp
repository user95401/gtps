#pragma once
#include "hooks.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class MenuLayerMod : MenuLayer {
public:
    inline CCLabelBMFont static* versionLabel;
    const char static* version;
    const char static* versionsUrl;
    const char static* upadateInfoUrl;
    void versionsLink(cocos2d::CCObject*);
    void onUpdateHttpResponse(CCHttpClient*, CCHttpResponse*);
};

void MenuLayerHook();
