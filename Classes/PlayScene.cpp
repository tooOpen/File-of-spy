/*
* PlayScene.cpp
*
*  Created on: 2014. 5. 6.
*      Author: pym

*/


#include "PlayScene.h"
#include "GameLevel.h"
#include "GameState.h"
#include "Enemy.h"
#include "PopLayer.h"
#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/StoreScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/manager/ItemManager.h"

#define FIX_POS(_pos,_min,_max)\
	if(_pos<_min)\
	_pos = _min; \
   else if(_pos>_max) \
   _pos = _max; \

#define DistMax 100
#define Z_UI 3
#define Z_bgraund 0
#define Z_Enemy 1
#define Z_player 2
#define Z_effect 4
using namespace cocos2d;
using namespace CocosDenshion;
PlayScene::PlayScene() {
	// TODO Auto-generated constructor stub
}
PlayScene::~PlayScene() {
	// TODO Auto-generated destructor stub
}
CCScene* PlayScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	// 'layer' is an autorelease object
	PlayScene *layer = PlayScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

int soundCount = 0;
void PlayScene::gamemenuCallBack(CCObject* pSender) {
	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
	CCMenuItem *item = (CCMenuItem*) pSender;
	int tag = item->getTag();
	if(tag==1)
	{
		CCScene* rScene = MenuScene::scene();
			CCDirector::sharedDirector()->pushScene(rScene);
	}
	else if(tag==2)
	{
		restart();
	}
	else
	{
		CCScene* rScene = StoreScene::scene();
		CCDirector::sharedDirector()->replaceScene(rScene);
	}
}
bool PlayScene::init() {
	////
	_nowMoeny = 0;
	_stage  = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameStage");

	_resultcount = 0;
	_isplay = false;
	_transidone = false;
	_stage  = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameStage");
				_title = CCSprite::create("gameplay/images/title.png");
			_title->setPosition(ccp(720/2,1000));
			if(_stage==0)
			{
				_title->setColor(ccc3(150,150,150));
			}
			this->addChild(_title, 4);
			_title->retain();


	this->setKeypadEnabled(true);

	_totalMoeny = CCLabelTTF::create("", "fonts/carre.ttf", 120);
			_totalMoeny->setColor(ccc3(0, 0, 0));
			_totalMoeny->setAnchorPoint(ccp(0.5,0.5));
			_totalMoeny->setPosition(ccp(350,520));
			_totalMoeny->setVisible(false);
			this->addChild(_totalMoeny,6);
		//	_totalMoeny->retain();

	sprite = CCSprite::create("gameplay/images/number.png");
	sprite->retain();
		_resultNUM1 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
		_resultNUM2 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
		_resultNUM3 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
		_resultNUM4 = CCSprite::createWithTexture(sprite->getTexture(),CCRectMake(0,0,120,90));
		_resultNUM1->setPosition(ccp(530,730));
		_resultNUM1->setVisible(false);
		this->addChild(_resultNUM1,6);
		_resultNUM1->retain();

		_resultNUM2->setPosition(ccp(410,730));
		_resultNUM2->setVisible(false);
		this->addChild(_resultNUM2, 6);
		_resultNUM2->retain();

		_resultNUM3->setPosition(ccp(290,730));
		_resultNUM3->setVisible(false);
		this->addChild(_resultNUM3, 6);
		_resultNUM3->retain();

		_resultNUM4->setPosition(ccp(170,730));
		_resultNUM4->setVisible(false);
		this->addChild(_resultNUM4, 6);
		_resultNUM4->retain();


		_resultRe =CCMenuItemImage::create("gameplay/images/retry.png",
					"gameplay/images/retryclick.png", this,
					menu_selector(PlayScene::gamemenuCallBack));
			_resultRe->setTag(2);

			_resultStore =CCMenuItemImage::create("gameplay/images/store.png",
						"gameplay/images/storeclick.png", this,
						menu_selector(PlayScene::gamemenuCallBack));
			_resultStore->setTag(3);

			_gameResultMenu = CCMenu::create(_resultRe,_resultStore, NULL);
			_gameResultMenu->setPosition(ccp(360,340));
			_gameResultMenu->alignItemsHorizontallyWithPadding(70);
			_gameResultMenu->setVisible(false);
			_gameResultMenu->setEnabled(false);
			this->addChild(_gameResultMenu,6);
			_gameResultMenu->retain();


			_resultBack = CCSprite::create("gameplay/images/result.png");
			_resultBack->setPosition(ccp(360,640));
			_resultBack->setVisible(false);
			this->addChild(_resultBack,5);




			_transi = CCSprite::create("common/images/transi.png");
			_transi->setPosition(ccp(360,640));
			this->addChild(_transi, 5);

			CCActionInterval* transiAction = CCMoveTo::create(2, ccp(-360,1280/2));
			CCFiniteTimeAction* action = CCSequence::create(transiAction,CCCallFunc::create(this,callfunc_selector(PlayScene::activateScene)),NULL);
			_transi->runAction(action);
			//CCLayer::onEnter();
			if(soundCount==0)
			AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
			else
			AudioManager::getAudioManager()->playSound(SOUND_READYAUDIO);

////////////////////////////////////////////////////////////////////////////////////////////
	projectiles=NULL;
	projectiles=CCArray::create();
	projectiles->retain();
	enemy_temp=new list<Enemy*>;
	enemys=NULL;
	enemys=CCArray::create(); //에너미
	sectors=NULL;
	sectors=CCArray::create();
	sectors->retain();
	//logic init
	isphase1set=true;
	isphase2set=true;
	isphase3set=true;
	isphase4set=true;
	setAccelerometerEnabled(true); //자이로
	this->setTouchEnabled(true);//터치 활성화
	phase=-2;
	scr_speed=0;////화면 카메라 스피드 y축
	curdist=0;//현재 거리
	money=0;
	//player
	if(ItemManager::getItemManager()->getArmorItem()==-1)
	{
		playr_hp=0;
	}
	else
	{
		playr_hp=ItemManager::getItemManager()->getArmorItem();
	}
	//방패 값
	if(ItemManager::getItemManager()->getGunItem()==-1)
	{
		shot_damge=1;
	}
	else
	{
		shot_damge=ItemManager::getItemManager()->getGunItem();//총 대미지
	}
	if(ItemManager::getItemManager()->getBagItem()==-1)
		{
			max_file=10;
		}
		else
		{
			max_file=ItemManager::getItemManager()->getBagItem();//총 대미지
		}

	Acc_left=true;
	Acc_right=true;
	left_switch=true;
	right_switch=true;
	/////player
	player=CCSprite::create("gameplay/images/l_rgb_0_0.png");
	player->setPosition(ccp(720/2,1280+120));
	this->addChild(player,Z_player);
	CCAnimation * playerAni=CCAnimation::create();
	playerAni->setDelayPerUnit(0.3);
	playerAni->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_0.png");
	playerAni->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_1.png");
	CCAnimate *playerAnimate=CCAnimate::create(playerAni);
	playerAnimate->setDuration(0.3);
	CCAction *player_rep =CCRepeatForever::create(playerAnimate);
	player->runAction(player_rep);
	//stage
	char str[100]={0};
	GameState::getInstance()->initLevel();
	GameState::getInstance()->setstage(_stage);
	sprintf(str,"gameplay/images/bg_%d.png",GameState::getInstance()->curStageIndex);
	//car


	////ui_set
	/*p_menuimage=CCMenuItemImage::create("gameplay/images/pause1.png",
		"gameplay/images/pause2.png",
		this,
		menu_selector(PlayScene::doPop));

	p_menuimage->setZOrder(Z_UI);
	pause_menu=CCMenu::create(p_menuimage,NULL);
	pause_menu->setPosition(720-50,1280-120);
	pause_menu->alignItemsVertically();
	this->addChild(pause_menu,Z_UI);*/

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(PlayScene::doNotification),
			"notification", NULL);
//
//	back_p_sprite=CCSprite::create("gameplay/images/pauseback1.png");
//	back_p_sprite->setPosition(ccp(720-100,1280-75));
//
//	p_sprite=CCSprite::create("gameplay/images/pausebutton1.png");
//	p_sprite->setPosition(ccp(720-50,1280-65));
//	p_sprite->retain();
	//this->addChild(back_p_sprite,Z_UI);
	//this->addChild(p_sprite,Z_UI);

	//

	level_bkgrnd1=CCSprite::create(str);
	level_bkgrnd1->setPosition(ccp(720/2,1280/2));
	this->addChild(level_bkgrnd1,Z_bgraund);
	level_bkgrnd2= CCSprite::create(str);
	level_bkgrnd2->setPosition(ccp(720/2,level_bkgrnd1->getPositionY()-1280));
	this->addChild(level_bkgrnd2,Z_bgraund);
	_test = CCLabelTTF::create(
		CCString::createWithFormat("%f m", curdist)->getCString(),
		"fonts/MarkerFelt.ttf", 50);
	_test->setColor(ccc3(255, 255, 255));
	_test->setPosition(ccp(300,30));
	this->addChild(_test,Z_UI);
	usb_count=0;
	usbsprite=CCSprite::create("gameplay/images/folder.png");
	usbsprite->setContentSize(CCSize(usbsprite->getContentSize().width/5,usbsprite->getContentSize().height/5));
	//usbsprite->setPosition(ccp(25,1280-120));
	usbsprite->setPosition(ccp(25,1280+60));
	this->addChild(usbsprite,Z_UI);
	usb_text = CCLabelTTF::create(
		CCString::createWithFormat(" X%d", usb_count)->getCString(),
		"fonts/MarkerFelt.ttf", 50);
	usb_text->setColor(ccc3(255, 255, 255));
	usb_text->setPosition(ccp(50+100,1280+80));

	this->addChild(usb_text,Z_UI);
	enemyInit();

	return true;
}
void PlayScene::registerWithTouchDispatcher()
 	{
	   CCDirector* pDirector = CCDirector::sharedDirector();
	    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), false);
 	}
void PlayScene::restart()
{


	_resultcount=0;
	AudioManager::getAudioManager()->stopSound();
	_resultNUM1->setVisible(false);
	_resultNUM2->setVisible(false);
	_resultNUM3->setVisible(false);
	_resultNUM4->setVisible(false);
	_totalMoeny->setVisible(false);
	_gameResultMenu->setVisible(false);
	_gameResultMenu->setEnabled(false);
	_resultBack->setVisible(false);


	_title->setVisible(true);

//   this->getCamera()->setCenterXYZ(0,0,0);
//   this->getCamera()->setEyeXYZ(0, 0, 0);
   projectiles=NULL;
   projectiles=CCArray::create();
   projectiles->retain();
   enemy_temp=NULL;
   enemy_temp=new list<Enemy*>;
   sectors=NULL;
   sectors=CCArray::create();
   sectors->retain();
   //logic init
   isphase1set=true;
   isphase2set=true;
   isphase3set=true;
   isphase4set=true;
   setAccelerometerEnabled(true); //자이로
   this->setTouchEnabled(true);//터치 활성화
   phase=-2;
   scr_speed=0;////화면 카메라 스피드 y축
   curdist=0;//현재 거리
   money=0;
   usb_count=0;
   if(ItemManager::getItemManager()->getArmorItem()==-1)
   {
      playr_hp=0;
   }
   else
   {
      playr_hp=ItemManager::getItemManager()->getArmorItem();
   }
   //방패 값
   if(ItemManager::getItemManager()->getGunItem()==-1)
   {
      shot_damge=1;
   }
   else
   {
      shot_damge=ItemManager::getItemManager()->getGunItem();//총 대미지
   }
   if(ItemManager::getItemManager()->getBagItem()==-1)
   {
      max_file=10;
   }
   else
   {
      max_file=ItemManager::getItemManager()->getBagItem();//총 대미지
   }
   Acc_left=true;
   Acc_right=true;
   left_switch=true;
   right_switch=true;
//   //sprite reset
   player->setPosition(ccp(720/2,1280+120));
   CCAnimation * playerAni=CCAnimation::create();
      playerAni->setDelayPerUnit(0.3);
      playerAni->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_0.png");
      playerAni->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_1.png");
      CCAnimate *playerAnimate=CCAnimate::create(playerAni);
      playerAnimate->setDuration(0.3);
      CCAction *player_rep =CCRepeatForever::create(playerAnimate);
      player->runAction(player_rep);
      level_bkgrnd1->setPosition(ccp(720/2,1280/2));
      level_bkgrnd2->setPosition(ccp(720/2,level_bkgrnd1->getPositionY()-1280));

     // back_p_sprite->setPosition(ccp(720-100,1280-75));
      //p_sprite->setPosition(ccp(720-50,1280-65));
      _test->setPosition(ccp(300,30));
      usbsprite->setPosition(ccp(25,1280+60));
      usb_text->setPosition(ccp(50+100,1280+80));
      this->removeChild(enemy_car);
   enemyInit();
}

void PlayScene::activateScene()
{
	_isplay = true;
	_gamemenuItem = CCMenuItemImage::create("gameplay/images/menuBtn1.png",
				"gameplay/images/menuBtn2.png", this,
				menu_selector(PlayScene::gamemenuCallBack));
	_gamemenuItem->setTag(1);
	_gameMenu = CCMenu::create(_gamemenuItem, NULL);
	_gameMenu->setPosition(ccp(360,640));
	_gameMenu->retain();
		this->addChild(_gameMenu,3);
		_transidone = true;
}


void PlayScene::keyBackClicked() {
	if(JniHelper::getStaticMethodInfo(t, "com/fexting/spy/FileofSpy","callDialog","()V"))
									    {
										  t.env->CallStaticVoidMethod(t.classID, t.methodID);
										  t.env->DeleteLocalRef(t.classID);
									    }

 }


std::string addComma(int value)
{
	  std::string result;
	  int cnt = 0;
	  do
	  {
		  result.insert(0, 1, char('0' + value % 10));
		  value /= 10;
	    if (++cnt == 3 && value)
	    {
	    	result.insert(0, 1, ',');
	      cnt = 0;
	    }
	  } while (value);
	  return result;

}




void PlayScene::popUpResult()
{
	int first;
	int second;
	int third;
	int fourth;
	int now = _nowMoeny;
	int total = money;
	_totalMoeny->setString(addComma(total).c_str());

	fourth = now/1000;
	now -=fourth*1000;
	third = now/100;
	now -=third*100;
	second = now/10;
	now -=second*10;
	first = now;

	_resultBack->setVisible(true);
	_resultNUM1->setVisible(true);
	_resultNUM2->setVisible(true);
	_resultNUM3->setVisible(true);
	_resultNUM4->setVisible(true);

	_gameResultMenu->setEnabled(true);
	_gameResultMenu->setVisible(true);

	_resultNUM1->runAction(resultAni(++first));
	_resultNUM2->runAction(resultAni(++second));
	_resultNUM3->runAction(resultAni(++third));
	_resultNUM4->runAction(resultAni(++fourth));

	_totalMoeny->setVisible(true);

}

CCAnimate* PlayScene::resultAni(int value)
{
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(.2);

	for(int i=0;i<value;i++)
	{
		animation->addSpriteFrameWithTexture(sprite->getTexture(),CCRectMake(120*i,0,120,90));
	}
	CCAnimate* animate = CCAnimate::create(animation);
	return animate;
}

#ifdef __cplusplus
extern "C" {
#endif
void Java_com_fexting_spy_FileofSpy_exitGame(JNIEnv* env, jobject thisObj) {
	CCDirector::sharedDirector()->end();
}

#ifdef __cplusplus
}
#endif






void PlayScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	this->schedule(schedule_selector(PlayScene::update));
}
void PlayScene::onExit()
{
	//////audio seting
	CCLayer::onExit();
}
bool PlayScene::ccTouchBegan(CCTouch *ptouch,CCEvent *event)
{
	if(_isplay)
	{
	//CCSetIterator it= pTouches->begin();
	CCTouch *touch=ptouch;
	CCPoint location=touch->getLocation();
	//CCRect menu=p_sprite->boundingBox();
	if(phase==-2)
	{
		phase=-1;
		_gameMenu->setEnabled(0);
		_gameMenu->setVisible(0);
		_title->setVisible(0);
		AudioManager::getAudioManager()->playEffectAudio(SOUND_CARCOME);

		CCSprite *car=CCSprite::create("gameplay/images/car.png");
			car->setTag(1);
			car->setPosition(ccp(500,1280+(car->getContentSize().height/2)));
			CCActionInterval *car_move=CCMoveBy::create(2,ccp(0,-1280/2-(car->getContentSize().height/2)));
			CCActionInterval *car_move2=car_move->reverse();
			CCFiniteTimeAction *player_visible_phase=CCCallFuncN::create(this,callfuncN_selector(PlayScene::carfunction));
			CCActionInterval *d_time=CCDelayTime::create(1);
			CCFiniteTimeAction *caract=CCSequence::create(car_move,d_time,player_visible_phase,car_move2,player_visible_phase,player_visible_phase,NULL);
			car->runAction(caract);
			car->retain();
			this->addChild(car,Z_Enemy);

	}

//	if(menu.containsPoint(location))
//	{
//		//CCLog("in");
//		doPop();
//	}
	if(phase==0)
	{
		phase=1;
	}
	if(phase==1)
	{
		scr_speed=-5;

	}
	if(phase==4)
	{
		if(projectiles->count()<4)
		{
		AudioManager::getAudioManager()->playEffectAudio(SOUND_SHOT);
		CCParticleSystem *particle2=CCParticleSmoke::create();
		particle2->retain();
		particle2->setTexture(CCTextureCache::sharedTextureCache()->addImage("gameplay/images/ex3.png"));
		particle2->setDuration(0.001f);
		particle2->setLife(1);
		particle2->setLifeVar(1);
		particle2->setTotalParticles(1);
		particle2->setStartColor(ccc4f(0.2,0.2,0.2,0.4));
		particle2->setEndColor(ccc4f(1,1,1,0.4));
		particle2->setStartSize(70);
		particle2->setEndSize(70);
		particle2->setContentSize(CCSize(30,30));
		particle2->setEmissionRate(200);
		particle2->setPosition(player->getPosition());
		particle2->setAutoRemoveOnFinish(true);
		this->addChild(particle2,Z_effect);
		//총알 사운드 추가

		//총알 스프라이트 만들기
		nextProjectile=CCSprite::create("gameplay/images/bullet.png");
		CCPoint my=player->getPosition();
		nextProjectile->setPosition(ccp(my.x,my.y));
		CCPoint shotVector= ccpSub(location,player->getPosition());

		float shootAngle=ccpToAngle(shotVector);
		float coAngle=CC_RADIANS_TO_DEGREES(shootAngle);
		float curAngle=player->getRotation();
		float rotatdiff=270-coAngle;
		if(rotatdiff>180)
		{
			rotatdiff-=360;
		}
		if(rotatdiff<-180)
		{
			rotatdiff+=360;
		}
		nextProjectile->setRotation(rotatdiff);
		this->addChild(nextProjectile,Z_player);
		//포탄 이동
		float delta=1.5f;
		CCPoint normalizedShootVector=ccpNormalize(shotVector);
		CCPoint overshotvector=ccpMult(normalizedShootVector,650);
		CCActionInterval *shotmove=CCMoveBy::create(delta,overshotvector);
		CCFiniteTimeAction *shotfunc=CCCallFuncN::create(this,callfuncN_selector(PlayScene::spriteMoveFinished));
		CCFiniteTimeAction *shotact=CCSequence::create(shotmove,shotfunc,NULL);
		nextProjectile->runAction(shotact);
		nextProjectile->setTag(2);
		projectiles->addObject(nextProjectile);
		}

	}
	}
	return true;
}
void PlayScene::spriteMoveFinished(CCNode *sender)
{
	CCSprite *temp=(CCSprite*)sender;
	this->removeChild(temp);
	projectiles->removeObject(temp);
}
void PlayScene::ccTouchesEnded(CCSet *pTouches, CCEvent *event)
{
	/*if(phase==1)
	{
	scr_speed=0;
	}*/
}

void PlayScene::update(float dt)//충돌체크
{
	if(curdist>101)
	{
		phase=2;
		curdist=100;
	}
	if(curdist<0)
	{
		phase=4;
		curdist=0;
	}
	moveCamera();
	_test->setString(CCString::createWithFormat("%.2f m", curdist)->getCString());
	usb_text->setString(CCString::createWithFormat(" X %d", usb_count)->getCString());
	CCObject *pObj=NULL;
	CCRect player_rect=player->boundingBox();
	CCSprite *enemy_sprite=NULL;
	Enemy *curenemy=NULL;
	CCRect enemy_rect;
	if(enemys==NULL)return;
	int num=0;

	if(phase==1)
	{
		if(isphase1set)
		{
			if(_stage==0)
				AudioManager::getAudioManager()->playSound(SOUND_PALYAUDIO_1);
			else if(_stage==1)
				AudioManager::getAudioManager()->playSound(SOUND_PALYAUDIO_2);
			else if(_stage==2)
				AudioManager::getAudioManager()->playSound(SOUND_PALYAUDIO_3);
			isphase1set=false;
		}

		list<Enemy*>::iterator iter;
		for(iter=enemy_temp->begin();iter!=enemy_temp->end();iter++)
		{
			Enemy * enemy_i=(*iter);
			enemy_rect=enemy_i->sprite->boundingBox();
			if(player_rect.intersectsRect(enemy_rect))
			{
				if(enemy_i->_isdummy_collision)
				{
					enemy_i->enemyCollisionMove(player);
					enemy_i->_isdummy_collision=false;
				}
				else if(enemy_i->_phase_collision1)
				{
					playr_hp--;
					enemy_i->_phase_collision1=false;
				}
			}
			if(player->getPositionY()-(player->getContentSize().height/2) < enemy_i->sprite->getPositionY()+(enemy_i->sprite->getContentSize().height/2))
			{
				enemy_i->_overtake=true;
			}
			if(playr_hp<0)
			{
				phase=2;
			}
		}
		CCObject *s_obj=NULL;
		CCARRAY_FOREACH(sectors,s_obj)
		{
			CCSprite *temp_sec=(CCSprite*)s_obj;
			CCRect sec_rect=temp_sec->boundingBox();
			if(player_rect.intersectsRect(sec_rect))
			{
				this->removeChild(temp_sec);
				sectors->removeObject(s_obj,true);
				phase=2;
			}
		}

	}
	else if(phase==3)
	{
		list<Enemy*>::iterator iter;
		for(iter=enemy_temp->begin();iter!=enemy_temp->end();iter++)
		{
			Enemy * enemy_i=(*iter);
			enemy_rect=enemy_i->sprite->boundingBox();
			if(player_rect.intersectsRect(enemy_rect))
			{
				if(enemy_i->_phase_collision2)
				{
					AudioManager::getAudioManager()->playEffectAudio(SOUND_ENEMYHIT);
					usb_count++;
					if(usb_count>max_file)
					{
						usb_count=max_file;
					}

					CCParticleSystem *particle=CCParticleFireworks::create();
					char str[100]={0};
					int r_file=rand()%3+1;
					sprintf(str,"gameplay/images/file_0%d.png",r_file);
					particle->setTexture(CCTextureCache::sharedTextureCache()->addImage(str));
					particle->setDuration(0.4);
					particle->setLife(1);
					particle->setLifeVar(1);
					particle->setTotalParticles(1);
					particle->setStartSize(100);
					particle->setEndSize(5);
					particle->setStartColor(ccc4f(1,1,1,1));
					particle->setContentSize(CCSize(20,20));
					particle->setEmissionRate(200);
					particle->setEndSize(100);
					particle->setPosition((*iter)->sprite->getPosition());
					particle->setAutoRemoveOnFinish(true);
					this->addChild(particle,Z_effect);
					enemy_i->_overtake=true;
					enemy_i->_phase_collision2=false;
				}
			}
		}
	}
	else if(phase==4)
	{
		list<Enemy*>::iterator iter;
		for(iter=enemy_temp->begin();iter!=enemy_temp->end();iter++)
		{
			Enemy * enemy_i=(*iter);
			enemy_rect=enemy_i->sprite->boundingBox();
			CCObject *project=NULL;
			//CCLog("%f///%f",enemy_i->sprite->getPositionX(),enemy_i->sprite->getPositionY());
			CCARRAY_FOREACH(projectiles,project)
			{
				CCSprite *project_obj=(CCSprite *)project;
				CCRect project_obj_rect=project_obj->boundingBox();

				if(enemy_rect.intersectsRect(project_obj_rect))
				{
					CCParticleSystem *particle=CCParticleExplosion::create();
					particle->retain();
					particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("gameplay/images/ex.png"));
					particle->setDuration(0.1);
					particle->setContentSize(CCSize(20,20));
					particle->setLife(1);
					particle->setLifeVar(1);
					particle->setTotalParticles(1);
					particle->setStartSize(100);
					particle->setStartColor(ccc4f(1,1,1,1));
					particle->setEndSize(100);
					particle->setEndSizeVar(50);
					particle->setEmissionRate(200);
					particle->setPosition(project_obj->getPosition());
					particle->setAutoRemoveOnFinish(true);
					this->addChild(particle,Z_effect);
					project_obj->stopAllActions();
					enemy_i->hp-=shot_damge;
					this->removeChild(project_obj);
					projectiles->removeObject(project_obj);
				}
			}
			if(enemy_rect.intersectsRect(player_rect))
							{
								if(enemy_i->_phase_collision3)
								{
									usb_count--;
									if(usb_count<0)
									{
										usb_count=0;
									}
									enemy_i->_phase_collision3=false;
								}
							}
			if(enemy_i->sprite->getPositionY()+(enemy_i->sprite->getContentSize().height/2) > 1280)
				{
					enemy_i->hp=0;
				}
		}
	}
	list<Enemy*>::iterator iter2;
	for(iter2=enemy_temp->begin();iter2!=enemy_temp->end();)
	{
		if((*iter2)->hp<=0)
		{
			money+=(*iter2)->enemy_money;
			(*iter2)->sprite->stopAllActions();
			this->removeChild((*iter2)->sprite);
			enemy_temp->remove(*iter2++);
		}
		else
		{
			++iter2;
		}
	}
	if(enemy_temp->empty())
	{
		if(_resultcount==0)
		{
			soundCount++;
			AudioManager::getAudioManager()->playEffectAudio(SOUND_RESULT);
			_nowMoeny = money+(usb_count*3);
			money=_nowMoeny+CCUserDefault::sharedUserDefault()->getIntegerForKey("gameMoney");
			CCUserDefault::sharedUserDefault()->setIntegerForKey("gameMoney",money);
			popUpResult();
			_resultcount++;
			phase=5;

		}
		CCLog("endgame");
	}
	else
	{
		//CCLog("non end_enemy %d",enemy_temp->size());
	}
}

void PlayScene::gameLogic(float dt)
{
	if(!inLevel) return;
	GameLevel *curlevel=GameState::getInstance()->curLevel;
	timeval nowTime;
	gettimeofday(&nowTime,0);
	double now=nowTime.tv_sec;
	//if(levelBegin=0)//배경음악시작
	//{
	//
	//}
	//else
	//{}
}
void PlayScene::enemyInit()
{
	GameLevel *curlevel=GameState::getInstance()->curLevel;
	CCLog("bbbbb");
	CCObject* pObj=NULL;
	double dis=0;
	int intvral=400;
	int randvar=rand()%100;
	CCARRAY_FOREACH(curlevel->spawnIds,pObj)
	{
		dis-=(intvral+randvar);
		int enemyId=dynamic_cast<CCString*>(pObj)->intValue();
		Enemy  *enemy=new Enemy();
		enemy->setEnemy(enemyId,dis);
		enemy_temp->push_back(enemy);
		this->addChild(enemy->sprite,Z_Enemy);
		if(enemy->sprite->getTag()==4)
		{
			CCPoint enemy_p=CCPoint(enemy->sprite->getPosition());
			CCSprite *suv_sprite=CCSprite::create("gameplay/images/sector2.png");
			suv_sprite->setAnchorPoint(ccp(0.5f,0));
			suv_sprite->setPosition(enemy_p);
			CCActionInterval *rotation=CCRotateBy::create(0.1f,20,20);
			rotation->step(5);
			rotation->setDuration(0.5f);
			CCAction *acttion=CCRepeatForever::create(rotation);
			this->addChild(suv_sprite,Z_Enemy-1);
			sectors->addObject(suv_sprite);
			sectors->retain();
			suv_sprite->runAction(acttion);
		}
	}
}
void PlayScene::moveCamera()
{
	float x = 0, y = 0, z = 0;//camare position init
	int resist=1;//if collision
	//backgraund bot top seting
	double bk1_bot=level_bkgrnd1->getPositionY()-(level_bkgrnd1->getContentSize().height/2);
	double bk2_bot=level_bkgrnd2->getPositionY()-(level_bkgrnd2->getContentSize().height/2);
	double bk1_top=level_bkgrnd1->getPositionY()+(level_bkgrnd1->getContentSize().height/2);
	double bk2_top=level_bkgrnd2->getPositionY()+(level_bkgrnd2->getContentSize().height/2);
	//distance text postion set

	//player run distance
	//CCLog("phase=%d",phase);
	//player
	if(phase==1)
	{
		curdist+=scr_speed/-100;
		this->getCamera()->getCenterXYZ(&x, &y, &z);
		this->getCamera()->setCenterXYZ(x, y+scr_speed,z);
		this->getCamera()->getEyeXYZ(&x, &y, &z);
		this->getCamera()->setEyeXYZ(x, y+scr_speed, z);
		usbsprite->setPositionY(y+1280-120);
		usb_text->setPositionY(y+1280-100);
		_test->setPositionY(y+30);


		player->setPositionY(y+700);
		//p_sprite->setPositionY(y+1280-15);
		//back_p_sprite->setPositionY(y+1280-35);
		double camera_top=y+(1280);
		double camera_bot=y;
		if(camera_top<=bk1_bot)
		{
			level_bkgrnd1->setPositionY(level_bkgrnd2->getPositionY()
				-(level_bkgrnd2->getContentSize().height));
		}
		if(camera_top<=bk2_bot)
		{
			level_bkgrnd2->setPositionY(level_bkgrnd1->getPositionY()
				-(level_bkgrnd1->getContentSize().height));
		}
	}
	else if(phase==2)
	{
		this->getCamera()->getCenterXYZ(&x, &y, &z);
		if(isphase2set)
		{
			_gameMenu->setTouchEnabled(false);
			_gameMenu->setVisible(false);
			phaseset(ccp(x,y));
			isphase2set=false;
		}
	}
	else if(phase==3)
	{
		curdist+=scr_speed/-100;
		scr_speed+=resist;
		if(scr_speed>6) scr_speed=6;
		if(scr_speed<0)scr_speed=0;
		int downspeed=0;
		this->getCamera()->getCenterXYZ(&x, &y, &z);
		this->getCamera()->setCenterXYZ(x, y+scr_speed,z);
		this->getCamera()->getEyeXYZ(&x, &y, &z);
		this->getCamera()->setEyeXYZ(x, y+scr_speed, z);
		usbsprite->setPositionY(y+1280-120);
		usb_text->setPositionY(y+1280-100);
		_test->setPositionY(y+30);

		//p_sprite->setPositionY(y+1280-15);
		//back_p_sprite->setPositionY(y+1280-35);
		double camera_top=y+(1280);
		double camera_bot=y;
		if(isphase3set)
		{
			AudioManager::getAudioManager()->stopSound();
			AudioManager::getAudioManager()->playSound(SOUND_COMEBACK);
			phaseset(ccp(x,y));
			CCAnimation *player_ani=CCAnimation::create();
			player_ani->setDelayPerUnit(0.2);
			player_ani->addSpriteFrameWithFileName("gameplay/images/b_rgb_0_0.png");
			player_ani->addSpriteFrameWithFileName("gameplay/images/b_rgb_0_1.png");
			CCAnimate *player_mate=CCAnimate::create(player_ani);
			CCAction *player_rep=CCRepeatForever::create(player_mate);
			player->stopAllActions();
			player->runAction(player_rep);
			isphase3set=false;
		}
		player->setPositionY(y+700);
		if(camera_bot>=bk1_top)
		{
			level_bkgrnd1->setPositionY(level_bkgrnd2->getPositionY()
				+(level_bkgrnd2->getContentSize().height));
		}
		if(camera_bot>=bk2_top)
		{
			level_bkgrnd2->setPositionY(level_bkgrnd1->getPositionY()
				+(level_bkgrnd1->getContentSize().height));
		}
	}
	else if(phase==4)
	{
		if(isphase4set)
		{
			CCPoint arrival_point =CCPoint(x+(720/2),y+(1280)-player->getContentSize().height/2-350);
			phaseset(arrival_point);
			isphase4set=false;
		}
	}
	//player end
}
void PlayScene::phaseset(CCPoint p)
{
	if(phase==2)
	{
		AudioManager::getAudioManager()->playEffectAudio(SOUND_SIREN);
			list<Enemy*>::iterator iter;
			for(iter=enemy_temp->begin();iter!=enemy_temp->end();iter++)
			{
				(*iter)->sprite->stopAllActions();
			}

		player->stopAllActions();
		enemy_car=CCSprite::create("gameplay/images/car.png");
		enemy_car->setRotation(180);
		enemy_car->setPosition(ccp(150,p.y-(enemy_car->getContentSize().height/2)));
		enemy_car->setTag(2);
		this->addChild(enemy_car,Z_Enemy);
		CCActionInterval *car_move=CCMoveBy::create(0.5,ccp(0,420));
		enemy_car->runAction(car_move);
		CCSprite *tempenemy1=CCSprite::create("gameplay/images/b_mon_101.png");
		tempenemy1->setVisible(0);
		tempenemy1->setPosition(ccp(340,p.y-(enemy_car->getContentSize().height/2)+420));
		this->addChild(tempenemy1,Z_Enemy);
		CCFiniteTimeAction *temp_function=CCCallFuncN::create(this,callfuncN_selector(PlayScene::carfunction));
		CCActionInterval *d_time=CCDelayTime::create(0.8);
		CCAnimation *temp_ani1=CCAnimation::create();
		temp_ani1->addSpriteFrameWithFileName("gameplay/images/b_mon_101.png");
		temp_ani1->addSpriteFrameWithFileName("gameplay/images/b_mon_102.png");
		temp_ani1->setDelayPerUnit(0.3);
		temp_ani1->setLoops(3);
		CCAnimate *temp_mate1=CCAnimate::create(temp_ani1);
		CCActionInterval *temp_move1=CCMoveBy::create(0.4,ccp(10,0));
		CCFiniteTimeAction *temp_spawn1=CCSpawn::create(temp_mate1,temp_move1,NULL);
		CCFiniteTimeAction *act=CCSequence::create(d_time,temp_function,temp_spawn1,temp_function,d_time,temp_function,NULL);
		tempenemy1->runAction(act);

		CCSprite *tempenemy2=CCSprite::create("gameplay/images/b_mon_401.png");
		tempenemy2->setVisible(0);
		tempenemy2->setPosition(ccp(340,p.y-(enemy_car->getContentSize().height/2)+420));
		this->addChild(tempenemy2,Z_Enemy);
		CCAnimation *temp_ani2=CCAnimation::create();
		temp_ani2->addSpriteFrameWithFileName("gameplay/images/b_mon_401.png");
		temp_ani2->addSpriteFrameWithFileName("gameplay/images/b_mon_402.png");
		temp_ani2->setDelayPerUnit(0.1);
		temp_ani2->setLoops(2);
		CCAnimate *temp_mate2=CCAnimate::create(temp_ani2);
		CCActionInterval *temp_move2=CCMoveBy::create(0.4,ccp(120,0));
		CCFiniteTimeAction *temp_spawn2=CCSpawn::create(temp_mate2,temp_move2,NULL);
		CCFiniteTimeAction *act2=CCSequence::create(d_time,temp_function,temp_spawn2,temp_function,d_time,temp_function,NULL);
		tempenemy2->runAction(act2);
		CCFiniteTimeAction *phase_controll=CCCallFuncN::create(this,callfuncN_selector(PlayScene::carfunction));
		CCFiniteTimeAction *caract=CCSequence::create(car_move,NULL);

		//enemy_car->setro
	}
	else if(phase==3)
	{
		sectors->removeAllObjects();
		player->stopAllActions();
	}
	else if(phase==4)
	{
		CCPoint player_point=p;
		CCAnimation *player_ani=CCAnimation::create();
		player_ani->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_0.png");
		player_ani->setDelayPerUnit(1);
		CCAnimate *player_mate=CCAnimate::create(player_ani);
		player->stopAllActions();
		player->runAction(player_mate);
		CCActionInterval *player_act=CCMoveTo::create(1,player_point);
		player->runAction(player_act);
		list<Enemy*>::iterator iter;
		for(iter=enemy_temp->begin();iter!=enemy_temp->end();)
		{
			if((*iter)->_overtake==true)
			{
				(*iter)->sprite->stopAllActions();
				(*iter)->phaseThreeset(player_point);
				++iter;
			}
			else
			{
				(*iter)->sprite->stopAllActions();
				this->removeChild((*iter)->sprite);
				enemy_temp->remove(*iter++);
			}
		}
	}
}
void PlayScene::didAccelerate(CCAcceleration* pAccelerationValue)
{
	CCDirector* pDir = CCDirector::sharedDirector();
	CCSize ballsize = player->getContentSize();
	CCPoint ptNow = player->getPosition();
	CCPoint ptTemp = pDir->convertToUI(ptNow);
	if(phase==1 || phase==3 )
	{
		ptTemp.x +=pAccelerationValue->x*20;
		//ptTemp.y -=pAccelerationValue->y * 15.81f;
		CCPoint ptNext = pDir->convertToGL(ptTemp);
		FIX_POS(ptNext.x,(ballsize.width/2.0),(720-ballsize.width/2.0));
		//FIX_POS(ptNext.y,(ballsize.height/2.0),(winsize_h-ballsize.height/2.0));
		player->setPosition(ptNext);

		CCAnimation *ani=CCAnimation::create();
		ani->setDelayPerUnit(0.3);
		if(pAccelerationValue->x<0)
		{
			if(right_switch)
			{
				player->stopAllActions();
				if(phase==1)
				{

				ani->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_0.png");
				ani->addSpriteFrameWithFileName("gameplay/images/l_rgb_0_1.png");
				}
				else if(phase==3)
				{

					ani->addSpriteFrameWithFileName("gameplay/images/b_rgb_0_0.png");
					ani->addSpriteFrameWithFileName("gameplay/images/b_rgb_0_1.png");
				}
				right_switch=false;
			}
			else
			{
				left_switch=true;
			}
		}
		else if(pAccelerationValue->x>0)
		{

			if(left_switch)
			{
				player->stopAllActions();
				if(phase==1)
				{
					ani->addSpriteFrameWithFileName("gameplay/images/r_rgb_0_0.png");
					ani->addSpriteFrameWithFileName("gameplay/images/r_rgb_0_1.png");
				}
				else if(phase==3)
				{

					ani->addSpriteFrameWithFileName("gameplay/images/b_rgb_1_0.png");
					ani->addSpriteFrameWithFileName("gameplay/images/b_rgb_1_1.png");
				}
				left_switch=false;
			}
			else
			{
				right_switch=true;
			}
		}
		CCAnimate *animate=CCAnimate::create(ani);
		CCAction *acttion=CCRepeatForever::create(animate);
		player->runAction(acttion);
	}
	if(phase==1)
	{
		list<Enemy*>::iterator iter;
		for(iter=enemy_temp->begin();iter!=enemy_temp->end();iter++)
		{
			if((*iter)->sprite->getTag()==6)
			{
				(*iter)->accelanimation(pAccelerationValue);
				CCSize ballsize_e=(*iter)->sprite->getContentSize();
				CCPoint peNow= (*iter)->sprite->getPosition();
				CCPoint peTemp= pDir->convertToUI(peNow);
				peTemp.x+=pAccelerationValue->x*5.5f;
				CCPoint peNext=pDir->convertToGL(peTemp);
				FIX_POS(peNext.x,(ballsize_e.width/2.0),(720-(ballsize_e.width/2.0)));
				(*iter)->sprite->setPosition(peNext);
			}
		}
	}
}
void PlayScene::carfunction(CCNode *sender)
{
	CCSprite *temp=(CCSprite*)sender;
	if(temp->getTag()==1)
	{
		if(phase==-1)
		{
			temp->setTag(3);
			player->setPositionY(700);
			phase=0;
		}
	}
	else
	{
		if(temp->getTag()==3)
		{
			temp->setVisible(false);
		}
		else if(temp->isVisible()==false)
		{
			temp->setVisible(true);
		}
		else
		{
			for(int i=0;i<15;i++)
			{
				AudioManager::getAudioManager()->playEffectAudio(SOUND_SHOT);
				CCSprite *bullet=CCSprite::create("gameplay/images/bullet.png");
				bullet->setPosition(temp->getPosition());
				bullet->setTag(i);
				this->addChild(bullet);
				CCActionInterval *bullet_move=CCMoveTo::create(0.2,ccp(player->getPositionX()+(50*(i%3))-50,player->getPositionY()-70));
				CCActionInterval *d_time=CCDelayTime::create(i*0.1);
				CCActionInterval *d_time2=CCDelayTime::create(2);
				CCFiniteTimeAction *bullet_function=CCCallFuncN::create(this,callfuncN_selector(PlayScene::bullet_Visible));
				CCFiniteTimeAction *act=CCSequence::create(d_time,bullet_move,bullet_function,bullet_function,NULL);
				bullet->runAction(act);
			}
			temp->setTag(3);
		}

	}
}
void PlayScene::doPop()
{

	CCScene* pScene=PopLayer::scene();
	this->addChild(pScene,2000,2000);
}
//노티피케이션 함수
void PlayScene::doNotification(CCObject *obj){
      //노티피케이션 받기
	CCString *pParam=(CCString*)obj;

	if(pParam->intValue()==1){

		CCDirector::sharedDirector()->resume();
		//화면 재시작
		AudioManager::getAudioManager()->resumeSound();
		//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(pause_menu, kCCMenuHandlerPriority,true);
                                     //메뉴 버튼 활성
	}
	else{

		CCArray* childs = this->getChildren();
			CCDirector::sharedDirector()->pause();
			AudioManager::getAudioManager()->pauseSound();
			//화면 정지
			//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(pause_menu);
                                      //메뉴버튼 비활성
	}

}
void PlayScene::bullet_Visible(CCNode *sender)
{
	CCSprite *temp=(CCSprite*)sender;
	if(temp->isVisible()==true)
	{
		temp->setVisible(false);
	}

		if(temp->getTag()==7)
		{
			if(phase==2)
			{
				phase=3;
				CCParticleSystem *particle=CCParticleFireworks::create();
				char str[100]={0};
				sprintf(str,"gameplay/images/alert.png");
				particle->setTexture(CCTextureCache::sharedTextureCache()->addImage(str));
				particle->setDuration(0.4);
				particle->setLife(1);
				particle->setLifeVar(1);
				particle->setTotalParticles(2);
				particle->setStartSize(100);
				particle->setEndSize(5);
				particle->setStartColor(ccc4f(1,1,1,1));
				particle->setEndColor(ccc4f(1,1,1,1));
				particle->setContentSize(CCSize(20,20));
				particle->setEmissionRate(200);
				particle->setEndSize(100);
				particle->setPosition(player->getPositionX()+40,player->getPositionY());
				particle->setAutoRemoveOnFinish(true);
				this->addChild(particle,Z_effect);

			}

		}





}
