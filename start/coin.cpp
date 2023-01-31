/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "coin.h"

Coin::Coin(Player* player) : Entity()
{
	this->addSprite("assets/coin.tga");
	this->scale = Point2(1.2, 1.2);
	followspeed = 500;
	_player = player;
	followplayer = false;
}

Coin::~Coin()
{

}


void Coin::update(float deltaTime)
{
	if (followplayer == true)
	{
		float playerangle = atan2(_player->position.y - this->position.y, _player->position.x - this->position.x);
		this->rotation.z = playerangle;

		this->position += Point2(followspeed, followspeed) * Point2(cos(this->rotation.z), sin(this->rotation.z)) * deltaTime;
	}

}
