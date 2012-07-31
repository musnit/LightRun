
#include "cocos2d.h"
using namespace cocos2d;

class TrailedCCSprite : public CCSprite
{
private:
	int colourer;
public:
	TrailedCCSprite();
	virtual void draw();
	virtual void spriteWithSpriteFrameName(const char* pszSpriteFrameName);
	void updateTrail();
};