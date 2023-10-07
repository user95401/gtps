﻿#include "cocosHooks.hpp"
#include "SimpleIni.h"

CCSprite* CCSprite_create_H(const char* name) {
    if (strstr(std::string(name).c_str(), "cx1_14") || HideEverySprite) {//blankSprite
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name,"CCSprite_createHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (std::string(name) == "GJ_gradientBG.png" && !GameManager::sharedState()->getGameVariable("57862")) {
        CCSprite* randomBackGround = ModUtils::createSprite(ModUtils::getRandomFileNameFromDir("gtps/Resources/randomBackGrounds", name).c_str());
        randomBackGround->runAction(CCRepeatForever::create(CCTintTo::create(0.1f, 255, 255, 255)));
        return randomBackGround;
    }
    return CCSprite_create(name);
}

CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    if (strstr(std::string(name).c_str(), "cx1_14") || std::string(name) == HideEveryFrameByName.c_str() || HideEveryFrame == true) {//blankSprite
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name, "CCSprite_createWithSpriteFrameNameHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (ReplaceAllFramesByName::by != "" && ReplaceAllFramesByName::by == std::string(name)) name = ReplaceAllFramesByName::to.c_str();
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
    if (std::string(name) == "GJ_logo_001.png") {
        CCSprite* GJ_logo_001 = CCSprite::create(name);
        GJ_logo_001->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCScaleBy::create(1.0, 1.025)), CCEaseSineInOut::create(CCScaleBy::create(1.0, 0.975)), nullptr)));
        return GJ_logo_001;
    }
    //custom sprite process
    CSimpleIniA sprites_list;
    sprites_list.LoadFile("gtps/sprites_list.ini");
    if (sprites_list.GetSection(name)) {
        //sprite getting
        if (sprites_list.GetValue(name, "name"))
            name = sprites_list.GetValue(name, "name");
        CCSprite* sprite = CCSprite_create_H(name);
        //custom setup
        if (sprites_list.GetValue(name, "setAnchorPointX"))
            sprite->setAnchorPoint({ std::stof(sprites_list.GetValue(name, "setAnchorPointX")), sprite->getAnchorPoint().y });
        if (sprites_list.GetValue(name, "setAnchorPointY"))
            sprite->setAnchorPoint({ sprite->getAnchorPoint().x, std::stof(sprites_list.GetValue(name, "setAnchorPointY")) });
        if (sprites_list.GetValue(name, "setScale"))
            sprite->setScale(std::stof(sprites_list.GetValue(name, "setScale")));
        if (sprites_list.GetValue(name, "setScaleX"))
            sprite->setScaleX(std::stof(sprites_list.GetValue(name, "setScaleX")));
        if (sprites_list.GetValue(name, "setScaleY"))
            sprite->setScaleY(std::stof(sprites_list.GetValue(name, "setScaleY")));
        if (sprites_list.GetValue(name, "setFlipX"))
            sprite->setFlipX(sprites_list.GetBoolValue(name, "setFlipX"));
        if (sprites_list.GetValue(name, "setFlipY"))
            sprite->setFlipY(sprites_list.GetBoolValue(name, "setFlipY"));
        if (sprites_list.GetValue(name, "setOpacity"))
            sprite->setOpacity(std::stoi(sprites_list.GetValue(name, "setOpacity")));
        if (sprites_list.GetValue(name, "setRotation"))
            sprite->setRotation(std::stof(sprites_list.GetValue(name, "setRotation")));
        return sprite;
    }
    //custom frame process
    CSimpleIniA frames_list;
    frames_list.LoadFile("gtps/frames_list.ini");
    if (frames_list.GetSection(name)) {
        //sprite getting
        if (frames_list.GetValue(name, "name"))
            name = frames_list.GetValue(name, "name");
        CCSprite* frame = CCSprite::createWithSpriteFrameName(name);
        //custom setup
        if (frames_list.GetValue(name, "setAnchorPointX"))
            frame->setAnchorPoint({ std::stof(frames_list.GetValue(name, "setAnchorPointX")), frame->getAnchorPoint().y });
        if (frames_list.GetValue(name, "setAnchorPointY"))
            frame->setAnchorPoint({ frame->getAnchorPoint().x, std::stof(frames_list.GetValue(name, "setAnchorPointY")) });
        if (frames_list.GetValue(name, "setScale"))
            frame->setScale(std::stof(frames_list.GetValue(name, "setScale")));
        if (frames_list.GetValue(name, "setScaleX"))
            frame->setScaleX(std::stof(frames_list.GetValue(name, "setScaleX")));
        if (frames_list.GetValue(name, "setScaleY"))
            frame->setScaleY(std::stof(frames_list.GetValue(name, "setScaleY")));
        if (frames_list.GetValue(name, "setFlipX"))
            frame->setFlipX(frames_list.GetBoolValue(name, "setFlipX"));
        if (frames_list.GetValue(name, "setFlipY"))
            frame->setFlipY(frames_list.GetBoolValue(name, "setFlipY"));
        if (frames_list.GetValue(name, "setOpacity"))
            frame->setOpacity(std::stoi(frames_list.GetValue(name, "setOpacity")));
        if (frames_list.GetValue(name, "setRotation"))
            frame->setRotation(std::stof(frames_list.GetValue(name, "setRotation")));
        return frame;
    }
    return CCSprite_createWithSpriteFrameName(name);
}

CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    //settings
    if ("settings") {
        if (std::string(str) == "uwuifier must be loaded...")
            LoadLibraryA("gtps\\libs\\uwuifier.dll");
        if (std::string(str) == "Settings for gtps") {
            MoreOptionsLayer* _ModOptionsLayer = MoreOptionsLayer::create();
            _ModOptionsLayer->m_bNoElasticity = true;
            _ModOptionsLayer->show();
        }
        //config ini
        if (
            bool((std::string(str) == "sprites_list.ini") || 
                (std::string(str) == "rand_sounds_list.ini") || 
                (std::string(str) == "frames_list.ini"))
            &&
            std::string(fntFile) == "bigFont.fnt"
            ) {
            ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
            ReplaceAllFramesByName::to = "geode.loader/pencil.png";
        }
        if (std::string(str) == "open up sprites_list.ini")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("sprites_list.ini", 0).c_str()), NULL, NULL, 1);
        if (std::string(str) == "open up frames_list.ini")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("frames_list.ini", 0).c_str()), NULL, NULL, 1);
        if (std::string(str) == "open up rand_sounds_list.ini")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("rand_sounds_list.ini", 0).c_str()), NULL, NULL, 1);
        //config folders
        if (
            bool((std::string(str) == "randomBackGrounds ") ||
                (std::string(str) == "explodes ") ||
                (std::string(str) == "menuLoops ") ||
                (std::string(str) == "quitSounds "))
            &&
            std::string(fntFile) == "bigFont.fnt"
            ) {
            ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
            ReplaceAllFramesByName::to = "gj_folderBtn_001.png";
        }
        if (std::string(str) == "open up randomBackGrounds")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps/Resources/randomBackGrounds", 0).c_str()), NULL, NULL, 1);
        if (std::string(str) == "open up quitSound")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps/Resources/sounds/quitSound", 0).c_str()), NULL, NULL, 1);
        if (std::string(str) == "open up explode")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps/Resources/sounds/explode", 0).c_str()), NULL, NULL, 1);
        if (std::string(str) == "open up menuLoop")
            ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps/Resources/sounds/menuLoop", 0).c_str()), NULL, NULL, 1);
        if (
            bool(ReplaceAllFramesByName::to == "gj_folderBtn_001.png" && ReplaceAllFramesByName::by == "GJ_infoIcon_001.png")
            &&
            std::string(str) == "                    "
            &&
            std::string(fntFile) == "bigFont.fnt"
            )
        {
            ReplaceAllFramesByName::by = "";
            ReplaceAllFramesByName::to == "";
        }

    }
    if (strstr(std::string(str).c_str(), "cx1_14") || HideEveryLabel) {
        CCLabelBMFont* lbl = CCLabelBMFont::create("", "gjFont01.fnt");
        lbl->setVisible(false);
        lbl->setAnchorPoint({ -999.0f,-999.0f });
        //MessageBoxA(nullptr, str, "CCLabelBMFont_createHook -> no lbl", MB_ICONINFORMATION | MB_OK);
        return lbl;
    }
    if (std::string(str) == "of modification 950df1") {
        str = "of modification";
        CCLabelBMFont* lbl = CCLabelBMFont::create(str, fntFile);
        CCPoint point = CCPoint();
        point.x = (CCDirector::sharedDirector()->getScreenRight() / 2) - (lbl->getContentSize().width / 2) / 2;
        point.y = CCDirector::sharedDirector()->getScreenTop() - 53;
        lbl->runAction(CCRepeatForever::create(CCMoveTo::create(0.0, point)));
        return lbl;
    }
    return CCLabelBMFont_create(str, fntFile);
}