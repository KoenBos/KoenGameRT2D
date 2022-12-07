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
	this->scale = Point2(1, 1);
	_player = player;
	
}

Enemy::~Enemy()
{

}


void Enemy::update(float deltaTime)
{
	// ###############################################################
	// Spacebar scales myentity
	// ###############################################################
	//if (input()->getKeyDown(KeyCode::Space)) {
	//	this->scale = Point(0.5f, 0.5f);
	//}
	//if (input()->getKeyUp(KeyCode::Space)) {
	//	this->scale = Point(1.0f, 1.0f);
	//}
	// ###############################################################
	// WS moves myentity
	// ###############################################################
	speed = 100 * deltaTime;
	currentRotation = this->rotation.z * 180 / PI;
	currentRotation = fmod(currentRotation, 180);

	this->position.x += (cos(0.017453277777 * currentRotation)) * (speed / 3);
	this->position.y += (sin(0.017453277777 * currentRotation)) * (speed / 3);


	float playerangle = atan2(_player->position.y - this->position.y, _player->position.x - this->position.x) * 180.0 / PI;
	this->rotation.z = playerangle * PI / 180;

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
