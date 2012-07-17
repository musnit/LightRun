
#include "cocos2d.h"
using namespace cocos2d;

class Light : public CCNode
{
public:
	Light();
	virtual void draw();
	virtual void removeFromParentAndCleanup();
};