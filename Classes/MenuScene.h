/*
 * MenuScene.h
 *
 *  Created on: 2014. 4. 28.
 *      Author: pc
 */
#include "cocos2d.h"
#include "Manager/AudioManager.h"
#include "cocos-ext.h"
#include "platform/android/jni/JniHelper.h"
#include "PlayScene.h"
using namespace cocos2d;

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

class MenuScene :public CCLayer{
public:
	MenuScene();
	virtual ~MenuScene();

	virtual bool init();
			static CCScene* scene();
			int _state; //0-menu 1-map 2-store 3-option
			int _volume;
			int _availableStage;

			JniMethodInfo t;

			CREATE_FUNC(MenuScene);
			CCSprite* _stageArrow;
			CCSprite* _menuframe;
			CCSprite* _spymap;
			CCSprite* _menuBack;

			CCMenuItemImage* _snsTwitterItem;
			CCMenuItemImage* _snsFacebookItem;
			CCMenuItemImage* _gamestoreItem;
			CCMenuItemImage* _gameoptionItem;
			CCMenuItemImage* _gamemapItem;
			CCMenu* _gameMenu;
			CCMenuItemImage* _gameStage1;
			CCMenuItemImage* _gameStage2;
			CCMenuItemImage* _gameStage3;
			CCMenu* _stageMenu;

			CCLabelTTF* _volumeSet;

			extension::CCControlSlider* _volumeSlider;
			virtual void keyBackClicked();	//adroid backkey
			void gameMenuClick(CCObject* pSender);
			void sliderValuechange(CCObject* sender,extension::CCControlEvent controlEvent);
			void backtoGameAction(float t);
//			void gametempCallBack(CCObject* pSender);
};

#endif
