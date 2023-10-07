#include "SoundRelated.hpp"
#include "SimpleIni.h"

void SoundRelated::playLoadingTheme() {
    GameManager::sharedState()->fadeInMusic("loading_theme.mp3");
}

inline void(__thiscall* fadeInMusic)(GameManager*, const char* filename);
void __fastcall fadeInMusic_H(GameManager* self, void*, const char* filename) {
    CSimpleIniA rand_sounds_list;
    rand_sounds_list.LoadFile("gtps/rand_sounds_list.ini");
    if (rand_sounds_list.GetSection(filename)) {
        return fadeInMusic(self, ModUtils::getRandomFileNameFromDir(rand_sounds_list.GetValue(filename, "dir"), filename).c_str());
    }
    return fadeInMusic(self, filename);
}

inline void(__thiscall* playEffect)(GameManager*, std::string sName);
void __fastcall playEffect_H(GameManager* self, void*, std::string sName) {
    CSimpleIniA rand_sounds_list;
    rand_sounds_list.LoadFile("gtps/rand_sounds_list.ini");
    if (rand_sounds_list.GetSection(sName.c_str())) {
        return playEffect(self, ModUtils::getRandomFileNameFromDir(rand_sounds_list.GetValue(sName.c_str(), "dir"), sName).c_str());
    }
    return playEffect(self, sName);
}

void CreateSoundRelatedHooks() {
    HOOK(base + 0xC4BD0, fadeInMusic);
    HOOK(base + 0x25450, playEffect);
}