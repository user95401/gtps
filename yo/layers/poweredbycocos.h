#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace gd;

class poweredbycocos : public CCLayer {
protected:
    virtual bool init();
    virtual void keyDown(enumKeyCodes key);
    void switchOut(CCObject*);
    void fastSwitchOut(CCObject*);
public:
    static poweredbycocos* create();
};