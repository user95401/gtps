#include "SoundRelated.hpp"

void SoundRelated::playLoadingTheme() {
    GameManager::sharedState()->fadeInMusic("loading_theme.mp3");
}

inline void(__thiscall* fadeInMusic)(GameManager*, const char* filename);
void __fastcall fadeInMusic_H(GameManager* self, void*, const char* filename) {
    if (filename == std::string("menuLoop.mp3"))
        return fadeInMusic(self, ModUtils::getRandomFileNameFromDir("gtps/Resources/sounds/menuLoop", filename).c_str());
    return fadeInMusic(self, filename);
}

inline void(__thiscall* playEffect)(GameManager*, std::string sName);
void __fastcall playEffect_H(GameManager* self, void*, std::string sName) {
    if (sName == std::string("explode_11.ogg"))
        return playEffect(self, ModUtils::getRandomFileNameFromDir("gtps/Resources/sounds/explode", sName).c_str());
    if (sName == std::string("quitSound_01.ogg"))
        return playEffect(self, ModUtils::getRandomFileNameFromDir("gtps/Resources/sounds/quitSound", sName).c_str());
    return playEffect(self, sName);
}

void CreateSoundRelatedHooks() {
    HOOK(base + 0xC4BD0, fadeInMusic);
    HOOK(base + 0x25450, playEffect);
}