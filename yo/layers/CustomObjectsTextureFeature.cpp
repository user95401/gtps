#include "CustomObjectsTextureFeature.hpp"
#include "mod_utils.hpp"
using namespace gd;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

#include "PlayLayerExt.hpp"

#include <urlmon.h>
#pragma comment (lib, "urlmon.lib")

void CustomObjectsTextureFeature::onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {

    std::vector<char>* responseData = response->getResponseData();
    std::string responseString(responseData->begin(), responseData->end());

    CCTextureCache::sharedTextureCache()->reloadTexture("GJ_GameSheet-uhd.png");
   
    if (responseString == "0") return;
    // URLDownloadToFile returns S_OK on success
    if (S_OK == URLDownloadToFile(NULL, responseString.c_str(), "gtps\\Resources\\UserContent\\GJ_GameSheet-uhd.png", 0, NULL))
    {
        CCTextureCache::sharedTextureCache()->reloadTexture("GJ_GameSheet-uhd.png");
        AchievementNotifier::sharedState()->notifyAchievement("Custom Objects Texture", "Downloaded and reloaded Custom Objects Texture.\n", "deleteFilter_none_001.png", true);
    }
    else
    {
        AchievementNotifier::sharedState()->notifyAchievement("Custom Objects Texture", "Failed download Custom Objects Texture.\n", "deleteFilter_none_001.png", true);
    }
}

bool CustomObjectsTextureFeaturePopup::init() {
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

    auto Title = CCLabelBMFont::create("Custom Objects Texture", "goldFont.fnt");
    Title->setPositionY(105.f);
    //Title->setPositionX(105.f);
    m_pButtonMenu->addChild(Title);

    auto desc = CCLabelBMFont::create("ass", "chatFont.fnt", bg->getContentSize().width - 60);
    desc->setPositionY(80.f);
    //desc->setPositionX(105.f);
    desc->setAnchorPoint({ 0.5, 1.0 });
    desc->setString("You can set custom textures of objects that will see other players playin this level!!!! \n \hooly mollly wtf ya?");
    m_pButtonMenu->addChild(desc);

    auto btn1Sprite = ButtonSprite::create("Go to adding page", 0, false, "goldFont.fnt", "GJ_button_05.png", 0, 0.6);
    auto btn1 = CCMenuItemSpriteExtra::create(btn1Sprite, this, menu_selector(CustomObjectsTextureFeaturePopup::onBtn1));
    btn1->setPositionY(-88.f);
    //btn1->setPositionX(105.f);
    m_pButtonMenu->addChild(btn1);

    auto btn2Sprite = ButtonSprite::create("Cancel", 0, false, "goldFont.fnt", "GJ_button_06.png", 0, 0.6);
    auto btn2 = CCMenuItemSpriteExtra::create(btn2Sprite, this, menu_selector(CustomObjectsTextureFeaturePopup::onBtn2));
    btn2->setPositionY(-88.f);
    btn2->setPositionX(123.f);
    m_pButtonMenu->addChild(btn2);

    return true;
}
void CustomObjectsTextureFeaturePopup::keyBackClicked() {
    this->setTouchEnabled(false);
    this->setKeypadEnabled(false);
    this->removeMeAndCleanup();
}
void CustomObjectsTextureFeaturePopup::createAndShowMe(CCObject* sneder) {
    this->create()->show();
}
#include "LevelInfoLayerExt.hpp"
void CustomObjectsTextureFeaturePopup::onBtn1(CCObject*) {
    CCApplication::sharedApplication()->openURL(("https://gtps.undo.it/core-modules/CustomObjectsTextureFeature?levelID=" + to_string(LevelInfoLayerExt::me->m_pLevel->m_nLevelID)).c_str());
    this->keyBackClicked();
}
void CustomObjectsTextureFeaturePopup::onBtn2(CCObject*) {
    this->keyBackClicked();
}
CustomObjectsTextureFeaturePopup* CustomObjectsTextureFeaturePopup::create() {
    CustomObjectsTextureFeaturePopup* pRet = new CustomObjectsTextureFeaturePopup();
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