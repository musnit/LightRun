#include "Light.h"

using namespace cocos2d;

Light::Light()
{
	CCNode::CCNode();

}

void Light::draw(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	glLineWidth( 5.0f );
	glColor4ub(255,0,0,255);
	ccDrawLine( ccp(-50,0), ccp(MIN(winSize.width*0.9-getPositionX(),50),0));
	
	glLineWidth(1);
	glColor4ub(255,255,255,255);

}

void Light::removeFromParentAndCleanup(){
	CCNode::removeFromParentAndCleanup(true);
}