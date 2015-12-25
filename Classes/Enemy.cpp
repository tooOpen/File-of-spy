#include "Enemy.h"
Enemy::Enemy():hp(0),maxDist(0),_phase_collision1(true),_phase_collision2(true),_phase_collision3(true),sprite(NULL),_overtake(false),_isdummy_collision(false),left_switch(true),right_switch(true),speed(0),enemy_money(0)
{
	// TODO Auto-generated constructor stub
}
Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
	sprite->release();
}
void Enemy::setEnemy(int enemyType,double ypos)
{
	double win_h=1280;
	double win_w=720;
	if(enemyType==1)//좌우
	{
		this->maxDist=70;
		this->hp=5;
		this->speed=1;
		this->enemy_money=enemyType;
		///좌표
		sprite=CCSprite::create("gameplay/images/r_mon_101.png");
		//suv_sprite->setZOrder(5);
		int minx=sprite->getContentSize().width/2;
		int maxx=win_w-(sprite->getContentSize().width/2);
		int rangex=maxx-minx;
		int actualx=( rand()% rangex)+minx;
		sprite->setPosition(ccp(actualx,ypos));
		int direction=1;
		if(sprite->getPositionX()-minx > maxx-sprite->getPositionX())
		{
			direction=-1;
		}
		sprite->setTag(enemyType);
		CCActionInterval *move=CCMoveBy::create(1,CCPoint(maxDist*direction,0));
		CCAnimation *ani_right=CCAnimation::create();
		ani_right->setDelayPerUnit(0.3);
		ani_right->setLoops(4);
		if(direction==1)
		{
			ani_right->addSpriteFrameWithFileName("gameplay/images/r_mon_101.png");
			ani_right->addSpriteFrameWithFileName("gameplay/images/r_mon_102.png");
		}
		else
		{
			ani_right->addSpriteFrameWithFileName("gameplay/images/l_mon_101.png");
			ani_right->addSpriteFrameWithFileName("gameplay/images/l_mon_102.png");
		}

		CCAnimate *right_animate=CCAnimate::create(ani_right);
		CCFiniteTimeAction *right_spawn=CCSpawn::create(move,right_animate,NULL);
		//
		CCActionInterval *moveback=move->reverse();
		CCAnimation *ani_left=CCAnimation::create();
		ani_left->setDelayPerUnit(0.3);
		ani_left->setLoops(4);
		if(direction==1)
		{
			ani_left->addSpriteFrameWithFileName("gameplay/images/l_mon_101.png");
			ani_left->addSpriteFrameWithFileName("gameplay/images/l_mon_102.png");
		}
		else
		{
			ani_left->addSpriteFrameWithFileName("gameplay/images/r_mon_101.png");
			ani_left->addSpriteFrameWithFileName("gameplay/images/r_mon_102.png");

		}
		CCAnimate *left_animate=CCAnimate::create(ani_left);
		//CCAction *left_ani_action=CCRepeatForever::create(right_animate);
		CCFiniteTimeAction *left_spawn=CCSpawn::create(moveback,left_animate,NULL);
		//
		double randster=(rand()%1000)/1000.f;
		CCActionInterval *d_time=CCDelayTime::create(randster);
		CCFiniteTimeAction *act=CCSequence::create(d_time,right_spawn,left_spawn,NULL);
		CCActionInterval *rep=(CCActionInterval*)act;
		CCAction *acttion=CCRepeatForever::create(rep);
		sprite->runAction(acttion);

	}
	else if(enemyType==2)//상하
	{
		sprite=CCSprite::create("gameplay/images/b_mon_201.png");
		this->hp=3;
		this->speed=1;
		this->maxDist=100;
		this->enemy_money=enemyType;
		sprite->setTag(enemyType);
		int minx=sprite->getContentSize().width/2;
		int maxx=win_w - (sprite->getContentSize().width/2);
		int rangex=maxx-minx;
		int actualx=( rand()% rangex)+minx;
		sprite->setPosition(ccp(actualx,ypos));
		double randster=(rand()%1000)/1000.f;
		CCActionInterval *d_time=CCDelayTime::create(randster);
		CCActionInterval *move=CCMoveBy::create(1,ccp(0,maxDist));
		CCAnimation *ani_up=CCAnimation::create();
		ani_up->setDelayPerUnit(0.6);
		ani_up->setLoops(2);
		ani_up->addSpriteFrameWithFileName("gameplay/images/b_mon_201.png");
		ani_up->addSpriteFrameWithFileName("gameplay/images/b_mon_202.png");
		CCAnimate *up_animate=CCAnimate::create(ani_up);
		CCFiniteTimeAction *up_spawn=CCSpawn::create(move,up_animate,NULL);
		CCActionInterval *moveback=move->reverse();
		CCAnimation *ani_down=CCAnimation::create();
		ani_down->setDelayPerUnit(0.6);
		ani_down->setLoops(2);
		ani_down->addSpriteFrameWithFileName("gameplay/images/l_mon_201.png");
		ani_down->addSpriteFrameWithFileName("gameplay/images/l_mon_202.png");
		CCAnimate *down_animate=CCAnimate::create(ani_down);
		CCFiniteTimeAction *down_spawn=CCSpawn::create(moveback,down_animate,NULL);
		//
		CCFiniteTimeAction *act=CCSequence::create(d_time,up_spawn,down_spawn,NULL);
		CCActionInterval *rep=(CCActionInterval*)act;
		CCAction *acttion=CCRepeatForever::create(rep);
		sprite->runAction(acttion);
	}
	else if(enemyType==3)//좌우 에스
	{
		sprite=CCSprite::create("gameplay/images/l_mon_301.png");
		this->hp=4;
		this->speed=2;
		this->maxDist=300;
		int hi=70;
		this->enemy_money=enemyType;
		sprite->setTag(enemyType);
		int minx=sprite->getContentSize().width/2;
		int maxx=win_w - (sprite->getContentSize().width/2);
		int rangex=maxx-minx;
		int actualx=( rand()% rangex)+minx;
		sprite->setPosition(ccp(actualx,ypos));
		int direction=1;
		if(sprite->getPositionX()-minx > maxx-sprite->getPositionX())
		{
			direction=-1;
		}
		ccBezierConfig bezier;
		bezier.controlPoint_1=ccp(0,50);
		bezier.controlPoint_2=ccp((maxDist/2)*direction,70);
		bezier.endPosition=ccp((maxDist/2)*direction,0);
		ccBezierConfig bezier2;
		bezier2.controlPoint_1=ccp(0,-50);
		bezier2.controlPoint_2=ccp((maxDist/2)*direction,-70);
		bezier2.endPosition=ccp((maxDist/2)*direction,0);
		double randster=(rand()%1000)/1000.f;
		CCActionInterval *b_move1=CCBezierBy::create(1,bezier);
		CCActionInterval *b_moveback1=b_move1->reverse();
		CCAnimation *ani_right=CCAnimation::create();
		ani_right->setDelayPerUnit(0.4);
		ani_right->setLoops(3);
		if(direction==1)
		{
			ani_right->addSpriteFrameWithFileName("gameplay/images/l_mon_301.png");
			ani_right->addSpriteFrameWithFileName("gameplay/images/l_mon_302.png");
		}
		else
		{
			ani_right->addSpriteFrameWithFileName("gameplay/images/r_mon_301.png");
			ani_right->addSpriteFrameWithFileName("gameplay/images/r_mon_302.png");
		}

		CCAnimate *right_animate=CCAnimate::create(ani_right);

		CCActionInterval *b_move2=CCBezierBy::create(1,bezier2);
		CCActionInterval *b_moveback2=b_move2->reverse();
		CCAnimation *ani_left=CCAnimation::create();
		ani_left->setDelayPerUnit(0.4);
		ani_left->setLoops(3);
		if(direction==1)
		{
			ani_left->addSpriteFrameWithFileName("gameplay/images/r_mon_301.png");
			ani_left->addSpriteFrameWithFileName("gameplay/images/r_mon_302.png");
		}
		else
		{
			ani_left->addSpriteFrameWithFileName("gameplay/images/l_mon_301.png");
			ani_left->addSpriteFrameWithFileName("gameplay/images/l_mon_302.png");
		}

		CCAnimate *left_animate=CCAnimate::create(ani_left);

		CCFiniteTimeAction *right_spawn1=CCSpawn::create(b_move1,left_animate,NULL);
		CCFiniteTimeAction *right_spawn2=CCSpawn::create(b_moveback1,right_animate,NULL);

		CCFiniteTimeAction *left_spawn1=CCSpawn::create(b_move2,left_animate,NULL);
		CCFiniteTimeAction *left_spawn2=CCSpawn::create(b_moveback2,right_animate,NULL);
		CCActionInterval *d_time=CCDelayTime::create(randster);
		CCFiniteTimeAction *act=CCSequence::create(d_time,right_spawn1,left_spawn1,right_spawn2,left_spawn2,NULL);
		CCActionInterval *rep=(CCActionInterval*)act;
		CCAction *acttion=CCRepeatForever::create(rep);
		sprite->runAction(acttion);
	}
	else if(enemyType==4)//경비형
	{
		this->hp=5;
		this->speed=3;
		this->enemy_money=enemyType;
		sprite=CCSprite::create("gameplay/images/r_mon_401.png");
		int minx=(sprite->getContentSize().width/2)+100;
		int maxx=win_w - (sprite->getContentSize().width/2)-100;
		int rangex=maxx-minx;
		int actualx=( rand()% rangex)+minx;
		CCAnimation *ani=CCAnimation::create();
		ani->setDelayPerUnit(0.01);
		if(win_w-actualx >win_w/2)//오른쪽
		{
			ani->addSpriteFrameWithFileName("gameplay/images/l_mon_401.png");
		}
		else //왼쪽
		{
			ani->addSpriteFrameWithFileName("gameplay/images/r_mon_401.png");
		}
		sprite->setPosition(ccp(actualx,ypos));
		sprite->setTag(enemyType);
		CCAnimate *animate=CCAnimate::create(ani);
		sprite->runAction(animate);
	}
	else if(enemyType==5)//지뢰형
	{
		this->hp=1;
		this->speed=1;
		this->enemy_money=enemyType;
		sprite=CCSprite::create("gameplay/images/hole.png");
		//sprite->setColor(ccc3(1.f,1.f,1.f));
		this->_isdummy_collision=true;
		int minx=sprite->getContentSize().width/2;
		int maxx=win_w - (sprite->getContentSize().width/2);
		int rangex=maxx-minx;
		int actualx=( rand()% rangex)+minx;
		sprite->setPosition(ccp(actualx,ypos));
		sprite->setTag(enemyType);
	}
	else if(enemyType==6)//기울기 값
	{
		sprite=CCSprite::create("gameplay/images/l_mon_601.png");
		this->hp=2;
		this->speed=2;
		this->enemy_money=enemyType;
		int minx=sprite->getContentSize().width/2;
		int maxx=win_w - (sprite->getContentSize().width/2);
		int rangex=maxx-minx;
		int actualx=( rand()% rangex)+minx;
		sprite->setPosition(ccp(actualx,ypos));
		sprite->setTag(enemyType);
	}
	sprite->retain();
}
void Enemy::enemyCollisionMove(CCSprite *p)
{
	double win_h=1280;
	double win_w=720;
	CCPoint vec=ccpSub(p->getPosition(),sprite->getPosition());
	CCPoint vec_normal=ccpNormalize(vec);
	if(sprite->getTag()==5)//충돌기 합번 따라오기
	{
		CCAnimation *initani=CCAnimation::create();
		initani->addSpriteFrameWithFileName("gameplay/images/r_mon_501.png");
		CCAnimate *initanimate=CCAnimate::create(initani);
		CCAnimation *anit=CCAnimation::create();
		anit->addSpriteFrameWithFileName("gameplay/images/l_mon_501.png");
		anit->addSpriteFrameWithFileName("gameplay/images/l_mon_502.png");
		anit->addSpriteFrameWithFileName("gameplay/images/l_mon_501.png");
		anit->addSpriteFrameWithFileName("gameplay/images/l_mon_502.png");
		anit->addSpriteFrameWithFileName("gameplay/images/r_mon_501.png");
		anit->addSpriteFrameWithFileName("gameplay/images/r_mon_502.png");
		anit->addSpriteFrameWithFileName("gameplay/images/r_mon_501.png");
		anit->addSpriteFrameWithFileName("gameplay/images/r_mon_502.png");
		anit->setDelayPerUnit(0.6);
		anit->setLoops(3);
		CCAnimate *animate=CCAnimate::create(anit);
		//sprite->runAction(animate);
		//CCLog("vex: %f, vey: %f",vec_normal.x*100,vec_normal.y*100);
		CCActionInterval *move=CCMoveBy::create(1,ccp(vec_normal.x*500,vec_normal.y*-500));
		CCFiniteTimeAction *spawn=CCSpawn::create(animate,move,NULL);
		CCActionInterval *d_time=CCDelayTime::create(1);
		CCFiniteTimeAction *act=CCSequence::create(initanimate,d_time,spawn,NULL);
		//CCAction *acttion=CCRepeatForever::create(act);
		sprite->runAction(act);
	}
}
void Enemy::phaseThreeset(CCPoint p)
{
	speed*=205;
	if(this->_overtake)
	{
		CCPoint p_distans1=ccpSub(ccp(sprite->getPositionX(),p.y-1280-200),sprite->getPosition());
		float movetime1= sqrtf((p_distans1.x*p_distans1.x)+(p_distans1.y*p_distans1.y))/speed;
		CCActionInterval *act1=CCMoveTo::create(movetime1,ccp(sprite->getPositionX(),p.y-1280-200));

		CCPoint p_distans2=ccpSub(ccp(sprite->getPositionX(),p.y-1280-200),p);
				float movetime2= sqrtf((p_distans2.x*p_distans2.x)+(p_distans2.y*p_distans2.y))/speed;

		CCActionInterval *act2=CCMoveTo::create (movetime2,ccp(p.x,p.y));
		int randX=rand()%720-360;
		CCActionInterval *act3=CCMoveBy::create (1,ccp(randX,500));
		CCAnimation * enemy_ani=CCAnimation::create();
		if(sprite->getTag()==1)
		{
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_101.png");
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_102.png");
		}
		else if(sprite->getTag()==2)
		{
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_201.png");
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_202.png");
		}
		else if(sprite->getTag()==3)
		{
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_301.png");
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_302.png");
		}
		else if(sprite->getTag()==4)
		{
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_401.png");
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_402.png");
		}
		else if(sprite->getTag()==5)
		{
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_501.png");
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_502.png");
		}
		else if(sprite->getTag()==6)
		{
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_601.png");
			enemy_ani->addSpriteFrameWithFileName("gameplay/images/b_mon_602.png");
		}
		else
		{
			CCLog("phaseThreeset point bug");
		}
		enemy_ani->setDelayPerUnit(0.1);
		CCAnimate *enemyAnimate=CCAnimate::create(enemy_ani);
		enemyAnimate->setDuration(0.3);
		/*CCFiniteTimeAction *spawn=CCSpawn::create(act2,enemyAnimate,NULL);
		CCFiniteTimeAction *spawn2=CCSpawn::create(act3,enemyAnimate,NULL);
		CCFiniteTimeAction *allact=CCSequence::create(act1,spawn,spawn2,NULL);
		sprite->runAction(allact);*/
		CCAction *f_animate=CCRepeatForever::create(enemyAnimate);
		sprite->runAction(f_animate);
		CCFiniteTimeAction *allact=CCSequence::create(act1,act2,act3,NULL);
		sprite->runAction(allact);
	}
}
void Enemy::accelanimation(CCAcceleration *pAccelerationValue)
{
	if(pAccelerationValue->x<0)
		{
			if(right_switch)
			{
				sprite->stopAllActions();
				CCAnimation *ani_right=CCAnimation::create();
				ani_right->setDelayPerUnit(0.2);
				ani_right->addSpriteFrameWithFileName("gameplay/images/l_mon_601.png");
				ani_right->addSpriteFrameWithFileName("gameplay/images/l_mon_602.png");
				CCAnimate *right_animate=CCAnimate::create(ani_right);
				CCAction *acttion=CCRepeatForever::create(right_animate);
				sprite->runAction(acttion);
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
				sprite->stopAllActions();
				CCAnimation *ani_left=CCAnimation::create();
				ani_left->setDelayPerUnit(0.2);
				ani_left->addSpriteFrameWithFileName("gameplay/images/r_mon_601.png");
				ani_left->addSpriteFrameWithFileName("gameplay/images/r_mon_602.png");
				CCAnimate *left_animate=CCAnimate::create(ani_left);
				CCAction *acttion=CCRepeatForever::create(left_animate);
				sprite->runAction(acttion);
				left_switch=false;
			}
			else
			{
				right_switch=true;
			}
		}
}
