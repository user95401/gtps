#pragma once
#include "hooks.hpp"
#include "mod_utils.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class LevelInfoLayerExt : public LevelInfoLayer {
public:
    inline static LevelInfoLayerExt* me;
    static void CreateHooks();
};
