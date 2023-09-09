#include <Windows.h>
#include <iostream>
#include <cocos2d.h>
#include <gd.h>
#include "mod_utils.hpp"
#include "hooks.hpp"
#include <MinHook.h>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

#include "cocosHooks.hpp" //ну и псих бляtь
#include "SoundRelated.hpp" //ну и псих бляtь

#include "MenuLayer.hpp"
const char* MenuLayerExt::version = "1.5"; 
const char* MenuLayerExt::upadateInfoUrl = "getInf.php?actualVersion";
const char* MenuLayerExt::versionsUrl = "download";
const char* MenuLayerExt::onFacebook = "cuming_soon";
const char* MenuLayerExt::onTwitter = "cuming_soon";
const char* MenuLayerExt::onYouTube = "cuming_soon";

#include "LoadingLayer.hpp"
#include "PlayLayer.hpp"
#include "deco_objects.hpp"

inline void(__thiscall* MoreOptionsLayer_addToggle)(MoreOptionsLayer*, const char*, const char*, const char*);
void __fastcall MoreOptionsLayer_addToggle_H(MoreOptionsLayer* self, void*, const char* name, const char* key, const char* info) {
    if (string(key) == "0026") {//at first (autoRetry)
        //row1
        MoreOptionsLayer_addToggle(self, "bad play quality", "542984", "it makes PlayLayer <cr>worse</c>");
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //row2
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //row3
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //row4
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //title row
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        MoreOptionsLayer_addToggle(self, "of modification 950df1", "", nullptr);
        HideEveryFrame = false;
    }
    MoreOptionsLayer_addToggle(self, name, key, info);
}

DWORD WINAPI thread_func(void* hModule) {
    //instant hooks
    MH_Initialize();

    LoadingLayerExt::SetSearchPaths();
    LoadingLayerExt::CreateHooks();

    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_create);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create);

    MH_EnableHook(MH_ALL_HOOKS);

    // safe hooks
    MH_SafeInitialize();

    CreateSoundRelatedHooks();
    CreateMenuLayerHooks();
    PlayLayerExt::CreateHooks();
    HOOK(base + 0x1DF6B0, MoreOptionsLayer_addToggle);
    deco_objects::setup();

    if ("iconsPatch") {
    }
    
    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}