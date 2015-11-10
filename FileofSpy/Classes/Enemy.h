#ifndef _enemy__
#define _enemy__
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class Enemy
{
public:
	CCSprite *sprite;
	int hp;
	bool _phase_collision1;
	bool _phase_collision2;
	double maxDist;
	bool _overtake;
	bool _isdummy_collision;
	bool _phase_collision3;
	int speed;
	bool left_switch;
	bool right_switch;
	int enemy_money;
	Enemy();
	void setEnemy(int enemyType,double ypos);
	void enemyCollisionMove(CCSprite *p);
	void phaseThreeset(CCPoint p);
	void accelanimation(CCAcceleration *pAccelerationValue);
	void enemyMoveFinished(CCNode *sender);
	virtual ~Enemy();
};
#endif
