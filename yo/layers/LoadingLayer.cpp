#include "LoadingLayer.hpp"
const char* (__thiscall* LoadingLayer_getString)(LoadingLayer*);//0x18cf40
const char* __fastcall LoadingLayer_getString_H(LoadingLayer* self, void*) {
    //playLoadingTheme xd
    SoundRelated::playLoadingTheme();
    //geting stringfdd
    const char* s[4] = {
        "Loading speedrun...",
        "user666 was here",
        "Counting to lEET",
        "Pro tip: Don't crash",
    };
    srand(time(NULL));
    return s[rand() % 4];
}

void (__thiscall* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self, void*) {
    LoadingLayerExt::SetSearchPaths();
    LoadingLayer_loadAssets(self);
}

void(__thiscall* LoadingLayer_loadingFinished)(LoadingLayer*);//0x18C790
void __fastcall LoadingLayer_loadingFinished_H(LoadingLayer* self, void*) {
    LoadingLayer_loadingFinished(self);
    //title
    SetWindowTextW(GetForegroundWindow(), L"Gemetry Trash Privete Servero");
}

bool(__thiscall* LoadingLayer_init)(LoadingLayer* self, bool fromReload);
bool __fastcall LoadingLayer_init_H(LoadingLayer* self, void* unk, bool fromReload) {
    if (!LoadingLayer_init(self, fromReload)) return false;
    self->addChild(CCLayerGradient::create({ 12,12,12,100 }, { 112,112,112,150 }));
    return true;
}

void LoadingLayerExt::CreateHooks() {
    HOOK(base + 0x18cf40, LoadingLayer_getString);
    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets);
    HOOK(base + 0x18C790, LoadingLayer_loadingFinished);
    HOOK(base + 0x18C080, LoadingLayer_init);
}