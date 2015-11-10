/*
 * OpenScene.h
 *
 *  Created on: 2014. 4. 28.
 *      Author: pc
 */

#ifndef OPENSCENE_H_
#define OPENSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;
class OpenScene :public CCLayer {
public:
	OpenScene();
	virtual ~OpenScene();

	virtual bool init();
		static CCScene* scene();
		CREATE_FUNC(OpenScene);
		bool _one;
		CCSprite* _logo;
		CCSprite* _swipe;
		CCSprite* _transi;
		void logotime(float f);
		void changeScene(float f);

};

#endif /* OPENSCENE_H_ */
