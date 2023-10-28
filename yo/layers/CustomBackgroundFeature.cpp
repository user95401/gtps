#include "CustomBackgroundFeature.hpp"
#include "mod_utils.hpp"
using namespace gd;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

#include <urlmon.h>
#pragma comment (lib, "urlmon.lib")

void CustomBackground::onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
    std::vector<char>* responseData = response->getResponseData();
    std::string responseString(responseData->begin(), responseData->end());
    if (responseString == "0") return;
    // URLDownloadToFile returns S_OK on success
    if (S_OK == URLDownloadToFile(NULL, responseString.c_str(), "gtps\\Resources\\UserContent\\.CustomBackground", 0, NULL))
    {
        CCTextureCache::sharedTextureCache()->reloadTexture(".CustomBackground");
        CCSprite* bg = ModUtils::createSprite(".CustomBackground");
        bg->setAnchorPoint(CCPoint());
        bg->setScaleX(CCDirector::sharedDirector()->getWinSize().width / bg->getContentSize().width);
        bg->setScaleY(CCDirector::sharedDirector()->getWinSize().height / bg->getContentSize().height);
        toAdd->addChild(bg, 0, 5931);
        if (strstr(responseString.c_str(), "#overlay")) bg->setZOrder(6);
    }
    else
    {
        AchievementNotifier::sharedState()->notifyAchievement("Custom Background", "Failed download Custom background.\n", "deleteFilter_none_001.png", true);
    }
}
void CustomBackground::setTargetLayer(CCLayer* layer) {
    toAdd = layer;
}

bool CustomBackgroundPopup::init() {
    if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);

    m_pLayer = CCLayer::create();
    this->addChild(m_pLayer);

    m_pButtonMenu = CCMenu::create();
    m_pLayer->addChild(m_pButtonMenu);

    auto bg = CCScale9Sprite::create("square01_001.png");
    bg->setContentSize({ 360.0f, 260.0f });
    m_pButtonMenu->addChild(bg);

    auto Title = CCLabelBMFont::create("Custom Background", "goldFont.fnt");
    Title->setPositionY(105.f);
    //Title->setPositionX(105.f);
    m_pButtonMenu->addChild(Title);

    auto desc = CCLabelBMFont::create("ass", "chatFont.fnt", bg->getContentSize().width - 60);
    desc->setPositionY(80.f);
    //desc->setPositionX(105.f);
    desc->setAnchorPoint({ 0.5, 1.0 });
    desc->setString("You can set custom image to layer that will see other players playin this level... \n \nAdd \"#overlay\" to end of link to make bg zIndex 100 (real overlay feature)");
    m_pButtonMenu->addChild(desc);

    auto btn1Sprite = ButtonSprite::create("Go to adding page", 0, false, "goldFont.fnt", "GJ_button_05.png", 0, 0.6);
    auto btn1 = CCMenuItemSpriteExtra::create(btn1Sprite, this, menu_selector(CustomBackgroundPopup::onBtn1));
    btn1->setPositionY(-88.f);
    //btn1->setPositionX(105.f);
    m_pButtonMenu->addChild(btn1);

    auto btn2Sprite = ButtonSprite::create("Cancel", 0, false, "goldFont.fnt", "GJ_button_06.png", 0, 0.6);
    auto btn2 = CCMenuItemSpriteExtra::create(btn2Sprite, this, menu_selector(CustomBackgroundPopup::onBtn2));
    btn2->setPositionY(-88.f);
    btn2->setPositionX(123.f);
    m_pButtonMenu->addChild(btn2);

    return true;
}
void CustomBackgroundPopup::keyBackClicked() {
    this->setTouchEnabled(false);
    this->setKeypadEnabled(false);
    this->removeMeAndCleanup();
}
void CustomBackgroundPopup::createAndShowMe(CCObject* sneder) {
    this->create()->show();
}
#include "LevelInfoLayerExt.hpp"
void CustomBackgroundPopup::onBtn1(CCObject*) {
    CCApplication::sharedApplication()->openURL(("https://gtps.undo.it/core-modules/CustomBackground/addBg.php?levelID=" + to_string(LevelInfoLayerExt::me->m_pLevel->m_nLevelID)).c_str());
    this->keyBackClicked();
}
void CustomBackgroundPopup::onBtn2(CCObject*) {
    this->keyBackClicked();
}
CustomBackgroundPopup* CustomBackgroundPopup::create() {
    CustomBackgroundPopup* pRet = new CustomBackgroundPopup();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}