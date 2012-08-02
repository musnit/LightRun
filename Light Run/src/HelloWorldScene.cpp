#include "HelloWorldScene.h"
#include "Light.h"
#include "cocos2d.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	//Load Spritesheets
	_batchNode = CCSpriteBatchNode::batchNodeWithFile("runner.png");
	this->addChild(_batchNode);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("runner.plist");
 
	// Construct a world object, which will hold and simulate the rigid bodies.
b2Vec2 gravity;
gravity.Set(0.0f, -10.0f);
world = new b2World(gravity);
 world->SetContinuousPhysics(true);

	//Create Individual sprites for objects that will persist all game
	 winSize = CCDirector::sharedDirector()->getWinSize();
		
	//player
	_player = GameObject::retainedObjectWithSpriteFrameName("stander.png");
	_player->getSprite()->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.1));
	_batchNode->addChild(_player->getSprite(), 1);
	_player->createBox2dObject(world);
	

	//animation
	CCAnimation *animation = CCAnimation::animation();
	animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner1.png"));
	animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner2.png"));
	animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner3.png"));
	CCAnimate *theAnim = CCAnimate::actionWithDuration(0.6f,animation,false); 
	_player->getSprite()->runAction(CCRepeatForever::actionWithAction(theAnim));   

	//boss
	_boss = GameObject::retainedObjectWithSpriteFrameName("boss2.png");
	_boss->getSprite()->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.1));
	_batchNode->addChild(_boss->getSprite(), 1);
	_boss->createBox2dObject(world);
	//animation
	CCFiniteTimeAction* actionTo = CCMoveTo::actionWithDuration( 2 ,ccp(winSize.width * 0.9, winSize.height * 0.9));
	CCFiniteTimeAction* actionFrom = CCMoveTo::actionWithDuration( 2 ,ccp(winSize.width * 0.9, winSize.height * 0.1));
	_boss->getSprite()->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(actionTo, actionFrom, NULL))));
	//Register for touches and gameloop
	this->setIsTouchEnabled(true) ;
	this->scheduleUpdate();
	move=true;
	spawnrate=3;
	return true;
}
void HelloWorld::update(ccTime dt) {

	_player->updateTrail();

	if(move==false){
		spawnrate+=dt;
		if(spawnrate>=1){
			spawnrate=0.5;
			CCActionManager::sharedManager()->resumeTarget(_boss->getSprite());
			move=true;
		}
	}
	else{
		spawnrate-=dt;
		if((spawnrate<=0)&&(_boss->getSprite()->getPositionY()<winSize.height*0.1+0.5*winSize.height)){//err:doesn't account for change in players height on new platform
			Light* test = Light::retainedLight();
			test->setPosition(ccp(_boss->getSprite()->getPositionX()+50, _boss->getSprite()->getPositionY()));
			this->addChild(test);	
			test->runAction(CCSequence::actions(CCMoveBy::actionWithDuration( 4 ,ccp(-winSize.width*1.5, 0)),CCCallFunc::actionWithTarget(test,callfunc_selector(Light::removeFromParentAndCleanup)), NULL));
			spawnrate=0;
			CCActionManager::sharedManager()->pauseTarget(_boss->getSprite());
			move=false;
			CCLog("%i", this->getChildrenCount());//err:gameobjects arent autoreleased(coz it doesnt work dunno wtf- cocos releases them too early maybe?) so makesure to release when done - check/confirm memusage with this print
		}
	}
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	if(_player->getSprite()->getPositionY()==0.1*winSize.height){//err:doesn't account for change in players height on new platform
		_player->getSprite()->runAction(CCJumpBy::actionWithDuration(1.0f,ccp(0,0),0.6f*winSize.height,1));
	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
