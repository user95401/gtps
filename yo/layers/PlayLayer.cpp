#include "PlayLayer.hpp"

bool(__thiscall* PlayLayer_init)(PlayLayerExt*, GJGameLevel*);
bool __fastcall PlayLayer_init_H(PlayLayerExt* self, int edx, GJGameLevel* level) {
    if (!PlayLayer_init(self, level)) return false;
    PlayLayerExt::me = self;
    //"bad play quality", "542984", "it makes Playlayer <cr>worse</c>"
    if(GameManager::sharedState()->getGameVariable("542984")) 
        self->runAction(CCShaky3D::create(0.1, CCSizeMake(1, 1), 1, false));
    return true;
}

void PlayLayerExt::CreateHooks() {
    HOOK(base + 0x1fb780, PlayLayer_init);
}