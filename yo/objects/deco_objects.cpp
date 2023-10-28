#include "deco_objects.hpp"

//OBJECT SETUPS
void deco_objects::activateObject(GameObject* self, PlayerObject* player) {
}

void deco_objects::triggerObject(GameObject* self, GJBaseGameLayer* baseGameLayer) {
}
void deco_objects::customSetup(GameObject* self) {
    if (self->m_sTextureName.find("SwissArcadeGameEntertainment_some_black_white_tiles") != self->m_sTextureName.npos) {
        self->m_nObjectType = GameObjectType::kGameObjectTypeDecoration;
        self->setBatchNode(CCSpriteBatchNode::create(".CustomBackground", 1233));
    }
    if (self->m_sTextureName.find("idk_theme") != self->m_sTextureName.npos) {
        self->m_nObjectType = GameObjectType::kGameObjectTypeDecoration;
    }
    if (self->m_sTextureName.find("KenneyNL_tile") != self->m_sTextureName.npos) {
        self->m_nObjectType = GameObjectType::kGameObjectTypeDecoration;
    }
}

//EDITOR SETUP
void deco_objects::setupCreateMenu(EditorUI* self) {
    //tab0(blocks)
    if (auto tab0 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(0))) {
        //tab0->m_pButtonArray->addObject(self->getCreateBtn(5321, 4));
        if ("SwissArcadeGameEntertainment_some_black_white_tiles") {
            for (int i = 1; i <= 15; ++i)
                tab0->m_pButtonArray->addObject(self->getCreateBtn(9000 + i, 4));
        }
        if ("KenneyNL_tile") {
            for (int i = 1; i <= 81; ++i)
                tab0->m_pButtonArray->addObject(self->getCreateBtn(9200 + i, 4));
        }
        tab0->reloadItemsInNormalSize();
    }
    //tab8(deco)
    if (auto tab8 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(8))) {
        //tab8->m_pButtonArray->addObject(self->getCreateBtn(5321, 4));
        if ("idk_theme") {
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9101, 4));//idk_theme_hi_modxd.png");
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9102, 4));//idk_theme_emod.png");
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9103, 4));//idk_theme_troll.png");
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9104, 4));//idk_theme_thinksmart.png");
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9105, 4));//idk_theme_dank_laugh.png");
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9106, 4));//idk_theme_like.png");
            tab8->m_pButtonArray->addObject(self->getCreateBtn(9107, 4));//idk_theme_dislike.png");
        }
        tab8->reloadItemsInNormalSize();
    }
}

//PLAYLAYER THINGS
void deco_objects::resetLevel(PlayLayerExt* self) {
}
void deco_objects::updateProgressbar(PlayLayerExt* self) {
}

void deco_objects::setup() {
    //add via ObjectToolbox
    if ("SwissArcadeGameEntertainment_some_black_white_tiles") {
        for (int i = 1; i <= 15; ++i) 
            ObjectToolbox::sharedState()->addObject(9000 + i, ("SwissArcadeGameEntertainment_some_black_white_tiles_" + to_string(i) + ".png").c_str());
    }
    if ("idk_theme") {
        ObjectToolbox::sharedState()->addObject(9101, "idk_theme_hi_modxd.png");
        ObjectToolbox::sharedState()->addObject(9102, "idk_theme_emod.png");
        ObjectToolbox::sharedState()->addObject(9103, "idk_theme_troll.png");
        ObjectToolbox::sharedState()->addObject(9104, "idk_theme_thinksmart.png");
        ObjectToolbox::sharedState()->addObject(9105, "idk_theme_dank_laugh.png");
        ObjectToolbox::sharedState()->addObject(9106, "idk_theme_like.png");
        ObjectToolbox::sharedState()->addObject(9107, "idk_theme_dislike.png");
    }
    if ("KenneyNL_tile") {
        for (int i = 1; i <= 81; ++i)
            ObjectToolbox::sharedState()->addObject(9200 + i, ("KenneyNL_tile_" + to_string(i) + ".png").c_str());
    }
}
