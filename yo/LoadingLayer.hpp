#pragma once
#include <iostream>
#include <ctime>
#include "hooks.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class LoadingLayerMod : LoadingLayer {
public:
};
void LoadingLayerHook();
