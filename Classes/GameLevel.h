/*
 * GameLevel.h
 *
 *  Created on: 2014. 4. 30.
 *      Author: pym
 */

#ifndef GAMELEVEL_H_
#define GAMELEVEL_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameLevel :public CCObject
{
public:
	GameLevel();
	virtual ~GameLevel();
	float spawnSeconds;
	float rundistance;
	float spawnRate;
	CCArray *spawnIds;

};

#endif /* GAMELEVEL_H_ */
