#pragma once

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

namespace cocosHooks {

	inline bool HideEverySprite;
	inline bool HideEveryFrame;
	inline std::string HideEveryFrameByName;
	class ReplaceAllFramesByName {
	public:
		inline static std::string by;
		inline static std::string to;
	};
	inline bool HideEveryLabel;
	inline bool DontProcessFrames;

	void createHooks();
};
