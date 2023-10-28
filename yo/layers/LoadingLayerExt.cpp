#include "LoadingLayerExt.hpp"
#include "SimpleIni.h"
const char* (__thiscall* LoadingLayer_getString)(LoadingLayer*);//0x18cf40
const char* __fastcall LoadingLayer_getString_H(LoadingLayer* self, void*) {
    //playLoadingTheme xd
    SoundRelated::playLoadingTheme();
    //geting stringfdd
    const char* s[5] = {
        "<cg>Loading speedrun...</c>",
        "<cr>user666 was here</c>",
        "Counting to lEET",
        "Pro tip: <cr>Don't crash</c>",
        "<cp>Sorry for CCObject::retain crashes :></c>",
    };
    srand(time(NULL));
    return s[rand() % int(sizeof(s) / sizeof(s[0]))];
}

#include "poweredbycocos.hpp"
void (__thiscall* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self, void*) {
    if (GetWindowTextLengthA(GetForegroundWindow()) == 13 || GetWindowTextLengthA(GetForegroundWindow()) == 29)
        LoadingLayer_loadAssets(self);
    else { self->m_nLoadIndex = 0; LoadingLayer_loadAssets(self); }
}
void(__thiscall* LoadingLayer_loadingFinished)(LoadingLayer*);//0x18C790
void __fastcall LoadingLayer_loadingFinished_H(LoadingLayer* self, void*) {
    //title
    SetWindowTextW(GetForegroundWindow(), L"Gemetry Trash Privete Servero");
    //"Maximize Window on load", "113882",
    if (GameManager::sharedState()->getGameVariable("113882"))
        ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);
    if (!self->m_bFromRefresh) {
        auto scene = CCScene::create();
        scene->addChild(poweredbycocos::create());
        auto transition = CCTransitionFade::create(0.5f, scene);
        CCDirector::sharedDirector()->pushScene(transition);
        return;
    }
    LoadingLayer_loadingFinished(self);
}

bool(__thiscall* LoadingLayer_init)(LoadingLayer* self, bool fromReload);
bool __fastcall LoadingLayer_init_H(LoadingLayer* self, void* unk, bool fromReload) {
    if (!LoadingLayer_init(self, fromReload)) return false;
    twoTimesLayerInitHookEscape(self);

    return true;
}

void LoadingLayerExt::CreateHooks() {
    HOOK(base + 0x18cf40, LoadingLayer_getString);
    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets);
    HOOK(base + 0x18C790, LoadingLayer_loadingFinished);
    HOOK(base + 0x18C080, LoadingLayer_init);
}