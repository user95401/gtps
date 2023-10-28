#include "mod_utils.hpp"
#include "hooks.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

#include "cocosHooks.hpp" //ну и псих бляtь
#include "SoundRelated.hpp" //ну и псих бляtь

#include "MenuLayerExt.hpp"
const char* MenuLayerExt::version = "1.6"; 
const char* MenuLayerExt::upadateInfoUrl = "http://gtps.undo.it/getInf.php?actualVersion";
const char* MenuLayerExt::versionsUrl = "http://gtps.undo.it/getInf.php?download";
const char* MenuLayerExt::onFacebook = "http://gtps.undo.it/getInf.php?onFacebook";
const char* MenuLayerExt::onTwitter = "http://gtps.undo.it/getInf.php?onTwitter";
const char* MenuLayerExt::onYouTube = "http://gtps.undo.it/getInf.php?onYouTube";

#include "LoadingLayerExt.hpp"
#include "PlayLayerExt.hpp"
#include "PauseLayerExt.hpp"
#include "ObjectsController.hpp"
#include "LevelInfoLayerExt.hpp"
#include "ProfilePageExt.hpp"
#include "CreatorLayerExt.hpp"

MoreOptionsLayer* _ModOptionsLayer;
float deltaTime;

void ApplyPatches() {
    //"description": "Removes limits in place for window resizing.",
    //"name": "Free Window Resize",
    if (!GameManager::sharedState()->getGameVariable("11388")) {
        ModUtils::write_bytes(libcocos2d + 0x11388B, { 0x90 , 0x90 , 0x90 , 0x90 , 0x90 });
        ModUtils::write_bytes(libcocos2d + 0x11339D, { 0xB9 , 0xFF , 0xFF , 0xFF , 0x7F , 0x90 , 0x90 });
        ModUtils::write_bytes(libcocos2d + 0x1133C0, { 0x48 });
        ModUtils::write_bytes(libcocos2d + 0x1133C6, { 0x48 });
        ModUtils::write_bytes(libcocos2d + 0x112536, { 0xEB, 0x11 , 0x90 });
    }
    // Level Completion
    ModUtils::write_bytes(base + 0x1FD557, { 0xEB, 0x0C, });
    ModUtils::write_bytes(base + 0x1FD742, { 0xC7, 0x87, 0xE0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x87, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x1FD756, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x1FD79A, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x1FD7AF, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    // Load Failed
    ModUtils::write_bytes(base + 0x18B2B4, { 0xB0 , 0x01 });
    //Object Bypass
    ModUtils::write_bytes(base + 0x73169, { 0xFF, 0xFF, 0xFF, 0x7F });
    ModUtils::write_bytes(base + 0x856A4, { 0xFF, 0xFF, 0xFF, 0x7F });
    ModUtils::write_bytes(base + 0x87B17, { 0xFF, 0xFF, 0xFF, 0x7F });
    ModUtils::write_bytes(base + 0x87BC7, { 0xFF, 0xFF, 0xFF, 0x7F });
    ModUtils::write_bytes(base + 0x87D95, { 0xFF, 0xFF, 0xFF, 0x7F });
    ModUtils::write_bytes(base + 0x880F4, { 0xFF, 0xFF, 0xFF, 0x7F });
    ModUtils::write_bytes(base + 0x160B06, { 0xFF, 0xFF, 0xFF, 0x7F });
    //Text Length
    ModUtils::write_bytes(base + 0x21ACB, { 0xEB, 0x04 });
    //Character Filter
    ModUtils::write_bytes(base + 0x21A99, { 0x90, 0x90 });
    //Default Song Bypass
    ModUtils::write_bytes(base + 0x174407, { 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x174411, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x174456, { 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x174460, { 0x90, 0x90, 0x90 });
    //Rotation Hack
    ModUtils::write_bytes(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    //Practice Pulse
    ModUtils::write_bytes(base + 0x205536, { 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x20555D, { 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x20553E, { 0xEB });
    //Custom Object Bypass
    ModUtils::write_bytes(base + 0x7A100, { 0xEB, });
    ModUtils::write_bytes(base + 0x7A022, { 0xEB, });
    ModUtils::write_bytes(base + 0x7A203, { 0x90, 0x90 });
    //Smooth Editor Trail
    ModUtils::write_bytes(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
}

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
        MoreOptionsLayer_addToggle(self, "dont take randBG for gradientBG", "57862", "dont touch that <cb>blue thing</c> in layers");
        MoreOptionsLayer_addToggle(self, "default blend func for trail", "65372", nullptr);
        //title row
        cocosHooks::HideEveryFrame = false;
        cocosHooks::HideEveryFrameByName = "GJ_checkOff_001.png";
        cocosHooks::ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
        cocosHooks::ReplaceAllFramesByName::to = "miniSkull_002.png";
        MoreOptionsLayer_addToggle(self, "click on skull btn to\nload uwuifier", "124231", "uwuifier must be loaded...");
        cocosHooks::ReplaceAllFramesByName::by = "";
        cocosHooks::ReplaceAllFramesByName::to = "";
        cocosHooks::HideEveryFrameByName = "";
        cocosHooks::HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "of modification 950df1", "", nullptr);
        cocosHooks::HideEveryFrame = false;
        #endif // 1
        #if 2
        //row1
        MoreOptionsLayer_addToggle(self, "default blend func\nfor all of player", "923956", "most of player things like trail, ghost trail, wave trail, particles have deafult sprite blending");
        MoreOptionsLayer_addToggle(self, "Never level MainMenu", "52905", "Never show level instead deafult main menu bg");
        //row2
        MoreOptionsLayer_addToggle(self, "Logo RGB", "89953", "animate logo color");
        cocosHooks::HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //row3
        MoreOptionsLayer_addToggle(self, "", "", "");
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //row4
        MoreOptionsLayer_addToggle(self, "", "", "");
        MoreOptionsLayer_addToggle(self, "", "", nullptr);
        //title row
        cocosHooks::HideEveryFrame = false;
        cocosHooks::HideEveryFrameByName = "GJ_checkOff_001.png";
        cocosHooks::ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
        cocosHooks::ReplaceAllFramesByName::to = "miniSkull_002.png";
        MoreOptionsLayer_addToggle(self, "click on skull btn to\nload cocos-explorer", "54211", "cocos-explorer must be loaded...");
        cocosHooks::ReplaceAllFramesByName::by = "";
        cocosHooks::ReplaceAllFramesByName::to = "";
        cocosHooks::HideEveryFrameByName = "";
        cocosHooks::HideEveryFrame = true;
        MoreOptionsLayer_addToggle(self, "of modification 950df1", "", nullptr);
        cocosHooks::HideEveryFrame = false;
        #endif // 2
    }
    MoreOptionsLayer_addToggle(self, name, key, info);
}

class MoreSearchLayerExt : public FLAlertLayer {
public:
    CCLabelBMFont* lbl;
    void onLbl(CCObject*) {
        GameManager::sharedState()->toggleGameVariable("58942");
        updateLbl();
    };
    void updateLbl() {
        lbl->setColor(cocos2d::ccGRAY);
        lbl->setString("Change server to robtop's one\n for getting levels");
        if (GameManager::sharedState()->getGameVariable("58942")) {
            lbl->setColor(cocos2d::ccWHITE);
            lbl->setString("Changed server to robtop's one\n for getting levels");
        }
    }
};
inline bool(__thiscall* MoreSearchLayer_init)(MoreSearchLayerExt*);//0x1825c0
bool __fastcall MoreSearchLayer_init_H(MoreSearchLayerExt* self, void*) {
    bool ret = MoreSearchLayer_init(self);
    twoTimesLayerInitHookEscape(self);
    self->lbl = CCLabelBMFont::create("Changed server to robtop's one\n for getting levels", "bigFont.fnt");
    self->updateLbl();
    CCMenuItemSpriteExtra* lblBtn = CCMenuItemSpriteExtra::create(self->lbl, self, menu_selector(MoreSearchLayerExt::onLbl));
    lblBtn->setPositionX(-212.f);
    lblBtn->setPositionY(-136.f);
    lblBtn->CCMenuItemSpriteExtra::setScale(0.15f);
    lblBtn->setAnchorPoint(CCPoint());
    self->getLayer()->addChild(CCMenu::createWithItem(lblBtn));
    return ret;
}

inline void(__thiscall* trySaveGame)(AppDelegate*);
void __fastcall trySaveGame_H(AppDelegate* self, void*) {
    trySaveGame(self);
}

inline void(__thiscall* GameManager_update)(GameManager*, float);
void __fastcall GameManager_update_H(GameManager* self, void*, float dt) {
    GameManager_update(self, dt);
    deltaTime = dt;
    //applyPatches i guess
    ApplyPatches();
}

DWORD WINAPI PROCESS_ATTACH(void* hModule) {
    //geode SetSearchPaths easter eggs
    Sleep(12);
    //SetSearchPaths
    LoadingLayerExt::SetSearchPaths();
    //instant hooks
    MH_STATUS ew;
    ew = MH_Initialize();
    cocosHooks::createHooks();
    LoadingLayerExt::CreateHooks();
    // safe hooks
    MH_STATUS eew;
    eew = MH_SafeInitialize();
    HOOK(base + 0x1DF6B0, MoreOptionsLayer_addToggle);
    HOOK(base + 0x1825c0, MoreSearchLayer_init);
    HOOK(base + 0x3d5e0, trySaveGame);
    HOOK(base + 0xce440, GameManager_update);
    SoundRelated::CreateHooks();
    MenuLayerExt::CreateHooks();
    PlayLayerExt::CreateHooks();
    PauseLayerExt::CreateHooks();
    ObjectsController::setup();
    LevelEditor::CreateHooks();
    LevelInfoLayerExt::CreateHooks();
    ProfilePageExt::CreateHooks();
    CreatorLayerExt::CreateHooks();
    //load libs
    if (LoadLibraryA("gtps\\libs\\rainsystem.dll")) ModUtils::log("rainsystem.dll loaded");
    else                                            CCMessageBox("cant load rainsystem.dll", ModUtils::GetModName().c_str());
    if (LoadLibraryA("gtps\\libs\\levelCustomizer.dll")) ModUtils::log("levelCustomizer.dll loaded");
    else                                            CCMessageBox("cant load levelCustomizer.dll", ModUtils::GetModName().c_str());
    //MakeModFolderTree() {
    std::filesystem::create_directories("gtps\\Resources\\UserContent");//!!!!!!!!!!
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, PROCESS_ATTACH, hModule, 0, 0);
    return TRUE;
}


/*
std::string dev;
getline(std::ifstream("gtps/.dev"), dev);
*/