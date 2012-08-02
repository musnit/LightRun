#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "TrailedCCSprite.h"
#include "GameObject.h"

#define PTM_RATIO 32

using namespace cocos2d;

class HelloWorld : public CCLayer
{
private:
	bool move;
	float spawnrate;
	CCSpriteBatchNode * _batchNode;
	GameObject* _player;
	GameObject* _boss;
	void update(ccTime dt);
	CCSize winSize;
	b2World* world;

public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	
	virtual void ccTouchesBegan(CCSet* touches, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
