#pragma execution_character_set("utf-8")

#include "HRocker.h"
const double PI = 3.1415;

HRocker::HRocker(void)
{
	rocketRun = false;
}

HRocker::~HRocker(void)
{
}
//创建摇杆(摇杆的操作题图片资源名，摇杆背景图片资源名，起始坐标)
HRocker* HRocker::createHRocker(const char *rockerImageName, const char *rockerBGImageName, CCPoint position)
{
	HRocker *layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

//自定义初始化函数
void HRocker::rockerInit(const char* rockerImageName, const char* rockerBGImageName, CCPoint position)
{
	CCSprite *spRockerBG = CCSprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	addChild(spRockerBG, 0, tag_rockerBG);//

	CCSprite *spRocker = CCSprite::create(rockerImageName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	addChild(spRocker, 1, tag_rocker);

	rockerBGPosition = position;
	rockerBGR = spRockerBG->getContentSize().width*0.45;//  摇杆大小
	rocketDirection = -1;//表示摇杆方向不变

	
}

//启动摇杆(显示摇杆、监听摇杆触屏事件)
void HRocker::startRocker(bool _isStopOther)
{
	//显示摇杆
	CCSprite *rocker = (CCSprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	CCSprite *rockerBG = (CCSprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
}

//停止摇杆(隐藏摇杆，取消摇杆的触屏监听)
void HRocker::stopRocker()
{
	

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this,false);

}


//获取当前摇杆与用户触屏点的角度
float HRocker::getRad(CCPoint pos1, CCPoint pos2)
{
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	//得到两点x的距离
	float x = px2 - px1;
	//得到两点y的距离
	float y = py1 - py2;
	//算出斜边长度
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	//得到这个角度的余弦值(通过三角函数中的店里：角度余弦值=斜边/斜边)
	float cosAngle = x / xie;
	//通过反余弦定理获取到期角度的弧度
	float rad = acos(cosAngle);
	//注意：当触屏的位置Y坐标<摇杆的Y坐标，我们要去反值-0~-180
	if (py2 < py1)
	{
		rad = -rad;
	}
	return rad;
}

CCPoint getAngelePosition(float r, float angle){
	return ccp(r*cos(angle), r*sin(angle));
}

//抬起事件
bool HRocker::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation(); //获取触摸点
	CCSprite *rocker = (CCSprite *)this->getChildByTag(tag_rocker);  //获取摇杆
	if (rocker->boundingBox().containsPoint(point))
	{
		isCanMove = true;
		//CCLOG("begin");
	}
	return true;
}
//移动事件
void HRocker::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation();//获得手触摸屏幕的位置
	CCSprite *rocker = (CCSprite *)this->getChildByTag(tag_rocker);
	//得到摇杆与触屏点所形成的角度
	float angle = getRad(rockerBGPosition, point);
	//判断两个圆的圆心距是否大于摇杆背景的半径
	if (sqrt(pow((rockerBGPosition.x - point.x), 2) + pow((rockerBGPosition.y - point.y), 2)) >= rockerBGR)
	{

		//保证内部小圆运动的长度限制
		rocker->setPosition(ccpAdd(getAngelePosition(rockerBGR, angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
		//	CCLOG("touch");
	}
	else
	{
		//当没有超过，让摇杆跟随用户触屏点移动即可
		rocker->setPosition(point);
		//CCLOG("touch");
	}

	//判断方向
	if (angle >= -PI / 4 && angle<PI / 4)
	{
		rocketDirection = rocker_right;
		rocketRun = false;
		//CCLOG("%d", rocketDirection);
	}
	else if (angle >= PI / 4 && angle<3 * PI / 4)
	{
		rocketDirection = rocker_up;
		//CCLOG("%d", rocketDirection);
	}
	else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI&&angle<-3 * PI / 4))
	{
		rocketDirection = rocker_left;
		rocketRun = true;
		//CCLOG("%d", rocketDirection);
	}
	else if (angle >= -3 * PI / 4 && angle<-PI / 4)
	{
		rocketDirection = rocker_down;
		/*CCLOG("%d", rocketDirection);*/
	}

	

}
//离开事件
void HRocker::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

	
	

	if (!isCanMove)
	{
		return;
	}
	CCSprite *rockerBG = (CCSprite*)this->getChildByTag(tag_rockerBG);
	CCSprite * rocker = (CCSprite*)this->getChildByTag(tag_rocker);
	rocker->stopAllActions();
	rocker->runAction(CCMoveTo::create(0.04f, rockerBG->getPosition()));
	isCanMove = false;
	rocketDirection = rocker_stay;
	/*CCLOG("%d", rocketDirection);
	CCLOG("end");*/
}

void HRocker::resumeState()
{
	CCSprite *rockerBG = (CCSprite*)this->getChildByTag(tag_rockerBG);
	CCSprite * rocker = (CCSprite*)this->getChildByTag(tag_rocker);
	rocker->stopAllActions();
	rocker->runAction(CCMoveTo::create(0.08f, rockerBG->getPosition()));
	isCanMove = false;
	rocketDirection = rocker_stay;
}

void HRocker::update(float dt)
{
	if (isCanMove)
	{

	}
}
