#include "PopLayer.h"
#include "PlayScene.h"

using namespace cocos2d;

CCScene* PopLayer::scene()
{
    CCScene *scene = CCScene::create();

    PopLayer *layer = PopLayer::create();

    scene->addChild(layer);

    return scene;
}
bool PopLayer::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(20, 20, 20, 200)) )  //�����ϰ�
    {
        return false;
    }
	this->setTouchEnabled(true);//��ġ Ȱ��ȭ
	////////////////////////
	CCString* popParam=CCString::create("0");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //��Ƽ�����̼� ������
	back=CCSprite::create("gameplay/images/pause.png");
	back->setPosition(ccp(720/2,1280/2));
	this->addChild(back,10);
    return true;
}
void PopLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *event)
{
	CCLog("out");
	CCSetIterator it= pTouches->begin();
		CCTouch *touch=(CCTouch*)(*it);
		CCPoint location=touch->getLocation();
		CCRect temp=back->boundingBox();
		if(temp.containsPoint(location))
		{
			CCLog("in");
			doClose();
		}
}


void PopLayer::doClose()
{
	CCLog("wdfwdf");
	CCString* popParam=CCString::create("1");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //��Ƽ�����̼� ������

	//�˾�â ����
	this->removeFromParentAndCleanup(true);

}
