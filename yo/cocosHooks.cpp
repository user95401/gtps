#include "mod_utils.hpp"
#include "hooks.hpp"
#include "cocosHooks.hpp"
#include "SimpleIni.h"

using namespace cocosHooks;

CCSprite* (__cdecl* CCSprite_create)(const char*);
CCSprite* CCSprite_create_H(const char* name) {
    if (strstr(std::string(name).c_str(), "cx1_14") || HideEverySprite) {//blankSprite
        //MessageBoxA(nullptr, name,"CCSprite_createHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        CCSprite* no = CCSprite::create();
        return no;
    }
    if (std::string(name) == "GJ_gradientBG.png" && !GameManager::sharedState()->getGameVariable("57862")) {
        CCSprite* randomBackGround = ModUtils::createSprite(ModUtils::getRandomFileNameFromDir("gtps/Resources/randomBackGrounds", name).c_str());
        randomBackGround->runAction(CCRepeatForever::create(CCTintTo::create(0.1f, 255, 255, 255)));
        return randomBackGround;
    }
    return CCSprite_create(name);
}

CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char*);
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
        //user666s_original->setAnchorPoint(CCPoint());

        CCSprite* blankSprite = CCSprite::create();
        blankSprite->addChild(user666s_original);
        //blankSprite->setContentSize(user666s_original->getContentSize());
        return blankSprite;
    }
    if (std::string(name) == "RobTopLogoBig_001.png") {
        CCLabelBMFont* user666s_originalBig = CCLabelBMFont::create("user666's original", "gjFont06.fnt");
        user666s_originalBig->setAlignment(kCCTextAlignmentCenter);
        user666s_originalBig->setAnchorPoint(CCPoint());

        CCSprite* blankSprite = CCSprite::create();
        blankSprite->addChild(user666s_originalBig);
        blankSprite->setContentSize(user666s_originalBig->getContentSize());
        return blankSprite;
    }
    if (std::string(name) == "GJ_logo_001.png") {
        CCSprite* GJ_logo_001 = ModUtils::createSprite("GTPS_logo_001.png", 4.0f);
        GJ_logo_001->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCScaleBy::create(1.0, 1.025)), CCEaseSineInOut::create(CCScaleBy::create(1.0, 0.975)), nullptr)));
        CCSprite* GJ_logo_002 = ModUtils::createSprite("GTPS_logo_002.png", 4.0f);
        GJ_logo_002->setColor(GameManager::sharedState()->colorForIdx(rand() % 18));
        GJ_logo_002->setAnchorPoint(CCPointZero);
        GJ_logo_002->setBlendFunc({ GL_ONE, GL_ONE });
        if(GameManager::sharedState()->getGameVariable("89953")) GJ_logo_002->runAction(ModUtils::CreateRGB(3.0f));
        GJ_logo_001->addChild(GJ_logo_002);
        return GJ_logo_001;
    }
    //custom sprite process
    CSimpleIniA sprites_list;
    sprites_list.LoadFile("gtps/sprites_list.ini");
    if (sprites_list.GetSection(name)) {
        CCTextureCache::sharedTextureCache()->reloadTexture(name);
        //sprite getting
        if (sprites_list.GetValue(name, "name"))
            name = sprites_list.GetValue(name, "name");
        CCSprite* sprite = CCSprite_create_H(name);
        //custom setup
        if (sprites_list.GetValue(name, "setAnchorPointX"))
            sprite->setAnchorPoint({ std::stof(sprites_list.GetValue(name, "setAnchorPointX")), sprite->getAnchorPoint().y });
        if (sprites_list.GetValue(name, "setAnchorPointY"))
            sprite->setAnchorPoint({ sprite->getAnchorPoint().x, std::stof(sprites_list.GetValue(name, "setAnchorPointY")) });
        if (sprites_list.GetValue(name, "setScaleAction"))
            sprite->runAction(CCRepeatForever::create(CCScaleTo::create(0.f, std::stof(sprites_list.GetValue(name, "setScale")))));
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
        CCTextureCache::sharedTextureCache()->reloadTexture(name);
        //sprite getting
        if (frames_list.GetValue(name, "name"))
            name = frames_list.GetValue(name, "name");
        CCSprite* frame = CCSprite::createWithSpriteFrameName(name);
        //custom setup
        if (frames_list.GetValue(name, "setAnchorPointX"))
            frame->setAnchorPoint({ std::stof(frames_list.GetValue(name, "setAnchorPointX")), frame->getAnchorPoint().y });
        if (frames_list.GetValue(name, "setAnchorPointY"))
            frame->setAnchorPoint({ frame->getAnchorPoint().x, std::stof(frames_list.GetValue(name, "setAnchorPointY")) });
        if (frames_list.GetValue(name, "setScaleAction"))
            frame->runAction(CCRepeatForever::create(CCScaleTo::create(0.f, std::stof(frames_list.GetValue(name, "setScale")))));
        if (frames_list.GetValue(name, "setScale"))
            frame->setScaleX(std::stof(frames_list.GetValue(name, "setScale")));
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

CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    //settings
    if ("settings") {
        if (std::string(str) == "uwuifier must be loaded...")
            LoadLibraryA("gtps\\libs\\uwuifier.dll");
        if (std::string(str) == "cocos-explorer must be loaded...")
            LoadLibraryA("gtps\\libs\\cocos-explorer.dll");
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
        CCLabelBMFont* lbl = CCLabelBMFont::create(str, "goldFont.fnt");
        CCPoint point = CCPoint();
        point.x = CCMenu::create()->getPositionX() - 50;
        point.y = CCMenu::create()->getPositionY() + 110;
        lbl->runAction(CCRepeatForever::create(CCMoveTo::create(0.0, point)));
        return lbl;
    }
    return CCLabelBMFont_create(str, fntFile);
}

inline void(__thiscall* CCHttpRequest_setUrl)(CCHttpRequest*, const char*);
void __fastcall CCHttpRequest_setUrl_H(CCHttpRequest* self, void*, const char* url) {
    //Change server to robtop's one\n for getting levels
    if (GameManager::sharedState()->getGameVariable("58942")) {
        if (strstr(std::string(url).c_str(), "getGJLevels21.php"))
            url = "http://www.boomlings.com/database/getGJLevels21.php";
        if (strstr(std::string(url).c_str(), "downloadGJLevel22.php"))
            url = "http://www.boomlings.com/database/downloadGJLevel22.php";
    }
    //for betterinfo
    /*if (strstr(std::string(url).c_str(), "getGJScores20.php"))
        url = "http://user95401.undo.it/gtps/core/getGJScores20.php";*/
    CCHttpRequest_setUrl(self, url);
}

void cocosHooks::createHooks() {
    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_create);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create);
    CCEXT_HOOK("?setUrl@CCHttpRequest@extension@cocos2d@@QAEXPBD@Z", CCHttpRequest_setUrl);
}