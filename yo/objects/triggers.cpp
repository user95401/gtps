#include "triggers.hpp"

//OBJECT SETUPS
void triggers::activateObject(GameObject* self, PlayerObject* player) {
}

void triggers::triggerObject(GameObject* self, GJBaseGameLayer* baseGameLayer) {
    if (self->m_nObjectID == 9301) {
        baseGameLayer->m_pObjectLayer->setZOrder(8);
    }
}
void triggers::customSetup(GameObject* self) {
    if (self->m_nObjectID == 9301) {
        self->m_nObjectType = GameObjectType::kGameObjectTypeModifier;
        self->m_bIsEffectObject = true;
        self->m_bTrigger = true;
        if (!self->m_bEditor) self->setOpacity(0);
    }
}

//EDITOR SETUP
void triggers::setupCreateMenu(EditorUI* self) {
    //tab8(deco)
    if (auto tab8 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(8))) {
        //tab8->m_pButtonArray->addObject(self->getCreateBtn(9301, 4));
        tab8->m_pButtonArray->addObject(self->getCreateBtn(9301, 4));
        tab8->reloadItemsInNormalSize();
    }
}

//PLAYLAYER THINGS
void triggers::resetLevel(PlayLayerExt* self) {
    if (self->m_pObjectLayer->getZOrder() == 8) self->m_pObjectLayer->setZOrder(0);
}
void triggers::updateProgressbar(PlayLayerExt* self) {
}

void triggers::setup() {
    //add via ObjectToolbox
    ObjectToolbox::sharedState()->addObject(9301, "rod_01_001.png");
}
