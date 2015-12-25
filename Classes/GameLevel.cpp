/*
 * GameLevel.cpp
 *
 *  Created on: 2014. 4. 30.
 *      Author: pym
 */

#include "GameLevel.h"

GameLevel::GameLevel() {
	// TODO Auto-generated constructor stub
	spawnIds=CCArray::create();
	spawnIds->retain();
}

GameLevel::~GameLevel() {
	// TODO Auto-generated destructor stub
	spawnIds->release();
}

