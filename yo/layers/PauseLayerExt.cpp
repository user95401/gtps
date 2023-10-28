#include "PlayLayerExt.hpp"
#include "PauseLayerExt.hpp"
#include "SoundRelated.hpp"

inline void(__thiscall* customSetup)(PauseLayerExt*);//0x1e4620
void __fastcall customSetup_H(PauseLayerExt* self) {
    customSetup(self);
    PauseLayerExt::me = self;
    twoTimesLayerCustomSetupEscape(self);
    if (reinterpret_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(1))->getString() == PlayLayerExt::me->m_level->m_sLevelName) {
        CCLabelBMFont* nameLbl = reinterpret_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(1));
        nameLbl->setAnchorPoint({ 0.5f, 0.3f });
        CCLabelBMFont* creatorLbl = CCLabelBMFont::create((PlayLayerExt::me->m_level->m_sCreatorName).c_str(), nameLbl->getFntFile());
        creatorLbl->setPosition(nameLbl->getPosition());
        creatorLbl->setScale(0.5f);
        creatorLbl->setAnchorPoint({0.5f, 1.3f});
        creatorLbl->setBlendFunc({ GL_ONE, GL_ZERO });
        self->addChild(creatorLbl, -1);
        //nameLbl->setRotation(12);
    }
}
inline void(__thiscall* onResume)(PauseLayerExt*, CCObject*);//0x1e5fa0
void __fastcall onResume_H(PauseLayerExt* self, void*, CCObject* sender) {
    onResume(self, sender);
}

void PauseLayerExt::CreateHooks() {
    HOOK(base + 0x1e4620, customSetup);
    HOOK(base + 0x1e5fa0, onResume);
}