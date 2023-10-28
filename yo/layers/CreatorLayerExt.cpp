#include "CreatorLayerExt.hpp"

void CreatorLayerExt::onSomeBtn(cocos2d::CCObject* pSender) {
    //or reinterpret_cast<CCLayer*>(pSender) instead this->me
    this->me->runAction(CCEaseExponentialOut::create(CCRotateBy::create(1.0, 60)));
}

void CreatorLayerExt::onSomeBtn2(cocos2d::CCObject* pSender) {
    //or reinterpret_cast<CCLayer*>(pSender) instead this->me
    this->me->runAction(CCEaseExponentialOut::create(CCScaleTo::create(1.0, this->me->getScale() - 0.1f)));//CCScaleBy is imposter
}

void CreatorLayerExt::onSomeBtn3(cocos2d::CCObject* pSender) {
    this->me->removeChild(reinterpret_cast<CCNode*>(this->me->getChildren()->objectAtIndex(0)));
    reinterpret_cast<CCNode*>(this->me->getChildren()->objectAtIndex(0))->runAction(CCTintTo::create(0.1f, 180, 80, 80));
}

void addclbtn(const char* name, cocos2d::SEL_MenuHandler sus, const CCPoint& pos, CCMenu* menu) {
    CCSprite* btn = ModUtils::createSprite(name);
    btn->setScale(0.8f);
    auto btnItem = CCMenuItemSpriteExtra::create(btn, menu, sus);
    btnItem->setPosition(pos);
    menu->addChild(btnItem);
}

inline bool(__thiscall* CreatorLayer_init)(CreatorLayerExt*);
bool __fastcall CreatorLayer_init_H(CreatorLayerExt* self) {
    CreatorLayer_init(self);
    CreatorLayerExt::me = self;

    return true;
}

void CreatorLayerExt::CreateHooks() {
    HOOK(base + 0x4de40, CreatorLayer_init);
}