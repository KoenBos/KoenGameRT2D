/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "enemy.h"
#include "collider.h"

Enemy::Enemy(Player* player) : Entity()
{
	this->addSprite("assets/enemy.tga");
	this->sprite()->color = WHITE;
	this->scale = Point2(0.75, 0.75);
	_player = player;
	health = 3;
	canBeHit = true;
	lastHitTime = 0;
	better = false;
	speed = 40 + (player->CurrentWave);
	speedup = false;
}

Enemy::~Enemy()
{

}


void Enemy::update(float deltaTime)
{
	if (better == true)
	{
		this->sprite()->color = RED;
		this->position += Point2(speed * 2.5, speed * 2.5) * Point2(cos(this->rotation.z), sin(this->rotation.z)) * deltaTime;
	}
	else
	{
		this->position += Point2(speed, speed) * Point2(cos(this->rotation.z), sin(this->rotation.z)) * deltaTime;
	}
	float playerangle = atan2(_player->position.y - this->position.y, _player->position.x - this->position.x);
	this->rotation.z = playerangle;






	//Rectangle hitbox = Rectangle(this->position.x, this->position.y, 100, 100);




	//if (input()->getKey(KeyCode::A)) {
	//	this->position -= Point3(speed, 0, 0);
	//}
	//if (input()->getKey(KeyCode::D)) {
	//	this->position += Point3(speed, 0, 0);
	//}


	// //###############################################################
	// //Rotate color
	// //###############################################################
	//if (t.seconds() > 0.0333f) {
	//	RGBAColor color = this->sprite()->color;
	//	this->sprite()->color = Color::rotate(color, 0.01f);
	//	t.start();
	//}
	 //###############################################################
	 //Rotate
	 //###############################################################
	//this->rotation.z += angle * deltaTime; // 90 deg/sec
	//if (this->rotation.z > TWO_PI) {
	//	this->rotation.z -= TWO_PI;
	//}
}
