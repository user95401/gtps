#pragma once
#include <cocos2d.h>
#include "mod_utils.hpp"
using namespace cocos2d;

inline CCSprite* (__cdecl* CCSprite_create)(const char* name);
CCSprite* CCSprite_create_H(const char* name);

inline CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char* name);
CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name);

inline CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char* str, const char* fntFile);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile);
