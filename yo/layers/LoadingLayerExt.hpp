#pragma once
#include "hooks.hpp"
#include <MinHook.h>
#include <cocos2d.h>
#include <gd.h>
#include "SoundRelated.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
using namespace std;
class LoadingLayerExt : public LoadingLayer {
public:
    static void SetSearchPaths() {
        vector<string> wasSearchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        if (wasSearchPaths.front() != CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps", 0)) {
            vector<string> SearchPaths = {
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps\\Resources\\UserContent", 0),
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps", 0),
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps\\Resources", 0),
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps\\Resources\\sprites", 0),
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps\\Resources\\sprites\\ScaleFactorIgnored", 0),
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps\\Resources\\data", 0),
                CCFileUtils::sharedFileUtils()->fullPathForFilename("gtps\\Resources\\sounds", 0)
            };
            SearchPaths.insert(SearchPaths.end(), wasSearchPaths.begin(), wasSearchPaths.end());
            CCFileUtils::sharedFileUtils()->setSearchPaths(SearchPaths);
        }
        // Convert vector to string
        wasSearchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        std::stringstream ss;
        for (size_t i = 0; i < wasSearchPaths.size(); ++i)
        {
            if (i != 0)
                ss << ", \n";
            ss << wasSearchPaths[i];
        }

        //CCMessageBox(ss.str().c_str(), "asd");
    }
    static void CreateHooks();
};
