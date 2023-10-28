#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

namespace CustomBackgroundFeature {
    static LevelInfoLayer* LevelInfoLayerItself;
};

class CustomBackground {
public:
    inline static CCLayer* toAdd;
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response);
    static void setTargetLayer(CCLayer* layer);
};

class CustomBackgroundPopup : public FLAlertLayer {
public:
    static CustomBackgroundPopup* create();
    virtual bool init();
    virtual void keyBackClicked();
    void createAndShowMe(CCObject*);
    void onBtn1(CCObject*);
    void onBtn2(CCObject*);
};