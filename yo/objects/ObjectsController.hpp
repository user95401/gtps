#pragma once
#include "hooks.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
#include "PlayLayerExt.hpp"
#include "LevelEditor.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
using namespace std;
class ObjectsController {
public:
    static void resetLevel(PlayLayerExt* self);
    static void updateProgressbar(PlayLayerExt* self);
    static void setup();
};