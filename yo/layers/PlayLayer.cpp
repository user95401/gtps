#include "PlayLayer.hpp"
#include "ObjectsController.hpp"
#include "SoundRelated.hpp"
bool MusicStarted;

#include "SimpleIni.h"

PlayLayer* (__thiscall* PlayLayer_create)(GJGameLevel*);//0x1fb6d0
PlayLayer* __fastcall PlayLayer_create_H(GJGameLevel* level) {
    bool forcecursorgv = (level->m_sLevelName == std::string("isPreviewThing6380"));
    if (forcecursorgv) GameManager::sharedState()->setGameVariable("0024", true);
    else GameManager::sharedState()->setGameVariable("0024", GameManager::sharedState()->getGameVariable("56738926750"));
    //CCMessageBox(std::to_string(forcecursorgv).c_str(), "forcecursorgv");
    //CCMessageBox(std::to_string(GameManager::sharedState()->getGameVariable("0024")).c_str(), "0024");
    //CCMessageBox(std::to_string(GameManager::sharedState()->getGameVariable("56738926750")).c_str(), "56738926750");
    if (level->m_eLevelType == GJLevelType::kGJLevelTypeLocal) {
        CSimpleIniA level_creator_list;
        level_creator_list.LoadFile("gtps/level_creator_list.ini");
        if(level_creator_list.GetSection(level->m_sLevelName.c_str()))
        level->m_sCreatorName = std::string(level_creator_list.GetValue(level->m_sLevelName.c_str(), "name"));
    }

    PlayLayer* _PlayLayer = PlayLayer_create(level);
    if (rand() % 3 == 2 && !GameManager::sharedState()->getGameVariable("75821")) {
        //_PlayLayer->removeAllChildren();
        CCSprite* randomBackGround = ModUtils::createSprite(ModUtils::getRandomFileNameFromDir("gtps/Resources/randomBackGrounds", "emptyGlow.png").c_str());
        randomBackGround->setAnchorPoint(CCPoint());
        randomBackGround->setScaleX(CCDirector::sharedDirector()->getWinSize().width / randomBackGround->getContentSize().width);
        randomBackGround->setScaleY(CCDirector::sharedDirector()->getWinSize().height / randomBackGround->getContentSize().height);
        _PlayLayer->addChild(randomBackGround, 0, 57281);
        //_PlayLayer->m_pObjectLayer->setZOrder(4);
    }
    return _PlayLayer;
}

bool(__thiscall* PlayLayer_init)(PlayLayerExt*, GJGameLevel*);//0x1fb780
bool __fastcall PlayLayer_init_H(PlayLayerExt* self, int edx, GJGameLevel* level) {
    MusicStarted = false;
    if (!PlayLayer_init(self, level)) return false;
    twoTimesLayerInitHookEscape(self);
    PlayLayerExt::me = self;
    //"bad play quality", "542984", "it makes Playlayer <cr>worse</c>"
    if (GameManager::sharedState()->getGameVariable("542984")) {
        self->runAction(CCShaky3D::create(0.1, CCSizeMake(1, 1), 1, false));
        self->m_pObjectLayer->setZOrder(8);
        self->unk370->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pBatchNodeAddPlayer->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pBatchNodeAddGlow->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pEffectBatchNodeAdd->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pEffectBatchNode->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_playerGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_robotJumpParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_shipBoostParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_vehicleGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_waveTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_regularTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_playerGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_robotJumpParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_shipBoostParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_vehicleGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_waveTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_regularTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
    }
    //"default blend func for trail", "65372"
    if (GameManager::sharedState()->getGameVariable("65372")) {
        self->m_pPlayer1->m_regularTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_regularTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
    }
    //"default blend func\nfor all of player", "923956", "most of player things like trail, ghost trail, wave trail have deafult sprite blending"
    if (GameManager::sharedState()->getGameVariable("923956")) {
        self->m_pBatchNodeAddPlayer->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_playerGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_robotJumpParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_shipBoostParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_vehicleGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_waveTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer1->m_regularTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_playerGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_robotJumpParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_shipBoostParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_vehicleGroundParticles->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_waveTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
        self->m_pPlayer2->m_regularTrail->setBlendFunc(CCSprite::create()->getBlendFunc());
    }
    return true;
}

inline void(__thiscall* PlayLayer_updateProgressbar)(PlayLayerExt*);//0x208020
void __fastcall PlayLayer_updateProgressbar_H(PlayLayerExt* self) {
    PlayLayer_updateProgressbar(self);
    PlayLayerExt::me = self;
    ObjectsController::updateProgressbar(self);
    //shit
    if (GameManager::sharedState()->getGameVariable("75649")  &&
        (self->m_pPlayer1->isCube() || self->m_pPlayer1->m_isRobot) &&
        !self->m_bIsDualMode &&
        !self->m_cameraXLocked &&
        !self->m_cameraYLocked &&
        !self->m_isDead &&
        self->m_pPlayer1->m_position.y > 104) {
        self->m_cameraY = self->m_pPlayer1->m_position.y - 120;
        self->m_cameraX = self->m_pPlayer1->m_position.x - 80;
    }
    //very shit
    if (self->m_level->m_sLevelName == "isPreviewThing6380") {
        self->m_uiLayer->setPosition({9999, 9999});
        self->m_isTestMode = true;
        self->m_isPlaybackMode = true;
        //self->m_percentLabel->setString(to_string(self->m_pPlayer1->m_position.y).c_str());
        if (self->m_pPlayer1->m_position.y > 2700.f) self->m_pPlayer1->flipGravity(false, false);
    }
}

class PlayNormally : public FLAlertLayer {
    virtual bool init() {
        if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);

        m_pLayer = CCLayer::create();
        this->addChild(m_pLayer);

        this->addChild(CCLayerGradient::create({ 1, 1, 1, 220 }, { 1, 1, 1, 10 }), -10);

        m_pButtonMenu = CCMenu::create();
        m_pLayer->addChild(m_pButtonMenu);
        m_pButtonMenu->addChild(ModUtils::createSprite("killaCube.png"));
        m_pButtonMenu->addChild(CCLabelTTF::create((getMsg() + "\n\n\n\n\n").c_str(), "Comic Sans MS", 22.f));

        return true;
    }
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
        this->keyBackClicked();
    }
    virtual void keyDown(cocos2d::enumKeyCodes key) {
        this->keyBackClicked();
    }
    virtual void keyBackClicked() {
        this->setTouchEnabled(false);
        this->setKeypadEnabled(false);
        this->removeMeAndCleanup();

        PlayLayerExt::me->resetLevel();
    }
public:
    CREATE_FUNC(PlayNormally);
    string getMsg()
    {
        switch (rand() % 10)
        {
        case 0:
            return "Hey! focus, I'm fukin tired of crashing >:(";
        case 1:
            return  "Are you ok?";
        case 2:
            return  "Play normally, noob :p";
        case 3:
            return  "wtf";
        case 4:
            return  "Strain your limbs, you unskilled man!";
        case 5:
            return  "Why did I program this...";
        case 6:
            return  "I believe in you!..";
        case 7:
            return  "You can do it!";
        case 8:
            return  "Hey! focus, I'm fukin tired of crashing >:(";
        case 9:
            return  "Hey! focus, I'm fukin tired of crashing >:(";
        case 10:
            return  "Strain your limbs, you unskilled man!";
        default:
            return "Hey! focus, I'm fukin tired of crashing >:(";
        }
    }
};

inline void(__thiscall* PlayLayer_resetLevel)(PlayLayerExt*);//0x20bf00
void __fastcall PlayLayer_resetLevel_H(PlayLayerExt* self) {
    //"Disable PlayNormally thing", "965784", "layer that shows somtimes on reset level"
    if (!GameManager::sharedState()->getGameVariable("965784")) 
        if (rand() % 5 == 1 && self->m_currentAttempt > 5 && !self->m_isPracticeMode && self->m_isDead) 
            return PlayNormally::create()->show();
    PlayLayer_resetLevel(self);
    PlayLayerExt::me = self;
    ObjectsController::resetLevel(self);

    self->m_startCameraAtCorner = true;
}

inline void(__thiscall* PlayLayer_levelComplete)(PlayLayerExt*);//0x1fd3d0
void __fastcall PlayLayer_levelComplete_H(PlayLayerExt* self) {
    if (self->m_level->m_sLevelName == "isPreviewThing6380") return PlayLayer_resetLevel(PlayLayerExt::me);
    PlayLayer_levelComplete(self);
    //completeBg
    self->removeChildByTag(78630);
    auto completeBg = ModUtils::createSprite("completeBg.png");
    completeBg->setAnchorPoint(CCPoint());
    completeBg->setScaleX(CCDirector::sharedDirector()->getWinSize().width / completeBg->getContentSize().width);
    completeBg->setScaleY(CCDirector::sharedDirector()->getWinSize().height / completeBg->getContentSize().height);
    completeBg->runAction(CCSequence::create(CCMoveTo::create(0.f, { 0.f, -100.f }), CCMoveTo::create(3.f, { 0.f, 0.f }), CCDelayTime::create(3.f), CCMoveTo::create(3.f, { 0.f, -100.f })));
    self->addChild(completeBg, 10, 78630);
}
inline void(__thiscall* PlayLayer_startMusic)(PlayLayerExt*);//0x20C8F0
void __fastcall PlayLayer_startMusic_H(PlayLayerExt* self) {
    if (self->m_level->m_sLevelName == "isPreviewThing6380")
        if (MusicStarted) return;
        else {
            MusicStarted = true;
            return GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
        }
    MusicStarted = false;
    PlayLayer_startMusic(self);
}

void PlayLayerExt::CreateHooks() {
    HOOK(base + 0x1fb6d0, PlayLayer_create);
    HOOK(base + 0x1fb780, PlayLayer_init);
    HOOK(base + 0x208020, PlayLayer_updateProgressbar);
    HOOK(base + 0x1fd3d0, PlayLayer_levelComplete);
    HOOK(base + 0x20C8F0, PlayLayer_startMusic);
    HOOK(base + 0x20bf00, PlayLayer_resetLevel);
}