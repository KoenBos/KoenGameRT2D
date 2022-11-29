/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "enemy.h"

Enemy::Enemy() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = WHITE;
	this->scale = Point2(0.8, 0.8);
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
