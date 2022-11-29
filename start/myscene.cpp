/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include "myscene.h"


MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	player = new Player();
	player->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	enemy = new Enemy();
	enemy->position = Point2(SWIDTH / 2, SHEIGHT / 2);




	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(player);
	this->addChild(enemy);
	
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

	if (input()->getKey(KeyCode::LeftShift)) {
		power = true;
	}
	else {
		power = false;
	}
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->position.x > SWIDTH || projectiles[i]->position.x < 0 || projectiles[i]->position.y < 0 || projectiles[i]->position.y > SHEIGHT) {
			this->removeChild(projectiles[i]);
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			std::cout << "delete" << std::endl;
		}
	}
	
	

	//########-- Calculate Rotation with Atan2 --###############

	/*Point2 Direction = Point2(player->position - mouse);
	float angle = atan2(Direction.x, Direction.y);*/

	//player->rotation.z = angle - angle * 2;
	//It's just
	float angle = atan2(mouse.y - player->position.y, mouse.x - player->position.x) *180.0 / PI;

	//float angleDifference = fmod(angle - player->currentRotation + 1800, 720) - 360;


	player->rotation.z = angle * PI/180;

	//if (angleDifference < 0) {
	//	player->rotation.z -= 0.001;
	//}
	//else if(angleDifference > 0){
	//	player->rotation.z += 0.001;
	//}


	//std::cout <<  << std::endl;
	

	// ############-- Draw border and lazer --##################std::cout << angleDifference << std::endl;
	ddClear();
	ddLine(player->position.x, player->position.y, mousex, mousey, RED);
	ddCircle(mousex, mousey, 10, RED);
	int border = 10;
	ddSquare(border, border, SWIDTH - (border * 2), SHEIGHT - (border * 2), WHITE);
}//###################################################################
