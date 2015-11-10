/*
 * StoreScene.cpp
 *
 *  Created on: 2014. 4. 28.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/StoreScene.h"
#include "PlayScene.h"
/*
 *
 * item%dState //each item state 0~15
 *
 * line1Equipped //equipped item for each line
 * line2Equipped
 * line3Equipped
 * line4Equipped
 *
 * gameMoney // gamemoney
 *
 *
 * gameStage start from 0
 * availableStage start from 0
 *
 * SFXvolume //volume value 0~10
 */
#define  HEIGHTGAP  200
StoreScene::StoreScene() {
	// TODO Auto-generated constructor stub

}

StoreScene::~StoreScene() {
	// TODO Auto-generated destructor stub
}

CCScene* StoreScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	StoreScene *layer = StoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StoreScene::init() {
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	int count = 0;
	itemNum = 15;
	_selectedItem = 0;
	_seletedLine = 0;
	_itemstate = 0;
	_storebackgorund = CCSprite::create("store/images/storeBack.png");
	_storebackgorund->setPosition(ccp(360,640));
	_storebackgorund->retain();
	this->addChild(_storebackgorund, 0);

	_storeBackBoard = CCSprite::create("store/images/itemBack.png");
	_storeBackBoard->setPosition(ccp(360,760));
	this->addChild(_storeBackBoard, 1);


	_storeinfo = CCSprite::create("store/images/storeinfo.png");
	_storeinfo->setPosition(ccp(360,520));
	this->addChild(_storeinfo, 2);

	_itemNameLable = CCLabelTTF::create("", "fonts/MarkerFelt.ttf", 60);
	_itemNameLable->setColor(ccc3(0, 0, 0));
	_itemNameLable->setAnchorPoint(ccp(0,0.5));
	_itemNameLable->setPosition(ccp(70,580));
	this->addChild(_itemNameLable, 5);

	_itemDescLable = CCLabelTTF::create("", "fonts/arial.ttf",
			30);
	_itemDescLable->setColor(ccc3(0, 0, 0));
	_itemDescLable->setAnchorPoint(ccp(0,0.5));
	_itemDescLable->setPosition(ccp(70,500));
	this->addChild(_itemDescLable, 5);



	_itemFrame = CCSprite::create("store/images/click.png");
	_itemFrame->setPosition(CCPointZero);
	_itemFrame->retain();
	_itemFrame->setAnchorPoint(ccp(0,0));
//	_itemFrame->setVisible(false);

	_itemDescarr[0] = "You can earn more money. 110%";
	_itemNamearr[0] = "Brown Ticket";
	_itemPricearr[0] =addComma(110).c_str();

	_itemDescarr[1] = "You can earn more money. 120%";
	_itemNamearr[1] = "Green Ticket";
	_itemPricearr[1] =addComma(120).c_str();

	_itemDescarr[2] = "You can earn more money. 130%";
	_itemNamearr[2] = "Blue Ticket";
	_itemPricearr[2] =addComma(130).c_str();

	_itemDescarr[3] = "You can earn more money. 150%";
	_itemNamearr[3] = "Red Ticket";
	_itemPricearr[3] =addComma(150).c_str();

	_itemDescarr[4] = "You can earn more money. 200%";
	_itemNamearr[4] = "Star Ticket";
	_itemPricearr[4] =addComma(200).c_str();

	_itemDescarr[5] = "You can save 15 Ticket";
	_itemNamearr[5] = "Shoulder Bag";
	_itemPricearr[5] =addComma(50).c_str();

	_itemDescarr[6] = "You can save 20 Ticket";
	_itemNamearr[6] = "Shoulder Bag X 2";
	_itemPricearr[6] =addComma(70).c_str();

	_itemDescarr[7] = "You can save 25 Ticket";
	_itemNamearr[7] = "Backpack";
	_itemPricearr[7] =addComma(100).c_str();

	_itemDescarr[8] = "You can save 30 Ticket";
	_itemNamearr[8] = "TwoPocket Backpack";
	_itemPricearr[8] =addComma(125).c_str();

	_itemDescarr[9] = "You can save 35 Ticket";
	_itemNamearr[9] = "ThreePocket Backpack";
	_itemPricearr[9] = addComma(150).c_str();

	_itemDescarr[10] = "You can get second chance";
	_itemNamearr[10] = "stunning armor";
	_itemPricearr[10] = addComma(100).c_str();

	_itemDescarr[11] = "You can get third chance";
	_itemNamearr[11] = "Bullet Proof";
	_itemPricearr[11] = addComma(300).c_str();

	_itemDescarr[12] = "Not Powerfull Not bad";
	_itemNamearr[12] = "Pistol";
	_itemPricearr[12] = addComma(300).c_str();

	_itemDescarr[13] = "More Powerfull";
	_itemNamearr[13] = "Uzi";
	_itemPricearr[13] = addComma(500).c_str();

	_itemDescarr[14] = "Kill them all";
	_itemNamearr[14] = "Heavy Machine Gun";
	_itemPricearr[14] = addComma(1000).c_str();




	for (int i = 0; i < itemNum; i++) {
		if (count % 5 == 0)
			count = 0;
		std::string temp = CCString::createWithFormat("store/images/item%d.png",
				i + 1)->getCString();
		_itemarr[i] = CCSprite::create(temp.c_str());
		_itemarr[i]->setPosition(ccp(100,900-HEIGHTGAP*count++));
		_itemarr[i]->setTag(i);
		_itemarr[i]->retain();

	}

	_haveMoney = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameMoney");
	CCLog("%d",_haveMoney);
	_haveMoneyLable = CCLabelTTF::create(addComma(_haveMoney).c_str(), "fonts/carre.ttf", 60);
	_haveMoneyLable->setColor(ccc3(255, 255, 255));
	_haveMoneyLable->setAnchorPoint(ccp(1.0,1.0));
	_haveMoneyLable->setPosition(ccp(720,1260));
	_haveMoneyLable->retain();
	this->addChild(_haveMoneyLable);
	_itemPriceLable = CCLabelTTF::create("", "fonts/MarkerFelt.ttf", 60);
	_itemPriceLable->setColor(ccc3(255, 255, 255));
	_itemPriceLable->setAnchorPoint(ccp(0,0));
	_itemPriceLable->setPosition(ccp(30,20));
	_itemPriceLable->retain();

	_storebuyItem = CCMenuItemImage::create("store/images/buyBtn1.png",
			"store/images/buyBtn2.png", this,
			menu_selector(StoreScene::buyMenuClick));
	_storebuyItem->setTag(2);
	_storebuyItem->retain();
	_storebuyItem->addChild(_itemPriceLable, 5);

	_storebuyMenu = CCMenu::create(_storebuyItem, NULL);
	_storebuyMenu->setPosition(ccp(580,270));
	_storebuyMenu->retain();

	_linelayer1 = CCLayerColor::create(ccc4(48, 72, 45, 255));
	_linelayer1->addChild(_itemarr[0]);
	_linelayer1->addChild(_itemarr[1]);
	_linelayer1->addChild(_itemarr[2]);
	_linelayer1->addChild(_itemarr[3]);
	_linelayer1->addChild(_itemarr[4]);
	_linelayer1->setContentSize(CCSizeMake(200,1000));

	scrollView = CCScrollView::create(CCSizeMake(200,500), _linelayer1);
	scrollView->setDirection(kCCScrollViewDirectionVertical);
	scrollView->setContentOffset(
			ccp(0, scrollView->boundingBox().size.height-scrollView->getContentSize().height ),
			true);

	scrollView->setTouchEnabled(true);
	scrollView->setBounceable(false);
	scrollView->setPosition(ccp(50,640));
	this->addChild(scrollView,2);

	_linelayer2 = CCLayerColor::create(ccc4(200, 60, 30, 255));
	_linelayer2->addChild(_itemarr[5]);
	_linelayer2->addChild(_itemarr[6]);
	_linelayer2->addChild(_itemarr[7]);
	_linelayer2->addChild(_itemarr[8]);
	_linelayer2->addChild(_itemarr[9]);
	_linelayer2->setContentSize(CCSizeMake(200,1000));

	scrollView2 = CCScrollView::create(CCSizeMake(200,500), _linelayer2);
	scrollView2->setDirection(kCCScrollViewDirectionVertical);
	scrollView2->setContentOffset(
			ccp(0, scrollView->boundingBox().size.height-scrollView->getContentSize().height ),
			true);
	scrollView2->setTouchEnabled(true);
	scrollView2->setBounceable(false);
	scrollView2->setPosition(ccp(260,640));
	this->addChild(scrollView2,2);

	_linelayer3 = CCLayerColor::create(ccc4(30, 40, 77, 255));
	_linelayer3->addChild(_itemarr[10]);
	_linelayer3->addChild(_itemarr[11]);
	_linelayer3->addChild(_itemarr[12]);
	_linelayer3->addChild(_itemarr[13]);
	_linelayer3->addChild(_itemarr[14]);
	_linelayer3->setContentSize(CCSizeMake(200,1000));

	scrollView3 = CCScrollView::create(CCSizeMake(200,500), _linelayer3);
	scrollView3->setDirection(kCCScrollViewDirectionVertical);
	scrollView3->setContentOffset(
			ccp(0, scrollView->boundingBox().size.height-scrollView->getContentSize().height ),
			true);
	scrollView3->setTouchEnabled(true);
	scrollView3->setBounceable(false);
	scrollView3->setPosition(ccp(470,640));
	this->addChild(scrollView3,2);
	AudioManager::getAudioManager()->playSound(SOUND_STOREAUDIO);
	return true;

}
void StoreScene::backMenuClick(CCObject* pSender) {
	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
	AudioManager::getAudioManager()->stopSound();
	CCScene* reScene = PlayScene::scene();
	CCDirector::sharedDirector()->replaceScene(reScene);
}
void StoreScene::buyMenuClick(CCObject* pSender) {
	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
	if (_itemstate == 0) {
		_haveMoney -= atoi(_itemPricearr[_selectedItem].c_str());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("gameMoney",_haveMoney);
		_haveMoneyLable->setString(addComma(_haveMoney).c_str());
		CCUserDefault::sharedUserDefault()->setIntegerForKey(
				CCString::createWithFormat("item%dState", _selectedItem)->getCString(),
				1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(
				CCString::createWithFormat("line%dEquipped", _seletedLine)->getCString(),
				_selectedItem);
		_storebuyMenu->setEnabled(false);
		_itemPriceLable->setVisible(false);
		_storebuyItem->setNormalImage(
				CCSprite::create("store/images/equipped.png"));
		ItemManager::getItemManager()->setItem(_seletedLine,_selectedItem);
	} else if (_itemstate == 1) {
		CCUserDefault::sharedUserDefault()->setIntegerForKey(
				CCString::createWithFormat("line%dEquipped", _seletedLine)->getCString(),
				_selectedItem);
		_storebuyMenu->setEnabled(false);
		_itemPriceLable->setVisible(false);
		_storebuyItem->setNormalImage(
				CCSprite::create("store/images/equipped.png"));
		ItemManager::getItemManager()->setItem(_seletedLine,_selectedItem);
	}

}

void StoreScene::scrollViewDidScroll(CCScrollView* view) {

}
void StoreScene::scrollViewDidZoom(CCScrollView* view) {

}

void StoreScene::ccTouchesBegan(CCSet *pTouch, CCEvent *pEvent) {
	CCTouch* touch = (CCTouch*) (pTouch->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint temp;
	for (int i = 0; i < itemNum; i++) {
		if (i < 5)
			temp = _linelayer1->convertToWorldSpace(_itemarr[i]->getPosition());
		else if (i < 10)
			temp = _linelayer2->convertToWorldSpace(_itemarr[i]->getPosition());
		else
			temp = _linelayer3->convertToWorldSpace(_itemarr[i]->getPosition());

		if (temp.y > 650 &&temp.y < 1120) {
			CCRect tempRect = CCRect(temp.x - 100, temp.y - 100, 200, 200);
			if (tempRect.containsPoint(location)) {
				_selectedItem = i;
			}
		}
	}

}
void StoreScene::ccTouceshMove(CCSet *pTouch, CCEvent *pEvent) {

}
void StoreScene::ccTouchesEnded(CCSet *pTouch, CCEvent *pEvent) {

	CCTouch* touch = (CCTouch*) (pTouch->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint temp;

	for (int i = 0; i < itemNum; i++) {
		if (i < 5) {
			temp = _linelayer1->convertToWorldSpace(_itemarr[i]->getPosition());
			_seletedLine = 1;
		} else if (i < 10) {
			temp = _linelayer2->convertToWorldSpace(_itemarr[i]->getPosition());
			_seletedLine = 2;
		} else {
			temp = _linelayer3->convertToWorldSpace(_itemarr[i]->getPosition());
			if(i==10||i==11)
			{
				_seletedLine = 3;
			}else
				_seletedLine = 4;
		}

		if (temp.y > 650 &&temp.y < 1120) {
			CCRect tempRect = CCRect(temp.x - 100, temp.y - 100, 200, 200);
			if (tempRect.containsPoint(location)) {
				if (_selectedItem == i) {
					AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
					if (_storebuyMenu->getParent() == NULL) {
						this->addChild(_storebuyMenu, 6);
						}

					if (_itemFrame->getParent() != NULL) {
						_itemFrame->getParent()->removeAllChildren();
					}
					_itemarr[i]->addChild(_itemFrame, 2);
					_itemstate =
							CCUserDefault::sharedUserDefault()->getIntegerForKey(
									CCString::createWithFormat("item%dState",
											_selectedItem)->getCString()); //0 : didn't buy 1: bought
					if (_itemstate == 0) {
						_itemPriceLable->setVisible(true);
						if(_haveMoney<atoi(_itemPricearr[i].c_str()))
						{
							_storebuyMenu->setEnabled(false);
							_storebuyItem->setNormalImage(CCSprite::create("store/images/noMoney.png"));
						}else
						{
							_storebuyMenu->setEnabled(true);
							_storebuyItem->setNormalImage(
									CCSprite::create("store/images/buyBtn1.png"));
							_storebuyItem->setSelectedImage(
									CCSprite::create("store/images/buyBtn2.png"));
						}
					} else if (_itemstate == 1) {
						int isEqupped =
								CCUserDefault::sharedUserDefault()->getIntegerForKey(
										CCString::createWithFormat(
												"line%dEquipped", _seletedLine)->getCString());
						if (isEqupped == _selectedItem) {
							_storebuyMenu->setEnabled(false);
							_itemPriceLable->setVisible(false);
							_storebuyItem->setNormalImage(
									CCSprite::create(
											"store/images/equipped.png"));
						} else {
							_storebuyMenu->setEnabled(true);
							_itemPriceLable->setVisible(false);
							_storebuyItem->setNormalImage(
									CCSprite::create(
											"store/images/toequip.png"));
							_storebuyItem->setSelectedImage(
									CCSprite::create(
											"store/images/toequip2.png"));
						}

						//	CCUserDefault::sharedUserDefault()->setIntegerForKey( CCString::createWithFormat("_item%dState",_selectedItem)->getCString(), 120);

					}
					_itemPriceLable->setString(_itemPricearr[i].c_str());
					_itemNameLable->setString(_itemNamearr[i].c_str());
					_itemDescLable->setString(_itemDescarr[i].c_str());
				}
				break;
			}
		}
	}
}
void StoreScene::ccTouchesCanclled(CCSet *pTouch, CCEvent *pEvent) {

}

void StoreScene::keyBackClicked() {
	AudioManager::getAudioManager()->stopSound();
	CCScene* reScene = PlayScene::scene();
	CCDirector::sharedDirector()->replaceScene(reScene);
	//CCDirector::sharedDirector()->end();
}


std::string StoreScene::addComma(int value)
{
	  std::string result;
	  int cnt = 0;
	  do
	  {
		  result.insert(0, 1, char('0' + value % 10));
		  value /= 10;
	    if (++cnt == 3 && value)
	    {
	    	result.insert(0, 1, ',');
	      cnt = 0;
	    }
	  } while (value);
	  return result;

}
