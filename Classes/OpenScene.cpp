/*
 * OpenScene.cpp
 *
 *  Created on: 2014. 4. 28.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/OpenScene.h"
#include "ReadyScene.h"
#include "PlayScene.h"
#include "Manager/AudioManager.h"
CCScene* OpenScene::scene()
{
	 // 'scene' is an autorelease object
	    CCScene *scene = CCScene::create();

	    // 'layer' is an autorelease object
	    OpenScene *layer = OpenScene::create();

	    // add layer as a child to scene
	    scene->addChild(layer);

	    // return the scene
	    return scene;
}





bool OpenScene::init()
{

	_one = false;
	 _logo = CCSprite::create("common/images/logo.png");
	 _logo->setPosition(ccp(720/2,1280/2));
	    this->addChild(_logo,3);
	 _swipe = CCSprite::create("common/images/blood.png");
	 _swipe->setAnchorPoint(ccp(0.5,0.0));
	 _swipe->setPosition(ccp(360,1280));
	 this->addChild(_swipe,3);
	 CCActionInterval* transiActionblood = CCMoveBy::create(2.0,ccp(0,-1200));
	 	 _swipe->runAction(transiActionblood);
	    this->schedule(schedule_selector(OpenScene::logotime),1.0f,20,2.0f);

	    _transi = CCSprite::create("common/images/transi.png");
	    	_transi->setPosition(ccp(720+360,640));
	    	this->addChild(_transi, 3);
	    	_transi->retain();
AudioManager::getAudioManager()->playSound(SOUND_INTRO);
	return  true;

}


void OpenScene::logotime(float f)
{
	if (!_one) {
		CCActionInterval* transiAction = CCMoveTo::create(2, ccp(360,640));

		_transi->runAction(transiAction);
		_one = true;
	}
	if (_transi->getPositionX() <= 360) {
		AudioManager::getAudioManager()->stopSound();
		CCScene* rScene = PlayScene::scene();
		CCDirector::sharedDirector()->replaceScene(rScene);
	}
}


OpenScene::OpenScene() {
	// TODO Auto-generated constructor stub

}

OpenScene::~OpenScene() {
	// TODO Auto-generated destructor stub
}

