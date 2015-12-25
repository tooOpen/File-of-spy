///*
// * ReadyScene.cpp
// *
// *  Created on: 2014. 4. 28.
// *      Author: pc
// */
//
//#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/ReadyScene.h"
//#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/StoreScene.h"
//#include "MenuScene.h"
//
//
//#define FIX_POS(_pos,_min,_max)\
//	if(_pos<_min)\
//	_pos = _min; \
//	else if(_pos>_max) \
//	_pos = _max; \
//
//
//ReadyScene::ReadyScene() {
//
//	// TODO Auto-generated constructor stub
//
//}
//
//ReadyScene::~ReadyScene() {
//
//	// TODO Auto-generated destructor stub
//	AudioManager::getAudioManager()->stopSound();
//}
//
//CCScene* ReadyScene::scene() {
//	CCLog("inin");
//	// 'scene' is an autorelease object
//	CCScene *scene = CCScene::create();
//
//	// 'layer' is an autorelease object
//	ReadyScene *layer = ReadyScene::create();
//
//	// add layer as a child to scene
//	scene->addChild(layer);
//
//	// return the scene
//	return scene;
//}
//int g_titleCount = 0;
//int soundCount = 0;
//void ReadyScene::gamemenuCallBack(CCObject* pSender) {
//	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
//	CCMenuItem *item = (CCMenuItem*) pSender;
//	int tag = item->getTag();
//	if(tag==1)
//	{
//		CCScene* rScene = MenuScene::scene();
//			this->removeChild(_title);
//			CCDirector::sharedDirector()->pushScene(rScene);
//	}
//	else if(tag==2)
//	{
//
//	}
//	else
//	{
//		CCScene* rScene = StoreScene::scene();
//		CCDirector::sharedDirector()->replaceScene(rScene);
//	}
//}
//bool ReadyScene::init() {
//
//	this->setTouchEnabled(true);
//	_isplay = false;
//	_transidone = false;
//	_stage  = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameStage");
//	if(g_titleCount==0)
//	{
//		_title = CCSprite::create("gameplay/images/title.png");
//		_title->setPosition(ccp(720/2,1000));
//		this->addChild(_title, 4);
//		g_titleCount++;
//	}
//	this->setKeypadEnabled(true);
//	winsize = CCDirector::sharedDirector()->getWinSize();
//
////	if(_stage==0)
////	{
////	_stagetest = CCSprite::create("gameplay/images/stage1.jpg");
////	}
////	else if(_stage==1)
////	{
////	_stagetest = CCSprite::create("gameplay/images/stage2.jpg");
////	}
////	else if(_stage==2)
////	{
////	_stagetest = CCSprite::create("gameplay/images/stage3.jpg");
////	}
////	_stagetest->setPosition(ccp(720/2,1280/2));
//	//	this->addChild(_stagetest, 2);
//	this->setTouchEnabled(true);
//
//	_totalMoeny = CCLabelTTF::create("", "fonts/carre.ttf", 120);
//		_totalMoeny->setColor(ccc3(0, 0, 0));
//		_totalMoeny->setAnchorPoint(ccp(0,0));
//		_totalMoeny->setPosition(ccp(220,470));
//		_totalMoeny->setVisible(false);
//		this->addChild(_totalMoeny,5);
//		_totalMoeny->retain();
//
//
//	sprite = CCSprite::create("gameplay/images/number.png");
//	_resultNUM1 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
//	_resultNUM2 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
//	_resultNUM3 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
//	_resultNUM4 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
//
//	_resultNUM1->setPosition(ccp(530,730));
//	this->addChild(_resultNUM1,5);
//	_resultNUM1->retain();
//
//	_resultNUM2->setPosition(ccp(410,730));
//	this->addChild(_resultNUM2, 5);
//	_resultNUM2->retain();
//
//	_resultNUM3->setPosition(ccp(290,730));
//	this->addChild(_resultNUM3, 5);
//	_resultNUM3->retain();
//
//	_resultNUM4->setPosition(ccp(170,730));
//	this->addChild(_resultNUM4, 5);
//	_resultNUM4->retain();
//
//	popUpResult();
//
//	_resultRe =CCMenuItemImage::create("gameplay/images/retry.png",
//			"gameplay/images/retryclick.png", this,
//			menu_selector(ReadyScene::gamemenuCallBack));
//	_resultRe->setTag(2);
//	_resultStore =CCMenuItemImage::create("gameplay/images/store.png",
//				"gameplay/images/storeclick.png", this,
//				menu_selector(ReadyScene::gamemenuCallBack));
//	_resultStore->setTag(3);
//
//	_gameResultMenu = CCMenu::create(_resultRe,_resultStore, NULL);
//	_gameResultMenu->setPosition(ccp(360,340));
//	_gameResultMenu->alignItemsHorizontallyWithPadding(70);
//	this->addChild(_gameResultMenu,5);
//	_gameResultMenu->retain();
//
//	_resultBack = CCSprite::create("gameplay/images/result.png");
//	_resultBack->setPosition(ccp(360,640));
//	this->addChild(_resultBack,0);
//
//
//
//
//	_transi = CCSprite::create("common/images/transi.png");
//	_transi->setPosition(ccp(360,640));
//	this->addChild(_transi, 5);
//
//	CCActionInterval* transiAction = CCMoveTo::create(2, ccp(-360,1280/2));
//	CCFiniteTimeAction* action = CCSequence::create(transiAction,CCCallFunc::create(this,callfunc_selector(ReadyScene::activateScene)),NULL);
//	_transi->runAction(action);
//	CCLayer::onEnter();
//	setAccelerometerEnabled(true);
//	if(soundCount==0)
//	AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
//	else
//	AudioManager::getAudioManager()->playSound(SOUND_READYAUDIO_1);
//	return true;
//
//}
//
//void ReadyScene::activateScene()
//{
//	_gamemenuItem = CCMenuItemImage::create("gameplay/images/menuBtn1.png",
//				"gameplay/images/menuBtn2.png", this,
//				menu_selector(ReadyScene::gamemenuCallBack));
//
//	_gamemenuItem->setTag(1);
//	_gameMenu = CCMenu::create(_gamemenuItem, NULL);
//	_gameMenu->setPosition(ccp(360,640));
//	_gameMenu->retain();
//		this->addChild(_gameMenu,3);
//		_transidone = true;
//}
//
// void ReadyScene::keyBackClicked() {
//
//	if(JniHelper::getStaticMethodInfo(t, "com/fexting/spy/FileofSpy","callDialog","()V"))
//									    {
//										  t.env->CallStaticVoidMethod(t.classID, t.methodID);
//										  t.env->DeleteLocalRef(t.classID);
//									    }
// }
//
//
// void ReadyScene::registerWithTouchDispatcher()
// 	{
//	   CCDirector* pDirector = CCDirector::sharedDirector();
//	    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), false);
// 	}
//
// void ReadyScene::onEnter()
// {
//	 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
//	 CCLayer::onEnter();
// }
// void ReadyScene::onExit()
// {
//	 CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//	 CCLayer::onExit();
// }
//
//void ReadyScene::ccTouchesBegan(CCSet *pTouches, CCEvent *event)
//{
//	CCRect temp_rect =_gamemenuItem->boundingBox();
//
//		CCSetIterator it= pTouches->begin();
//			CCTouch *touch=(CCTouch*)(*it);
//			CCPoint location=touch->getLocation();
//		if(temp_rect.containsPoint(location)==false)
//		{
//			CCScene* rScene = PlayScene::scene();
//						this->removeChild(_title);
//						CCDirector::sharedDirector()->pushScene(rScene);
//		}
//}
//void ReadyScene::ccTouchEnded(CCTouch *ptouch,CCEvent *event)
//{
//	if(!_isplay&&_transidone)
//	{
//	AudioManager::getAudioManager()->stopSound();
//	AudioManager::getAudioManager()->playSound(SOUND_PALYAUDIO_1);
//	_isplay = true;
//	soundCount++;
//	}
//}
//void ReadyScene::ccTouchMoved(CCTouch *ptouch,CCEvent *event)
//{
//
//}
//void ReadyScene::ccTouchCancelled(CCTouch *ptouch,CCEvent *event)
//{
//
//}
//std::string addComma(int value)
//{
//	  std::string result;
//	  int cnt = 0;
//	  do
//	  {
//		  result.insert(0, 1, char('0' + value % 10));
//		  value /= 10;
//	    if (++cnt == 3 && value)
//	    {
//	    	result.insert(0, 1, ',');
//	      cnt = 0;
//	    }
//	  } while (value);
//	  return result;
//
//}
//void ReadyScene::popUpResult()
//{
//	int first;
//	int second;
//	int third;
//	int fourth;
//	int value = 1857;
//	_totalMoeny->setString(addComma(value).c_str());
//	fourth = value/1000;
//	value -=fourth*1000;
//	third = value/100;
//	value -=third*100;
//	second = value/10;
//	value -=second*10;
//	first = value;
//
//	_resultNUM1->runAction(resultAni(++first));
//	_resultNUM2->runAction(resultAni(++second));
//	_resultNUM3->runAction(resultAni(++third));
//	_resultNUM4->runAction(resultAni(++fourth));
//
//	_totalMoeny->setVisible(true);
//
//}
//void ReadyScene::ccTouchBegan(CCTouch *ptouch,CCEvent *event)
//{
//
//}
//CCAnimate* ReadyScene::resultAni(int value)
//{
//	CCAnimation* animation = CCAnimation::create();
//	animation->setDelayPerUnit(.2);
//
//	for(int i=0;i<value;i++)
//	{
//		animation->addSpriteFrameWithTexture(sprite->getTexture(),CCRectMake(120*i,0,120,90));
//	}
//	CCAnimate* animate = CCAnimate::create(animation);
//	return animate;
//}
//
//
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//void Java_com_fexting_spy_FileofSpy_exitGame(JNIEnv* env, jobject thisObj) {
//	CCLog("inin");
//	CCDirector::sharedDirector()->end();
//}
//
//#ifdef __cplusplus
//}
//#endif
//
//
//
