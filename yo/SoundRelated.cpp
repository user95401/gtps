#include "SoundRelated.hpp"
#include "SimpleIni.h"

void SoundRelated::playLoadingTheme() {
    GameManager::sharedState()->fadeInMusic("loading_theme.mp3");
}
inline void(__thiscall* GameManager_fadeInMusic)(GameManager*, const char* filename);
void __fastcall GameManager_fadeInMusic_H(GameManager* self, void*, const char* filename) {
    CSimpleIniA rand_sounds_list;
    rand_sounds_list.LoadFile("gtps/rand_sounds_list.ini");
    if (rand_sounds_list.GetSection(filename)) {
        return GameManager_fadeInMusic(self, ModUtils::getRandomFileNameFromDir(rand_sounds_list.GetValue(filename, "dir"), filename).c_str());
    }
    return GameManager_fadeInMusic(self, filename);
}

inline void(__thiscall* GameSoundManager_playEffect)(GameSoundManager*, std::string sName);
void __fastcall GameSoundManager_playEffect_H(GameSoundManager* self, void*, std::string sName) {
    CSimpleIniA rand_sounds_list;
    rand_sounds_list.LoadFile("gtps/rand_sounds_list.ini");
    if (rand_sounds_list.GetSection(sName.c_str())) {
        return GameSoundManager_playEffect(self, ModUtils::getRandomFileNameFromDir(rand_sounds_list.GetValue(sName.c_str(), "dir"), sName).c_str());
    }
    return GameSoundManager_playEffect(self, sName);
}

void SoundRelated::CreateHooks() {
    HOOK(base + 0xC4BD0, GameManager_fadeInMusic);
    HOOK(base + 0x25450, GameSoundManager_playEffect);
}