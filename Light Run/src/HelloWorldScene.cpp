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
 
	//Create Individual sprites for objects that will persist all game
	 winSize = CCDirector::sharedDirector()->getWinSize();
		
	//player
	_player = (TrailedCCSprite*)CCSprite::spriteWithSpriteFrameName("stander.png");
	_player->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.1));
	_batchNode->addChild(_player, 1);

	//shaderstuff
	/*const GLchar * fragmentSource = (GLchar*)CCFileUtils.fullPathFromRelativePath("CSEGrass.fsh") ;
		_player.shaderProgram = CCGLProgram.alloc().initWithVertexShaderByteArray(ccPositionTextureA8Color_vert,fragmentSource);
														  //fragmentShaderByteArray:;
		_player.shaderProgram.addAttribute(kCCAttributeNamePosition.index(kCCVertexAttrib_Position));
		_player.shaderProgram.addAttribute(kCCAttributeNameTexCoord.index(kCCVertexAttrib_TexCoords));
		_player.shaderProgram.link();
		_player.shaderProgram.updateUniforms();
		
		// 3
		timeUniformLocation = glGetUniformLocation(_player.shaderProgram->program_, "u_time");

		// 5
		_player.shaderProgram.use();
		*/
	//animation
	CCAnimation *animation = CCAnimation::animation();
	animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner1.png"));
	animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner2.png"));
	animation->addFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner3.png"));
	CCAnimate *theAnim = CCAnimate::actionWithDuration(0.6f,animation,false); 
	_player->runAction(CCRepeatForever::actionWithAction(theAnim));   

	//boss
	_boss = (TrailedCCSprite*)CCSprite::spriteWithSpriteFrameName("boss.png");
	_boss->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.1));
	_batchNode->addChild(_boss, 1);
	
	//animation
	CCFiniteTimeAction* actionTo = CCMoveTo::actionWithDuration( 2 ,ccp(winSize.width * 0.9, winSize.height * 0.9));
	CCFiniteTimeAction* actionFrom = CCMoveTo::actionWithDuration( 2 ,ccp(winSize.width * 0.9, winSize.height * 0.1));
	_boss->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(actionTo, actionFrom, NULL))));
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
			spawnrate=3;
			CCActionManager::sharedManager()->resumeTarget(_boss);
			move=true;
		}
	}
	else{
		spawnrate-=dt;
		if((spawnrate<=0)&&(_boss->getPositionY()<winSize.height*0.1+0.5*winSize.height)){//err:doesn't account for change in players height on new platform
			Light* test = new Light();
			test->setPosition(ccp(_boss->getPositionX()+50, _boss->getPositionY()));
			this->addChild(test);	
			test->runAction(CCSequence::actions(CCMoveBy::actionWithDuration( 4 ,ccp(-winSize.width*1.5, 0)),CCCallFunc::actionWithTarget(test,callfunc_selector(Light::removeFromParentAndCleanup)), NULL));
			spawnrate=0;
			CCActionManager::sharedManager()->pauseTarget(_boss);
			move=false;
		}
	}
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	if(_player->getPositionY()==0.1*winSize.height){//err:doesn't account for change in players height on new platform
		_player->runAction(CCJumpBy::actionWithDuration(1.0,ccp(0,0),0.6*winSize.height,1));
	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
