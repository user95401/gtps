#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace gd;

class user666 : public CCLayer {
protected:
    virtual bool init();
    virtual void keyDown(enumKeyCodes key);
    void switchOut(CCObject*);
public:
    static user666* create();
};