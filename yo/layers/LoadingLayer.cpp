#include "LoadingLayer.hpp"
using namespace std;
const char* (__thiscall* LoadingLayer_getString)(LoadingLayer*);
const char* __fastcall LoadingLayer_getString_H(LoadingLayer* self, void*) {
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

void LoadingLayerHook() {
    HOOK(base + 0x18cf40, LoadingLayer_getString, true);
}