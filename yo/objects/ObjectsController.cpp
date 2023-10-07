#include "ObjectsController.hpp"

#include "deco_objects.hpp"
#include "triggers.hpp"

//OBJECT SETUPS
#if 1
inline void(__thiscall* activateObject)(GameObject*, PlayerObject*);
void __fastcall activateObject_H(GameObject* self, int, PlayerObject* player) {
    activateObject(self, player);
    deco_objects::activateObject(self, player);
    triggers::activateObject(self, player);
}

inline void(__thiscall* triggerObject)(GameObject*, GJBaseGameLayer*);//0xd1790
void __fastcall triggerObject_H(GameObject* self, void*, GJBaseGameLayer* baseGameLayer) {
    triggerObject(self, baseGameLayer);
    deco_objects::triggerObject(self, baseGameLayer);
    triggers::triggerObject(self, baseGameLayer);
}

inline void(__thiscall* customSetup)(GameObject*);
void __fastcall customSetup_H(GameObject* self, int) {
    customSetup(self);
    deco_objects::customSetup(self);
    triggers::customSetup(self);
}
#endif // 1

//EDITOR SETUP
inline void(__thiscall* setupCreateMenu)(EditorUI*);
void __fastcall setupCreateMenu_H(EditorUI* self, void*) {
    setupCreateMenu(self);
    deco_objects::setupCreateMenu(self);
    triggers::setupCreateMenu(self);
}

//PLAYLAYER THINGS
#if 1
void ObjectsController::resetLevel(PlayLayerExt* self) {
    deco_objects::resetLevel(self);
    triggers::resetLevel(self);
}
void ObjectsController::updateProgressbar(PlayLayerExt* self) {
    deco_objects::updateProgressbar(self);
    triggers::updateProgressbar(self);
}
#endif // 1

void ObjectsController::setup() {
    //add via ObjectToolbox
    deco_objects::setup();
    triggers::setup();
    //hooks
    HOOK(base + 0xd1c10, customSetup);
    HOOK(base + 0xEF0E0, activateObject);
    HOOK(base + 0xd1790, triggerObject);
    HOOK(base + 0x7CAF0, setupCreateMenu);//huh
}
