/*
 * GameState.cpp
 *
 *  Created on: 2014. 4. 30.
 *      Author: pym
 */

#include "GameState.h"
#include "GameLevel.h"
GameState::GameState()
{
	// TODO Auto-generated constructor stub

}
GameState::~GameState() {
	// TODO Auto-generated destructor stub
	levels->release();
}
static GameState *pSingleton;
GameState *GameState::getInstance()
{
	if(!pSingleton)
	{
		pSingleton=new GameState();
		pSingleton->initLevel();
	}
	return pSingleton;
}

void GameState::initLevel()
{
	levels=CCArray::create();

	GameLevel *level1=new GameLevel;
	level1->spawnSeconds=15;
	level1->spawnRate=16;
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("4") );
	level1->spawnIds->addObject( CCString::create("4") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("3") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("4") );
	level1->spawnIds->addObject( CCString::create("4") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("1") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("2") );
	level1->spawnIds->addObject( CCString::create("2") );
//	level1->spawnIds->addObject( CCString::create("1") );
//	level1->spawnIds->addObject( CCString::create("1") );
//	level1->spawnIds->addObject( CCString::create("1") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("2") );
//	level1->spawnIds->addObject( CCString::create("2") );
//	level1->spawnIds->addObject( CCString::create("4") );
//	level1->spawnIds->addObject( CCString::create("4") );
//	level1->spawnIds->addObject( CCString::create("1") );
//	level1->spawnIds->addObject( CCString::create("1") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("3") );
//	level1->spawnIds->addObject( CCString::create("2") );
//	level1->spawnIds->addObject( CCString::create("2") );
//	level1->spawnIds->addObject( CCString::create("4") );
//	level1->spawnIds->addObject( CCString::create("4") );

	levels->addObject(level1);

	GameLevel *level2=new GameLevel;
	level2->spawnSeconds=15;
	level2->spawnRate=4;
	level2->spawnIds->addObject( CCString::create("3") );
	level2->spawnIds->addObject( CCString::create("2") );
	level2->spawnIds->addObject( CCString::create("2") );
	level2->spawnIds->addObject( CCString::create("3") );
	level2->spawnIds->addObject( CCString::create("3") );
	level2->spawnIds->addObject( CCString::create("3") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("6") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("2") );
	level2->spawnIds->addObject( CCString::create("2") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("2") );
	level2->spawnIds->addObject( CCString::create("2") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("1") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("4") );
	level2->spawnIds->addObject( CCString::create("5") );
	level2->spawnIds->addObject( CCString::create("1") );
	levels->addObject(level2);

	GameLevel *level3=new GameLevel;
	level3->spawnSeconds=15;
	level3->spawnRate=16;
	level3->spawnIds->addObject( CCString::create("1") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("6") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("2") );
	level3->spawnIds->addObject( CCString::create("5") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("3") );
	level3->spawnIds->addObject( CCString::create("4") );
	level3->spawnIds->addObject( CCString::create("6") );


	level3->spawnIds->addObject( CCString::create("6") );
	levels->addObject(level3);

	curStageIndex=0;
	curLevel=(GameLevel*)levels->objectAtIndex(curStageIndex);
}
void GameState::setstage(int state)
{
	curStageIndex=state;
	curLevel=(GameLevel*)levels->objectAtIndex(curStageIndex);
}
void GameState::nextLevel()
{
	curStageIndex++;
	if(curStageIndex<levels->count())
	{
		curLevel=(GameLevel*)levels->objectAtIndex(curStageIndex);
	}
}
void GameState::winGame()
{
	curStageIndex=3;
}
void GameState::loseGame()
{
	curStageIndex=4;
}


