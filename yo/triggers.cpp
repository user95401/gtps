#include "triggers.hpp"

inline void(__thiscall* GameObject_activateObject)(GameObject*, PlayerObject*);
void __fastcall GameObject_activateObject_H(GameObject* self, int, PlayerObject* player) {
    GameObject_activateObject(self, player);
}

inline void(__thiscall* triggerObject)(GameObject*, GJBaseGameLayer*);//0xd1790
void __fastcall triggerObject_H(GameObject* self, void*, GJBaseGameLayer* baseGameLayer) {
    triggerObject(self, baseGameLayer);
}

inline void(__thiscall* GameObject_customSetup)(GameObject*);
void __fastcall GameObject_customSetup_H(GameObject* self, int) {
    GameObject_customSetup(self);
}

PlayLayerExt* (__cdecl* PlayLayer_resetLevel)(PlayLayerExt*);
void __fastcall PlayLayer_resetLevel_H(PlayLayerExt* self) {
    PlayLayer_resetLevel(self);
    PlayLayerExt::me = self;
}

void triggers::Setup() {
    HOOK(base + 0xEF0E0, GameObject_activateObject);
    HOOK(base + 0xd1c10, GameObject_customSetup);
    HOOK(base + 0xd1790, triggerObject);

    ObjectToolbox::sharedState()->addObject(5321, "starAnim_008.png");

    HOOK(base + 0x20BF00, PlayLayer_resetLevel);
}
