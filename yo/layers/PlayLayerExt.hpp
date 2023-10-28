#pragma once
#include "hooks.hpp"
#include "mod_utils.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class PlayLayerExt : public PlayLayer {
public:
    inline static PlayLayerExt* me;
    static void CreateHooks();
};
