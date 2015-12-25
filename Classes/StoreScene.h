/*
 * StoreScene.h
 *
 *  Created on: 2014. 4. 28.
 *      Author: pc
 */

#ifndef STORESCENE_H_
#define STORESCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Manager/AudioManager.h"
#include "ReadyScene.h"
#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/manager/ItemManager.h"
USING_NS_CC_EXT;
using namespace cocos2d;


class StoreScene: public CCLayer, public CCScrollViewDelegate {
public:
	StoreScene();
	virtual ~StoreScene();

	virtual bool init();

	void scrollViewDidScroll(CCScrollView* view);
	void scrollViewDidZoom(CCScrollView* view);
	int itemNum;
	std::string _itemPricearr[15];/// change to 15 after came images
	std::string _itemDescarr[15];/// change to 15 after came images
	std::string _itemNamearr[15];/// change to 15 after came images
	int _selectedItem;
	int _seletedLine;
	int _itemstate;
	int _haveMoney;
	CCLabelTTF* _itemPriceLable;
	CCLabelTTF* _itemNameLable;
	CCLabelTTF* _itemDescLable;
	CCLabelTTF* _haveMoneyLable;
	CCMenuItemImage* _storebuyItem;
	CCMenuItemImage* _storebackItem;
	CCMenu* _storebuyMenu;
	CCMenu* _storebackMenu;

	virtual void ccTouchesBegan(CCSet *pTouch, CCEvent *pEvent);
	virtual void ccTouceshMove(CCSet *pTouch, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouch, CCEvent *pEvent);
	virtual void ccTouchesCanclled(CCSet *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();	//adroid backkey
	static CCScene* scene();CREATE_FUNC(StoreScene);

	std::string addComma(int value);
	void backMenuClick(CCObject* pSender);
	void buyMenuClick(CCObject* pSender);


	CCSprite* _storebackgorund;
	CCSprite* _storeinfo;

	CCSprite* _itemarr[15];
	CCSprite* _itemFrame;
	CCSprite* _storeBackBoard;

	CCLayerColor *_linelayer1;
	CCLayerColor *_linelayer2;
	CCLayerColor *_linelayer3;
	CCSprite* transi;
	CCScrollView *scrollView;
	CCScrollView *scrollView2;
	CCScrollView *scrollView3;

};



#endif /* OPENSCENE_H_ */
