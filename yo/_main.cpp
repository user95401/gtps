#include "mod_utils.hpp"
#include "hooks.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

#include "cocosHooks.hpp" //ну и псих бляtь
#include "SoundRelated.hpp" //ну и псих бляtь

#include "MenuLayer.hpp"
const char* MenuLayerExt::version = "1.5"; 
const char* MenuLayerExt::upadateInfoUrl = "http://gtps.undo.it/getInf.php?actualVersion";
const char* MenuLayerExt::versionsUrl = "http://gtps.undo.it/getInf.php?download";
const char* MenuLayerExt::onFacebook = "http://gtps.undo.it/getInf.php?onFacebook";
const char* MenuLayerExt::onTwitter = "http://gtps.undo.it/getInf.php?onTwitter";
const char* MenuLayerExt::onYouTube = "http://gtps.undo.it/getInf.php?onYouTube";

#include "LoadingLayer.hpp"
#include "PlayLayer.hpp"
#include "PauseLayer.hpp"
#include "ObjectsController.hpp"

MoreOptionsLayer* _ModOptionsLayer;
float deltaTime;

inline void(__thiscall* MoreOptionsLayer_addToggle)(MoreOptionsLayer*, const char*, const char*, const char*);
void __fastcall MoreOptionsLayer_addToggle_H(MoreOptionsLayer* self, void*, const char* name, const char* key, const char* info) {
    if (string(key) == "0026") {//at first (autoRetry)
        #if 1
        //row1
        MoreOptionsLayer_addToggle(self, "bad play quality", "542984", "it makes PlayLayer <cr>worse</c>");
        MoreOptionsLayer_addToggle(self, "gOOFY camERA", "75649", "make it <cr>follow player</c> as is");
        //row2
        MoreOptionsLayer_addToggle(self, "Disable Free Window Resize", "11388", "Free Window Resize - onload patch\nRemoves limits in place for window resizing.");
        MoreOptionsLayer_addToggle(self, "Maximize Window on load", "113882", nullptr);
        //row3
        MoreOptionsLayer_addToggle(self, "Disable PlayNormally thing", "965784", "layer that shows somtimes on reset level");
        MoreOptionsLayer_addToggle(self, "Always level MainMenu", "98549", "always show level instead deafult main menu bg");
        //row4
        MoreOptionsLayer_addToggle(self, "Dont add random bg\nto play layer", "75821", "sometimes random background appears\n when u playin level");
        MoreOptionsLayer_addToggle(self, "default blend func for trail", "65372", nullptr);
        //title row
        HideEveryFrame = false;
        HideEveryFrameByName = "GJ_checkOff_001.png";
        ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
        ReplaceAllFramesByName::to = "miniSkull_002.png";
        MoreOptionsLayer_addToggle(self, "click on skull btn to\nload uwuifier", "", "uwuifier must be loaded...");
        ReplaceAllFramesByName::by = "";
        ReplaceAllFramesByName::to = "";
        HideEveryFrameByName = "";
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "of modification 950df1", "", nullptr);
        HideEveryFrame = false;
        #endif // 1
        #if 2
        //row1
        MoreOptionsLayer_addToggle(self, "default blend func\nfor all of player", "923956", "most of player things like trail, ghost trail, wave trail, particles have deafult sprite blending");
        MoreOptionsLayer_addToggle(self, "Never level MainMenu", "52905", "Never show level instead deafult main menu bg");
        //row2
        MoreOptionsLayer_addToggle(self, "dont take randBG for gradientBG", "57862", "dont touch that <cb>blue thing</c> in layers");
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        HideEveryFrame = false;
        //row3
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "", "", "");
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        HideEveryFrame = false;
        //row4
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "", "", "");
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        HideEveryFrame = false;
        //title row
        HideEveryFrame = false;
        HideEveryFrameByName = "GJ_checkOff_001.png";
        ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
        ReplaceAllFramesByName::to = "miniSkull_002.png";
        MoreOptionsLayer_addToggle(self, "click on skull btn to\nload uwuifier", "", "uwuifier must be loaded...");
        ReplaceAllFramesByName::by = "";
        ReplaceAllFramesByName::to = "";
        HideEveryFrameByName = "";
        HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "of modification 950df1", "", nullptr);
        HideEveryFrame = false;
        #endif // 2
    }
    MoreOptionsLayer_addToggle(self, name, key, info);
}

inline void(__thiscall* trySaveGame)(AppDelegate*);
void __fastcall trySaveGame_H(AppDelegate* self, void*) {
    trySaveGame(self);
}

inline void(__thiscall* GameManager_update)(GameManager*, float);
void __fastcall GameManager_update_H(GameManager* self, void*, float dt) {
    GameManager_update(self, dt);
    deltaTime = dt;
}

void applyPatches() {
    //"description": "Removes limits in place for window resizing.",
    //"name": "Free Window Resize",
    if (!GameManager::sharedState()->getGameVariable("11388")) {
        ModUtils::write_bytes(libcocos2d + 0x11388B, { 0x90 , 0x90 , 0x90 , 0x90 , 0x90 });
        ModUtils::write_bytes(libcocos2d + 0x11339D, { 0xB9 , 0xFF , 0xFF , 0xFF , 0x7F , 0x90 , 0x90 });
        ModUtils::write_bytes(libcocos2d + 0x1133C0, { 0x48 });
        ModUtils::write_bytes(libcocos2d + 0x1133C6, { 0x48 });
        ModUtils::write_bytes(libcocos2d + 0x112536, { 0xEB, 0x11 , 0x90 });
    }
}

DWORD WINAPI PROCESS_ATTACH(void* hModule) {

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

    HOOK(base + 0x1DF6B0, MoreOptionsLayer_addToggle);
    HOOK(base + 0x3d5e0, trySaveGame);
    HOOK(base + 0xce440, GameManager_update);

    CreateSoundRelatedHooks();
    CreateMenuLayerHooks();
    PlayLayerExt::CreateHooks();
    PauseLayerExt::CreateHooks();
    ObjectsController::setup();
    LevelEditor::CreateHooks();
    
    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    LoadLibraryA("gtps\\libs\\rainsystem.dll");
    LoadLibraryA("gtps\\libs\\levelCustomizer.dll");

    //applyPatches i guess
    applyPatches();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, PROCESS_ATTACH, hModule, 0, 0);
    return TRUE;
}