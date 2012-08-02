#include "Player.h"


Player::Player(void)
{
	GameObject::GameObject();
}


void Player::moveRight(){
    b2Vec2 impulse = b2Vec2(7.0f, 0.0f);
    this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());		
}
 
void Player::jump(){
    b2Vec2 impulse = b2Vec2(4.0f, 15.0f);
    this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());		    
}