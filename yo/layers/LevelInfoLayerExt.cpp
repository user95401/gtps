#include "LevelInfoLayerExt.hpp"
#include "CustomBackgroundFeature.hpp"
#include "CustomObjectsTextureFeature.hpp"

inline bool(__thiscall* LevelInfoLayer_init)(LevelInfoLayerExt*, GJGameLevel*);//0x175df0
bool __fastcall LevelInfoLayer_init_H(LevelInfoLayerExt* self, void*, GJGameLevel* lvl) {
    //org and other next
    LevelInfoLayer_init(self, lvl);
    twoTimesLayerInitHookEscape(self);
    self->me = self;
    CCMenu* menu = CCMenu::create();
    self->addChild(menu);
    if (lvl->m_sCreatorName == GameManager::sharedState()->m_sPlayerName) {//setBgBtn
        auto setBgBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_everyplayBtn_001.png"), self, menu_selector(CustomBackgroundPopup::createAndShowMe));
        setBgBtn->setPositionX(-170.f);
        setBgBtn->setPositionY(-140.f);
        setBgBtn->CCMenuItemSpriteExtra::setScale(0.5f);
        menu->addChild(setBgBtn);
        /*auto setObjTexturesBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("block001_01_001.png"), self, menu_selector(CustomObjectsTextureFeaturePopup::createAndShowMe));
        setObjTexturesBtn->setPositionX(-192.f);
        setObjTexturesBtn->setPositionY(-148.f);
        setObjTexturesBtn->CCMenuItemSpriteExtra::setScale(0.5f);
        self->m_pPlayBtnMenu->addChild(setObjTexturesBtn);*/
    }
}

inline void(__thiscall* LevelInfoLayer_onPlay)(LevelInfoLayerExt*, CCObject*);
void __fastcall LevelInfoLayer_onPlay_H(LevelInfoLayerExt* self, void*, CCObject* pSender) {
    LevelInfoLayer_onPlay(self, pSender);
}

void LevelInfoLayerExt::CreateHooks() {
    HOOK(base + 0x175df0, LevelInfoLayer_init);
    HOOK(base + 0x179730, LevelInfoLayer_onPlay);
}