#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class RandomMeme : public CCLayer {
protected:
    virtual bool init();
    virtual void keyDown(enumKeyCodes key);
public:
    static RandomMeme* create();
    void switchOut(CCObject*);
    void fastSwitchOut(CCObject*);
    void onMemeGimmeHttpResponse(CCHttpClient* client, CCHttpResponse* response);
};