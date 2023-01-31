/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "projectile.h"


Projectile::Projectile() : Entity()
{
	this->addSprite("assets/bullet.tga");
	this->sprite()->color = WHITE;
	this->scale = Point2(1.5, 1.5);
	dead = false;
	pierceEnemyCount = 0;
	
}

Projectile::~Projectile()
{

}



void Projectile::update(float deltaTime)
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
	speed = 1000 * deltaTime;
	currentRotation = this->rotation.z * 180 / PI;
	currentRotation = fmod(currentRotation, 180);


	this->position += Point2(1000, 1000) * Point2(cos(this->rotation.z), sin(this->rotation.z)) * deltaTime;







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
