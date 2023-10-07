#include "LevelEditor.hpp"
#include "cocosHooks.hpp"
/*inline bool(__thiscall* EditButtonBar_init)(EditButtonBar*, cocos2d::CCArray*, int, bool, int, int, cocos2d::CCPoint);//0x6e550
bool __fastcall EditButtonBar_init_H(EditButtonBar* __this, int edx, cocos2d::CCArray* buttons, int idk, bool idkb, int rowCount, int columnCount, cocos2d::CCPoint pos) {
	DontProcessFrames = true;
	auto ret = EditButtonBar_init(__this, buttons, idk, idkb, rowCount, columnCount, pos);
	//EditButtonBar::init
	//DontProcessFrames = false;
	return ret;
}*/

void LevelEditor::CreateHooks() {
	//HOOK(base + 0x6e550, EditButtonBar_init);
}