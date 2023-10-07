#pragma once
#include "hooks.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
#include "PlayLayer.hpp"
#include "LevelEditor.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
using namespace std;
class triggers {
public:
    static void activateObject(GameObject* self, PlayerObject* player);
    static void triggerObject(GameObject* self, GJBaseGameLayer* baseGameLayer);
    static void customSetup(GameObject* self);
    static void setupCreateMenu(EditorUI* self);
    static void resetLevel(PlayLayerExt* self);
    static void updateProgressbar(PlayLayerExt* self);
    static void setup();
};