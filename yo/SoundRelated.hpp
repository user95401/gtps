#pragma once
#include "hooks.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
#include "mod_utils.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class SoundRelated : public GameSoundManager {
public:
	static void playLoadingTheme();
	inline static bool dontPlayMenuLoop;
};

void CreateSoundRelatedHooks();
