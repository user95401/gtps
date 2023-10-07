#pragma once
#include "hooks.hpp"
#include "mod_utils.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class PauseLayerExt : public PauseLayer {
public:
    inline static PauseLayerExt* me;
    static void CreateHooks();
};
