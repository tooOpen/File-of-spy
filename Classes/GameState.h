/*
 * GameState.h
 *
 *  Created on: 2014. 4. 30.
 *      Author: pym
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include "cocos2d.h"
using namespace cocos2d;

class GameLevel;

class GameState :public CCLayer
{
public:
	static GameState *getInstance();

	void setstage(int state);
	void nextLevel();
	void winGame();
	void loseGame();

	//level pointer
	GameLevel *curLevel;
	int curStageIndex;
	void initLevel();

private:

	GameState();
	~GameState();

	///level game start state save
	CCArray *levels;
};

#endif /* GAMESTATE_H_ */
