#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class CustomObjectsTextureFeature {
public:
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response);
};

class CustomObjectsTextureFeaturePopup : public FLAlertLayer {
public:
    static CustomObjectsTextureFeaturePopup* create();
    virtual bool init();
    virtual void keyBackClicked();
    void createAndShowMe(CCObject*);
    void onBtn1(CCObject*);
    void onBtn2(CCObject*);
};