#include "deco_objects.hpp"

inline void(__thiscall* deco_customSetup)(GameObject*);
void __fastcall deco_customSetup_H(GameObject* self, int) {
    deco_customSetup(self);
    if (self->m_nObjectID == 5321) {
        self->m_nObjectType = GameObjectType::kGameObjectTypeDecoration;
    }
}

inline void(__thiscall* deco_setupCreateMenu)(EditorUI*);
void __fastcall deco_setupCreateMenu_H(EditorUI* self, void*) {
    deco_setupCreateMenu(self);
    //tab11(triggers)
    if (auto tab11 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(11))) {
        tab11->m_pButtonArray->addObject(self->getCreateBtn(5321, 4));
        tab11->reloadItemsInNormalSize();
    }
}

void deco_objects::setup() {
    ObjectToolbox::sharedState()->addObject(5321, "starAnim_008.png");
    HOOK(base + 0xd1c10, deco_customSetup);
    HOOK(base + 0x7CAF0, deco_setupCreateMenu, true);//huh
}
