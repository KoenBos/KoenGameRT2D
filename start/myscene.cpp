/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include "myscene.h"
#include "collider.h"


MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	player = new Player();
	player->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	


	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(player);
	
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(player);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete player;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}
	//mouse coordinates --#########################################
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	Point2 mouse = Point2(mousex, mousey);
	//#############################################################

	if (input()->getMouseDown(0) && !power) {
		projectile = new Projectile();
		this->addChild(projectile);
		projectiles.push_back(projectile);
		projectile->position = player->position;
		projectile->rotation.z = player->rotation.z;
	}
	if (input()->getMouse(0) && power) {
		projectile = new Projectile();
		this->addChild(projectile);
		projectiles.push_back(projectile);
		projectile->position = player->position;
		projectile->rotation.z = player->rotation.z;
	}
	if (input()->getKey(KeyCode::LeftShift)) {power = true;}else{power = false;}

	if (input()->getKeyDown(KeyCode::E)) {
		enemy = new Enemy(player);
		this->addChild(enemy);
		enemys.push_back(enemy);
		enemy->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	}

	// create shapes ('colliders')

	//for (int i = 0; i < projectiles.size(); i++)
	//{
	//	if (projectiles[i]->position.x > SWIDTH || projectiles[i]->position.x < 0 || projectiles[i]->position.y < 0 || projectiles[i]->position.y > SHEIGHT) {
	//		this->removeChild(projectiles[i]);
	//		delete projectiles[i];
	//		projectiles.erase(projectiles.begin() + i);
	//		std::cout << "delete" << std::endl;
	//	}
	//}
	for (int i = projectiles.size()-1; i >= 0; i--)
	{
		if (projectiles[i]->position.x > SWIDTH || projectiles[i]->position.x < 0 || projectiles[i]->position.y < 0 || projectiles[i]->position.y > SHEIGHT) {
			this->removeChild(projectiles[i]);
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			std::cout << "deleteie" << std::endl;
		}
	}
	
	

	//########-- Calculate Rotation with Atan2 --###############

	/*Point2 Direction = Point2(player->position - mouse);
	float angle = atan2(Direction.x, Direction.y);*/

	//player->rotation.z = angle - angle * 2;
	//It's just

	///////////////////////////////////////////////////////////deltaY = mouse.y - player->position.y;
	///////////////////////////////////////////////////////////deltaX = mouse.x - player->position.x;

	/////////////////////////////////////////////////////////////angle = atan2(mouse.y - player->position.y, mouse.x - player->position.x) * 180 / PI;

	//if (deltaY < 0 && deltaX < 0) {
	//	angle = -atan2(deltaY, deltaX)- PI;// *180.0 / PI;
	//}
	//else
	//{
	//	angle = atan2(deltaY, deltaX);
	//}

	///////////////////////////////////////////////////////////player->rotation.z = angle * PI / 180;

	//float angleDifference = fmod(angle - player->currentRotation + 1800, 720) - 360;
	
	// Calculate the angle between the tank and the mouse cursor
	float mouseX = mouse.x;
	float mouseY = mouse.y;
	float tankX = player->position.x;
	float tankY = player->position.y;
	float targetAngle = atan2(mouseY - tankY, mouseX - tankX);

	// If the x-coordinate of the mouse cursor is negative, add 2 to the target angle
	if (mouseX < 0) {
		targetAngle += 2 * PI;
	}

	// Calculate the difference between the current rotation and the target angle
	float currentRotation = player->rotation.z;
	float rotationDifference = targetAngle - currentRotation;

	// Clamp the rotation difference to a maximum value
	float maxRotationDifference = 1 * deltaTime; // you can adjust this value to control the speed of rotation
	float rotationDiff = std::max(-maxRotationDifference, std::min(rotationDifference, maxRotationDifference));

	//Copyright 2022 JARNO Dijk en Joas heeft toegekeken.
	if (currentRotation > 0.25 * PI && rotationDifference < -PI)
	{
		rotationDiff = maxRotationDifference;
	}
	if (currentRotation < -0.25 * PI && rotationDifference > PI)
	{
		rotationDiff = -maxRotationDifference;
	}

	// Set the new rotation of the tank based on the difference between the current and target angles
	player->rotation.z = (currentRotation + rotationDiff);
	if (currentRotation > PI)
	{
		player->rotation.z = -3.14;
	}
	if (currentRotation < -PI)
	{
		player->rotation.z = 3.14;
	}
	//End of copyright JARNO Dijk en Joas die heeft toegekeken.

	




	//if (angle < player->rotation.z) {
	//	player->rotation.z -= 0.001;
	//}
	//else if(angle > player->rotation.z){
	//	player->rotation.z += 0.001;
	//}


	std::cout << player->rotation.z << std::endl;
	

	// ############-- Draw border and lazer --##################std::cout << angleDifference << std::endl;
	ddClear();
	ddLine(player->position.x, player->position.y, mousex, mousey, RED);
	ddCircle(mousex, mousey, 10, RED);
	int border = 10;
	ddSquare(border, border, SWIDTH - (border * 2), SHEIGHT - (border * 2), WHITE);
}//###################################################################
