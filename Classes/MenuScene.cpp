/*
 * MenuScene.cpp
 *
 *  Created on: 2014. 4. 28.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/MenuScene.h"
#include "StoreScene.h"
#include "ReadyScene.h"
using namespace extension;

CCScene* MenuScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MenuScene::init() {
	this->setKeypadEnabled(true);
	_volume = CCUserDefault::sharedUserDefault()->getIntegerForKey("SFXvolume",10);
	_availableStage = CCUserDefault::sharedUserDefault()->getIntegerForKey("availableStage");
	_state = 0;
	_menuframe = CCSprite::create("mainmenu/images/menuPda2.png");
	_menuframe->setPosition(ccp(360,640));
	this->addChild(_menuframe, 1);

	_spymap = CCSprite::create("mainmenu/images/stageback.png");
	_spymap->setPosition(ccp(720/2,850));
	_spymap->retain();


	_menuBack = CCSprite::create("mainmenu/images/menuBack.png");
	_menuBack->setPosition(ccp(360,640));
	this->addChild(_menuBack ,0);


	_stageArrow = CCSprite::create("mainmenu/images/arrow.png");
	_stageArrow->setPosition(CCPointZero);
	_stageArrow->setVisible(false);
	this->addChild(_stageArrow,5);
	_stageArrow->retain();

	_gamemapItem = CCMenuItemImage::create("mainmenu/images/stageBtn1.png",
			"mainmenu/images/stageBtn2.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_gamemapItem->setPosition(ccp(200,400));
	_gamemapItem->setTag(1);
	//_gamemapItem->retain();

	_gamestoreItem = CCMenuItemImage::create("mainmenu/images/storeBtn1.png",
			"mainmenu/images/storeBtn2.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_gamestoreItem->setTag(2);
	_gamestoreItem->setPosition(ccp(520,400));
	//_gamestoreItem->retain();

	_gameoptionItem = CCMenuItemImage::create("mainmenu/images/settingBtn1.png",
			"mainmenu/images/settingBtn2.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_gameoptionItem->setTag(3);
	_gameoptionItem->setPosition(ccp(200,50));
	//_gameoptionItem->retain();

	_snsTwitterItem = CCMenuItemImage::create("mainmenu/images/twitter1.png",
			"mainmenu/images/twitter2.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_snsTwitterItem->setTag(4);
	_snsTwitterItem->setPosition(ccp(450,-30));


	_snsFacebookItem = CCMenuItemImage::create("mainmenu/images/facebook1.png",
			"mainmenu/images/facebook2.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_snsFacebookItem->setTag(5);
	_snsFacebookItem->setPosition(ccp(610,-30));

	_gameMenu = CCMenu::create(_gamemapItem, _gamestoreItem,_gameoptionItem,
			_snsFacebookItem,_snsTwitterItem,NULL);

	_gameMenu->setPosition(ccp(0,640));
	_gameMenu->retain();
	//_gameMenu->alignItemsHorizontallyWithPadding(60.0f);
	this->addChild(_gameMenu, 2);


	_gameStage1 = CCMenuItemImage::create("mainmenu/images/stage11.png",
			"mainmenu/images/stage12.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_gameStage1->setTag(6);
	_gameStage1->retain();
	_gameStage1->setPosition(ccp(167,320));

	_gameStage2 = CCMenuItemImage::create("mainmenu/images/stage21.png",
			"mainmenu/images/stage22.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_gameStage2->setTag(7);
	_gameStage2->retain();
	_gameStage2->setPosition(ccp(362,320));

	_gameStage3 = CCMenuItemImage::create("mainmenu/images/stage31.png",
			"mainmenu/images/stage32.png", this,
			menu_selector(MenuScene::gameMenuClick));
	_gameStage3->setTag(8);
	_gameStage3->retain();
	_gameStage3->setPosition(ccp(562,320));

	_stageMenu = CCMenu::create(_gameStage1, _gameStage2, _gameStage3,
				NULL);

	_stageMenu->setPosition(ccp(0,500));
	_stageMenu->retain();



	_volumeSlider = CCControlSlider::create("mainmenu/images/sliderTrack2.png",
			"mainmenu/images/sliderProgress2.png",
			"mainmenu/images/sliderThumb.png");
	_volumeSlider->setMinimumValue(0.0f);
	_volumeSlider->setMaximumValue(10.0f);

	_volumeSlider->setValue(_volume);////////////////
	_volumeSlider->setPosition(ccp(360,840));
	_volumeSlider->addTargetWithActionForControlEvents(this,
			cccontrol_selector(MenuScene::sliderValuechange),
			CCControlEventValueChanged);
	_volumeSlider->setScale(3.0f);
	_volumeSlider->retain();

	_volumeSet = CCLabelTTF::create("SFX Volume", "fonts/MamaPunch.ttf", 60);
	_volumeSet->setColor(ccc3(255, 255, 255));
		_volumeSet->setAnchorPoint(ccp(0,0.5));
		_volumeSet->setPosition(ccp(150,950));
		_volumeSet->setVisible(false);
		_volumeSet->retain();
		this->addChild(_volumeSet, 4);

	return true;

}
void MenuScene::gameMenuClick(CCObject* pSender) { // 게임메뉴 클릭 시
	CCMenuItem *item = (CCMenuItem*) pSender;
	int tag = item->getTag();
	int _stage = 0;
	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
	if(tag==1) // map btn
	{
		//this->removeChild(_gameMenu);
		_gameMenu->setEnabled(false);
		_gameMenu->setVisible(false);
		_state = 1;
		this->addChild(_spymap, 3);
		this->addChild(_stageMenu, 4);
//		if (_availableStage == 0) /// apply images
//		{
//			_gameStage2->setNormalImage(CCSprite::create("mainmenu/images/stage2lock.png"));
//			_gameStage2->setEnabled(false);
//			_gameStage3->setNormalImage(CCSprite::create("mainmenu/images/stage3lock.png"));
//			_gameStage3->setEnabled(false);
//		}
//		else if (_availableStage == 1)
//		{
//			_gameStage3->setNormalImage(CCSprite::create("mainmenu/images/stage3lock.png"));
//			_gameStage3->setEnabled(false);
//		}
//		else if (_availableStage == 2)
//		{
//			//nothing
//		}

		_stage  = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameStage");
		if(_stage ==0)
			_stageArrow->setPosition(ccp(160,590));
		else if(_stage ==1)
			_stageArrow->setPosition(ccp(360,590));
		else if(_stage ==2)
			_stageArrow->setPosition(ccp(560,590));
		_stageArrow->setVisible(true);
	}
	else if(tag==2) //store btn
		{
		_state = 2;
		CCScene* rScene = StoreScene::scene();
		CCDirector::sharedDirector()->pushScene(rScene);
		}
	else if(tag==3)  // option btn
	{
		_gameMenu->setEnabled(false);
		_gameMenu->setVisible(false);
		_state = 3;
		this->addChild(_volumeSlider, 3);
		_volumeSet->setVisible(true);
	}
	else if(tag==4)
	{
		if(JniHelper::getStaticMethodInfo(t, "com/fexting/spy/FileofSpy","integrateTwitter","()V"))
											    {
												  t.env->CallStaticVoidMethod(t.classID, t.methodID);
												  t.env->DeleteLocalRef(t.classID);
											    }
	}
	else if(tag==5)
	{
		if(JniHelper::getStaticMethodInfo(t, "com/fexting/spy/FileofSpy","integrateFacebook","()V"))
											    {
												  t.env->CallStaticVoidMethod(t.classID, t.methodID);
												  t.env->DeleteLocalRef(t.classID);
											    }
	}
	else if(tag==6)
		{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("gameStage",0);
		CCScene* reScene = PlayScene::scene();
		CCDirector::sharedDirector()->replaceScene(reScene);
		}
	else if(tag==7)
		{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("gameStage",1);
		CCScene* reScene = PlayScene::scene();
		CCDirector::sharedDirector()->replaceScene(reScene);
		}
	else if(tag==8)
		{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("gameStage",2);
		CCScene* reScene = PlayScene::scene();
		CCDirector::sharedDirector()->replaceScene(reScene);
		}
}
void MenuScene::sliderValuechange(CCObject* sender,
	CCControlEvent controlEvent) {
	CCControlSlider* pSlider = (CCControlSlider*) sender;
	_volume = pSlider->getValue();

}
void MenuScene::backtoGameAction(float t)
{
	if(_menuframe->getPositionY()>-360)
		{
		    CCActionInterval* transiAction = CCMoveTo::create(2,ccp(360,-350));
			_menuframe->runAction(transiAction);
		    CCActionInterval* transiActionMenu = CCMoveTo::create(2,ccp(0,-350));
			_gameMenu->runAction(transiActionMenu);

		}else
		{
			unschedule(schedule_selector(MenuScene::backtoGameAction));
			CCDirector::sharedDirector()->popScene();
		}
}

void MenuScene::keyBackClicked() {

	switch (_state) {
	case 0:
		 this->schedule(schedule_selector(MenuScene::backtoGameAction),0.2f);
	//	CCDirector::sharedDirector()->popScene();
		break;
	case 1: // map btn
		this->removeChild(_spymap); //visible
		this->removeChild(_stageMenu);
		//this->addChild(_gameMenu, 2);
		_gameMenu->setEnabled(true);
		_gameMenu->setVisible(true);
		_stageArrow->setVisible(false);
		_state = 0;
		break;
	case 2: //store btn
		CCDirector::sharedDirector()->popScene();
		break;
	case 3: // option btn
		CCUserDefault::sharedUserDefault()->setIntegerForKey("SFXvolume",_volume);
		AudioManager::getAudioManager()->setSFXvolume(_volume);
		this->removeChild(_volumeSlider);
		_volumeSet->setVisible(false);
		//this->addChild(_gameMenu, 2);
		_gameMenu->setEnabled(true);
	    _gameMenu->setVisible(true);
		_state = 0;
		break;
	default:
		break;
	}
	//CCDirector::sharedDirector()->end();
}
MenuScene::MenuScene() {
	// TODO Auto-generated constructor stub

}

MenuScene::~MenuScene() {
	// TODO Auto-generated destructor stub
}

