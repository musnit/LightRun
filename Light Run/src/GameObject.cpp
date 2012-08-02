#include "GameObject.h"

using namespace cocos2d;

GameObject::GameObject()
{
		this->colourer=1;

    CCNode::CCNode();
}

GameObject* GameObject::retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName )
{
	GameObject *obj = new GameObject();
    if (obj->sprite=CCSprite::spriteWithSpriteFrameName(pszSpriteFrameName))
    {
		obj->colourer=1;
        return obj;
    }
    CC_SAFE_DELETE(obj);
	return NULL;
}

	CCSprite* GameObject::getSprite(){
		return this->sprite;
	}

	b2Body* GameObject::getBody(){
		return this->body;	
	}

	void GameObject::createBox2dObject(b2World* world) {
    b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(this->sprite->getPosition().x/PTM_RATIO, this->sprite->getPosition().y/PTM_RATIO);
	playerBodyDef.userData = this;
	playerBodyDef.fixedRotation = true;
 
	this->body = world->CreateBody(&playerBodyDef);
 
	   b2PolygonShape dynamicBox;
	   dynamicBox.SetAsBox((this->sprite->getContentSizeInPixels().width/PTM_RATIO)/2, (this->sprite->getContentSizeInPixels().height/PTM_RATIO)/2);//These are mid points for our 1m box err:if object is scaled/rotated this will bug out

//	b2CircleShape circleShape;
	//circleShape.m_radius = 0.7f; 
	   //err:change collision&other paramaters
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution =  0.0f;
	this->body->CreateFixture(&fixtureDef);
}

	void GameObject::updateTrail(){
		this->sprite->removeAllChildrenWithCleanup(1);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* head = CCSprite::spriteWithSpriteFrame( this->sprite->displayedFrame()); 
		head->setPosition(ccp(this->sprite->getContentSize().width/2, this->sprite->getContentSize().height/2));
		this->sprite->addChild(head, 9999);
for(int i=1;i<40;i++){//needs to loop to end of screen or based on motion
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* trail = CCSprite::spriteWithSpriteFrame( this->sprite->displayedFrame()); 
		trail->setPosition(ccp(this->sprite->getContentSize().width/2-i, this->sprite->getContentSize().height/2));
		_ccColor3B color = {20*(colourer+i),10*(colourer+i),50*(colourer+i)};
		trail->setColor(color);
		this->sprite->addChild(trail, 20-i);
		if (colourer==8){
			colourer=1;
			}
		else{
				colourer++;
		}
	}

	

}
 
