// GameObject.h
#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "cocos2d.h"
#include "box2d.h"
 using namespace cocos2d;
 #define PTM_RATIO 32

class GameObject : public CCNode {
public:
	CCSprite* getSprite();

	b2Body* getBody();
	void createBox2dObject(b2World* world);

	GameObject();
	static GameObject* retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName);
	void updateTrail();
private:
		int colourer;

protected:
	    b2Body *body;
		CCSprite* sprite;
};
#endif