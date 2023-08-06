#include "cocosHooks.hpp"

CCSprite* CCSprite_create_H(const char* name) {
    if (strstr(std::string(name).c_str(), "cx1_14")) {//blankSprite
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name,"CCSprite_createHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    return CCSprite_create(name);
}

CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    if (strstr(std::string(name).c_str(), "cx1_14")) {//blankSprite
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name, "CCSprite_createWithSpriteFrameNameHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (std::string(name) == "robtoplogo_small.png") {
        CCLabelBMFont* user666s_original = CCLabelBMFont::create("user666's\noriginal", "chatFont.fnt");
        user666s_original->setAlignment(kCCTextAlignmentCenter);

        CCSprite* blankSprite = CCSprite::create();
        blankSprite->addChild(user666s_original);
        return blankSprite;
    }
    if (std::string(name) == "RobTopLogoBig_001.png") {
        CCLabelBMFont* user666s_originalBig = CCLabelBMFont::create("user666's original", "gjFont06.fnt");

        CCSprite* blankSprite = CCSprite::create();
        blankSprite->addChild(user666s_originalBig);
        return blankSprite;
    }
    return CCSprite_createWithSpriteFrameName(name);
}

CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    if (std::string(str) == "no" || strstr(std::string(str).c_str(), "cx1_14")) {
        CCLabelBMFont* lbl = CCLabelBMFont::create("", "gjFont01.fnt");
        lbl->setVisible(false);
        lbl->setAnchorPoint({ -999.0f,-999.0f });
        //MessageBoxA(nullptr, str, "CCLabelBMFont_createHook -> no lbl", MB_ICONINFORMATION | MB_OK);
        return lbl;
    }
    return CCLabelBMFont_create(str, fntFile);
}