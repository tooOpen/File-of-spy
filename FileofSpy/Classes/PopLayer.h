#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PopLayer : public cocos2d::CCLayerColor
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();

    CREATE_FUNC(PopLayer);
	CCSize winSize;
	CCSprite *back;
	CCLayerColor* backLayer;
	CCLayerColor* popUpLayer;
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *event);
	void doClose();

};

