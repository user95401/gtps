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
#include "CustomBackgroundFeature.hpp"
inline bool(__thiscall* LevelEditorLayer_init)(LevelEditorLayer*, GJGameLevel*);
bool __fastcall LevelEditorLayer_init_H(LevelEditorLayer* self, int, GJGameLevel* level) {
    if (!LevelEditorLayer_init(self, level)) return false;
    CCLayerColor* THE_LINE = CCLayerColor::create({ 255,255,255,55 });
    THE_LINE->setAnchorPoint({ 0.f,0.f });
    THE_LINE->setPosition({ 0, CCDirector::sharedDirector()->getScreenTop() - 115 });
    THE_LINE->setScaleX({ 50 }); THE_LINE->setScaleY({ 0.002f });
    self->addChild(THE_LINE, -1);
    CustomBackground::setTargetLayer(self);
    CCHttpRequest* request = new CCHttpRequest;
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setUrl(("http://user95401.undo.it/gtps/core-modules/CustomBackground/getBg.php?levelID=" + std::to_string(level->m_nLevelID)).c_str());
    request->setResponseCallback(self, httpresponse_selector(CustomBackground::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();
    return true;
}

void LevelEditor::CreateHooks() {
	HOOK(base + 0x15ee00, LevelEditorLayer_init);
}