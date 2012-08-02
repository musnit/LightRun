// Player.h

#ifndef PLAYER
#define PLAYER

#include "cocos2d.h"
#include "Box2D.h"
#include "GameObject.h"
 
class Player : public GameObject {
public:
	Player();
	void jump();
	void moveRight();
};
  
#endif