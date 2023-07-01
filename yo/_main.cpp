#define WIN32_LEAN_AND_MEAN
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

#include "MenuLayer.hpp"
const char* MenuLayerMod::version = "1.0"; 
const char* MenuLayerMod::upadateInfoUrl = "http://speeddash.ml/getInf.php?actualVersion";
const char* MenuLayerMod::versionsUrl = "http://speeddash.ml/download";

#include "LoadingLayer.hpp"

DWORD WINAPI thread_func(void* hModule) {

    // initialize minhook
    MH_Initialize();

    MenuLayerHook();
    LoadingLayerHook();

    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createHook, CCSprite_createOrg);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameNameHook, CCSprite_createWithSpriteFrameNameOrg);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_createHook, CCLabelBMFont_createOrg);
    
    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}