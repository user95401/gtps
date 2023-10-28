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

    //tab0(blocks)
    if (auto tab0 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(0))) {
        //tab0->m_pButtonArray->addObject(self->getCreateBtn(5321, 4));
        tab0->reloadItemsInNormalSize();
    }

    //tab4(hazaqzrdblokers)
    if (auto tab4 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(4))) {
        tab4->m_pButtonArray->addObject(self->getCreateBtn(9, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(61, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(191, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(198, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(243, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(244, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(363, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(364, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(365, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(366, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(367, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(368, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(393, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(421, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(422, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(446, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(447, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(667, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(720, 4));
        //tab4->m_pButtonArray->addObject(self->getCreateBtn(763, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(989, 4));
        tab4->m_pButtonArray->addObject(self->getCreateBtn(991, 4));
        tab4->reloadItemsInNormalSize();
    }

    //tab11(triggers)
    if (auto tab11 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(11))) {
        //tab11->m_pButtonArray->addObject(self->getCreateBtn(5321, 4));
        tab11->m_pButtonArray->insertObject(self->getCreateBtn(29, 4), 1);//bg
        tab11->m_pButtonArray->insertObject(self->getCreateBtn(30, 4), 2);//grnd
        tab11->m_pButtonArray->insertObject(self->getCreateBtn(105, 4), 3);//obj
        tab11->m_pButtonArray->insertObject(self->getCreateBtn(744, 4), 4);//3dl
        tab11->m_pButtonArray->insertObject(self->getCreateBtn(900, 4), 5);//grnd2
        tab11->m_pButtonArray->insertObject(self->getCreateBtn(915, 4), 6);//line
        tab11->m_pButtonArray->addObject(self->getCreateBtn(55, 4));//eefab
        tab11->m_pButtonArray->addObject(self->getCreateBtn(34, 4));//shitstartpos
        tab11->reloadItemsInNormalSize();
    }
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
