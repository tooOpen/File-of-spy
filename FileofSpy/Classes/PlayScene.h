/*
 * PlayScene.h
 *
 *  Created on: 2014. 5. 6.
 *      Author: pym
 */

#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "Manager/AudioManager.h"
#include <list>
using namespace cocos2d;
using namespace std;
class Enemy;

class PlayScene :public CCLayer
{
public:
	int _stage;
	int _resultcount;
	int _nowMoeny;
	bool _isplay;
	bool _transidone;
	CCSprite* _title;
	CCSprite* _transi;
	CCSprite* _resultBack;
	CCSprite *enemy_car;
	CCSprite* _resultNUM1;
	CCSprite* _resultNUM2;
	CCSprite* _resultNUM3;
	CCSprite* _resultNUM4;

	CCLabelTTF* _totalMoeny;

	CCSprite* sprite;
	JniMethodInfo t;
	CCSize winsize;
	CCMenuItemImage* _gamemenuItem;
	CCMenuItemImage* _resultRe;
	CCMenuItemImage* _resultStore;
	CCMenu* _gameMenu;
	CCMenu* _gameResultMenu;
	void gamemenuCallBack(CCObject* pSender);
	virtual void keyBackClicked();	//adroid backkey
	void activateScene();
	CCAnimate* resultAni(int value);
	void popUpResult();
















	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(PlayScene);
	int playr_hp;
	bool Acc_left;
	bool left_switch;
	bool Acc_right;
	bool right_switch;
	int shot_damge;
	int max_file;
	int curLevelIndex;
	int money;
	//sprite
	CCSprite* level_bkgrnd1;
	CCSprite* level_bkgrnd2;
	CCSprite* player;
	CCArray* enemys;
	CCArray* projectiles;
	CCArray *sectors;
	CCSprite* nextProjectile;
	CCSprite* usbsprite;
	CCSprite *p_sprite;
	CCSprite *back_p_sprite;
	CCMenu *pause_menu;
	CCMenuItemImage *p_menuimage;
	int usb_count;
	CCLabelTTF *usb_text;
	bool monsterHit;
	bool isphase1set;
	bool isphase2set;
	bool isphase3set;
	bool isphase4set;
	double levelBegin;
	double lastTimeMonsterAdded;
	bool inLevel;
	double winsize_h;
	double winsize_w;
	//CCSize winsize;
	double scr_speed;
	double curdist;
	CCLabelTTF *_test;
	int phase;
	PlayScene();
	virtual ~PlayScene();
	virtual void onExit();
	virtual void onEnter();
	void update(float dt);
	void gameLogic(float dt);
	list<Enemy*> *enemy_temp;
	void enemyInit();
	void spriteMoveFinished(CCNode *sender);
	void clearDate(int victory);
	void finishShoot();
	void phaseset(CCPoint p);
	void moveCamera();
	void menuTouch(CCObject* pSender);
	void carfunction(CCNode *sender);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *ptouch,CCEvent *event);
	//virtual void ccTouchBegan(CCTouch *pTouch, CCEvent *event);
	//virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *event);
	//virtual void ccTouchBegan(CCTouch *pTouch, CCEvent *event);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	void bullet_Visible(CCNode *sender);
	void restart();

	void doPop();
	void doNotification(CCObject *obj);
};
#endif /* PLAYSCENE_H_ */
