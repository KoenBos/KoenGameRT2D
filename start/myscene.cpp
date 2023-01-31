/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <time.h>
#include "myscene.h"
#include "collider.h"


MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();
	srand(time(NULL));

	// 4 spawners for the enemies locations
	spawner_Top = new BasicEntity();
	spawner_Down = new BasicEntity();
	spawner_Left = new BasicEntity();
	spawner_Right = new BasicEntity();

	this->addChild(spawner_Top);
	this->addChild(spawner_Down);
	this->addChild(spawner_Left);
	this->addChild(spawner_Right);


	spawner_Top->position = Point2(SWIDTH / 2.5, -250);
	spawner_Down->position = Point2(SWIDTH / 2.5, SHEIGHT + 250);
	spawner_Left->position = Point2(-500, SHEIGHT / 2.5);
	spawner_Right->position = Point2(SWIDTH + 400, SHEIGHT / 2.5);
	

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	background = new BasicEntity();
	healthbar = new BasicEntity();
	healthbarback = new BasicEntity();
	backlayer = new BasicEntity();
	bottomlayer = new BasicEntity();
	moneytext = new Text();
	wavetext = new Text();
	endtext = new Text();
	endtextback = new Text();

	//Player
	player = new Player();
	player->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	//Coins

	
	UI_Back = new BasicEntity();
	UI_Front = new BasicEntity();

	startScreen = new BasicEntity();
	startbackground = new BasicEntity();


	upgrade_background = new BasicEntity();
	wave_background = new BasicEntity();

	this->addChild(background);
	this->addChild(bottomlayer);
	this->addChild(player);
	this->addChild(backlayer);
	this->addChild(UI_Back);
	this->addChild(UI_Front);
	this->addChild(startbackground);
	this->addChild(startScreen);

	//end text
	endtext->message("GAME OVER", RED);
	endtext->scale = Point2(2, 2);
	endtext->position = Point2(SWIDTH / 2 - 250,SHEIGHT/2 - 20);

	endtextback->message("GAME OVER", WHITE);
	endtextback->scale = Point2(2.06, 2.06);
	endtextback->position = Point2(SWIDTH / 2 - 256, SHEIGHT / 2 - 20);

	//wave background:
	wave_background->addSprite("assets/square.tga");
	wave_background->position = Point2(SWIDTH / 2, 20);
	wave_background->scale = Point2(1.1, 0.2);
	UI_Back->addChild(wave_background);

	//upgrades background:
	upgrade_background->addSprite("assets/square.tga");
	upgrade_background->scale = Point2(4.1, 0.9);
	upgrade_background->position = Point2(SWIDTH - 430, SHEIGHT - 110);
	UI_Back->addChild(upgrade_background);
	upgrade_background->sprite()->pivot = Point2(0,0);

	UI_Back->addChild(healthbarback);
	UI_Front->addChild(healthbar);
	UI_Front->addChild(moneytext);
	UI_Front->addChild(wavetext);

	background->addSprite("assets/background.tga");
	background->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	background->scale = Point2(2.6, 2.85);

	//healthbar
	healthbarback->addSprite("assets/square.tga");
	healthbarback->sprite()->pivot = Point2(0, 0);
	healthbarback->position = Point2(0, 0);
	healthbarback->scale = Point2(2, 0.3);
	healthbarback->sprite()->color = RED;

	healthbar->addSprite("assets/square.tga");
	healthbar->sprite()->pivot = Point2(0, 0);
	healthbar->position = Point2(0, 0);
	healthbar->scale = Point2(2, 0.3);
	healthbar->sprite()->color = GREEN;

	//waves and text of Wave
	currentWave = 0;
	enemiesPerWave = 5;
	wavetext->message("Wave: 1", BLUE);
	wavetext->scale = Point2(0.5f, 0.5f);
	wavetext->position = Point2(SWIDTH/2-50, 20);

	
	//Money score text
	money = 0;
	moneytext->message("Money: 0", GREEN);
	moneytext->scale = Point2(0.45f, 0.45f);
	moneytext->position = Point2(20, 55);

	//shoot delay
	canShoot = true;
	shootDelay = 0.8; // delay in seconds
	lastShotTime = 0;

	//hit delay and piecing
	hitDelay = 0.14;
	piecingcount = 1;

	//rotate speed
	rotatespeed = 1.3;


	//start stuff
	startbackground->addSprite("assets/background.tga");
	startbackground->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	startbackground->scale = Point2(2.6, 2.85);
	nextwave = true;
	

	startGame = false;

	//Buttons -------------------------------------------

	//START BUTTON
	startButton = new ImageButton("", -1);
	startScreen->addChild(startButton);
	startButton->position = Point2(SWIDTH /2 - 256, SHEIGHT /2 - 64);
	startButton->setCallbackFunction(std::bind(&MyScene::startgame, this));
	startButton->pricetext->scale = Point2(0,0);

	//NEXTWAVE BUTTON
	nextwaveButton = new ImageButton(" ", -1);
	nextwaveButton->position = Point2(SWIDTH - 132, SHEIGHT - 145);
	nextwaveButton->setCallbackFunction(std::bind(&MyScene::nextwavefunction, this));
	nextwaveButton->pricetext->scale = Point2(0, 0);

	//FIRERATE UPGRADE
	firerateButton = new ImageButton("Firerate", 10);
	UI_Front->addChild(firerateButton);
	firerateButton->position = Point2(SWIDTH -80, SHEIGHT -70);
	firerateButton->setCallbackFunction(std::bind(&MyScene::clickfirerate, this));

	//ROTATE SPEED UPGRADE
	rotatespeedButton = new ImageButton("Rotation", 5);
	UI_Front->addChild(rotatespeedButton);
	rotatespeedButton->position = Point2(SWIDTH - 190, SHEIGHT - 70);
	rotatespeedButton->setCallbackFunction(std::bind(&MyScene::clickrotatespeed, this));

	//PIERCING UPGRADE
	piercingButton = new ImageButton("Piercing", 30);
	UI_Front->addChild(piercingButton);
	piercingButton->position = Point2(SWIDTH - 300, SHEIGHT - 70);
	piercingButton->setCallbackFunction(std::bind(&MyScene::clickpiercing, this));

	//SPEED UPGRADE
	speedButton = new ImageButton("Speed", 8);
	UI_Front->addChild(speedButton);
	speedButton->position = Point2(SWIDTH - 410, SHEIGHT - 70);
	speedButton->setCallbackFunction(std::bind(&MyScene::clickspeed, this));
}

MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(player);
	delete player;

	this->removeChild(spawner_Top);
	this->removeChild(spawner_Down);
	this->removeChild(spawner_Left);
	this->removeChild(spawner_Right);
	delete spawner_Top;
	delete spawner_Down;
	delete spawner_Left;
	delete spawner_Right;


	// delete myentity from the heap (there was a 'new' in the constructor)
}

void MyScene::clickfirerate() {
	static int price = 10;
	if (money >= price)
	{
		if (shootDelay >= 0.2) {

			//upgrade and remove money
			shootDelay -= 0.1;
			money -= price;
			price *= 1.5;
			//update money text
			std::string prefix = "Money: ";
			std::ostringstream fullString;
			fullString << prefix << money;
			moneytext->message(fullString.str(), GREEN);

			std::string prefix2 = "Price: ";
			std::ostringstream fullString2;
			fullString2 << prefix2 << price;
			firerateButton->pricetext->message(fullString2.str(), BLUE);
		}
	}
}
void MyScene::clickrotatespeed() {
	static int price = 5;
	if (money >= price)
	{

		//upgrade and remove money
		rotatespeed += 0.5;
		money -= price;
		price *= 1.5;
		//update money text
		std::string prefix = "Money: ";
		std::ostringstream fullString;
		fullString << prefix << money;
		moneytext->message(fullString.str(), GREEN);

		std::string prefix2 = "Price: ";
		std::ostringstream fullString2;
		fullString2 << prefix2 << price;
		rotatespeedButton->pricetext->message(fullString2.str(), BLUE);
	}
}

void MyScene::clickpiercing() {
	static int price = 30;
	if (money >= price)
	{

		//upgrade and remove money
		piecingcount++;
		money -= price;
		price *= 1.5;
		//update money text
		std::string prefix = "Money: ";
		std::ostringstream fullString;
		fullString << prefix << money;
		moneytext->message(fullString.str(), GREEN);

		std::string prefix2 = "Price: ";
		std::ostringstream fullString2;
		fullString2 << prefix2 << price;
		piercingButton->pricetext->message(fullString2.str(), BLUE);
	}
}

void MyScene::clickspeed() {
	static int price = 8;
	if (money >= price)
	{

		//upgrade and remove money
		player->speed += 20;
		money -= price;
		price *= 1.3;
		//update money text
		std::string prefix = "Money: ";
		std::ostringstream fullString;
		fullString << prefix << money;
		moneytext->message(fullString.str(), GREEN);

		std::string prefix2 = "Price: ";
		std::ostringstream fullString2;
		fullString2 << prefix2 << price;
		speedButton->pricetext->message(fullString2.str(), BLUE);
	}
}

void MyScene::startgame() {
	startGame = true;
	startScreen->removeChild(startButton);
	this->removeChild(startbackground);
}

void MyScene::nextwavefunction() {
	nextwave = true;
	UI_Front->removeChild(nextwaveButton);
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


	//shooting with delay
	if (canShoot) {
		if (input()->getMouse(0)) {

			projectile = new Projectile();
			backlayer->addChild(projectile);
			projectiles.push_back(projectile);
			projectile->position = player->position;
			projectile->rotation.z = player->rotation.z;
			player->position -= Point2(10, 10) * Point2(cos(player->rotation.z), sin(player->rotation.z));

			canShoot = false;
			lastShotTime = clock();
		}
	}
	else {
		if ((clock() - lastShotTime) / CLOCKS_PER_SEC >= shootDelay) {
			canShoot = true;
		}
	}


	//if (input()->getMouseDown(0)) {
	//	projectile = new Projectile();
	//	backlayer->addChild(projectile);
	//	projectiles.push_back(projectile);
	//	projectile->position = player->position;
	//	projectile->rotation.z = player->rotation.z;
	//	player->position -= Point2(10, 10) * Point2(cos(player->rotation.z), sin(player->rotation.z));
	//}

	//nextwave button
	if (enemys.size() == 0) {
		UI_Front->addChild(nextwaveButton);
	}
	else {
		UI_Front->removeChild(nextwaveButton);
	}

	//spawn enemies
	if (nextwave == true && enemys.size() == 0) {
		for (int i = enemiesPerWave; i >= 1; i--)
		{
			enemy = new Enemy(player);
			backlayer->addChild(enemy);
			Point2 random = Point2(rand() % SWIDTH * 0.4f, rand() % SHEIGHT * 0.2f); //Random position 
			enemys.push_back(enemy);


			std::random_device rd; // random device engine
			std::mt19937 rng(rd()); // Mersenne Twister 19937 generator
			std::uniform_int_distribution<int> uni(1, 4); // uniformly distributed in range [1, 4]
			int spawnLocation = uni(rng);
			if (spawnLocation == 1) {
				std::cout << "Top" << std::endl;
				enemy->position = spawner_Top->position + random;

				std::random_device rd2;
				std::mt19937 rng2(rd2());
				std::uniform_int_distribution<int> uni2(1, 10);
				int better = uni2(rng2);
				if (better == 5)
				{
					enemy->better = true;
					enemy->sprite()->color = RED;
				}

			}
			else if (spawnLocation == 2)
			{
				std::cout << "Down" << std::endl;
				enemy->position = spawner_Down->position + random;

				std::random_device rd2;
				std::mt19937 rng2(rd2());
				std::uniform_int_distribution<int> uni2(1, 10);
				int better = uni2(rng2);
				if (better == 5)
				{
					enemy->better = true;
					enemy->sprite()->color = RED;
				}

			}
			else if (spawnLocation == 3)
			{
				std::cout << "Left" << std::endl;
				enemy->position = spawner_Left->position + random;

				std::random_device rd2;
				std::mt19937 rng2(rd2());
				std::uniform_int_distribution<int> uni2(1, 10);
				int better = uni2(rng2);
				if (better == 5)
				{
					enemy->better = true;
					enemy->sprite()->color = RED;
				}

			}
			else {
				std::cout << "Right" << std::endl;
				enemy->position = spawner_Right->position + random;

				std::random_device rd2;
				std::mt19937 rng2(rd2());
				std::uniform_int_distribution<int> uni2(1, 10);
				int better = uni2(rng2);
				if (better == 5)
				{
					enemy->better = true;
					enemy->sprite()->color = RED;
				}

			}
		}
		//grace period
		nextwave = false;
		//increase diffecuty
		enemiesPerWave += 3;
		currentWave += 1;
		player->CurrentWave = currentWave;
		//Update the wave counter
		std::string prefix = "Wave: ";
		std::ostringstream fullString;
		fullString << prefix << currentWave;
		wavetext->message(fullString.str(), BLUE);
	}

	for (int c = coins.size() - 1; c >= 0; c--)
	{
		if (enemys.size() == 0  || Vector2(player->position.x - coins[c]->position.x, player->position.y - coins[c]->position.y).getLengthSquared() < 100 * 100) {
			coins[c]->followplayer = true;
		}
		else {
			coins[c]->followplayer = false;
		}
		if (Vector2(player->position.x - coins[c]->position.x, player->position.y - coins[c]->position.y).getLengthSquared() < 25 * 25) {
			//add 1 money per enemy killed
			money++;
			//update money text
			std::string prefix = "Money: ";
			std::ostringstream fullString;
			fullString << prefix << money;
			moneytext->message(fullString.str(), GREEN);

			//delete the coin
			bottomlayer->removeChild(coins[c]);
			delete coins[c];
			coins.erase(coins.begin() + c);
		}
		//if coins in radius for player then move towards player

	}

	//Bullet deletion & Bullet collison with enemy
	for (int i = projectiles.size() - 1; i >= 0; i--)
	{
		for (int j = enemys.size() - 1; j >= 0; j--)
		{
			//check if projectile is colliding with enemy
			if (Vector2(projectiles[i]->position.x - enemys[j]->position.x, projectiles[i]->position.y - enemys[j]->position.y).getLengthSquared() < 22 * 22)
			{
				if (enemys[j]->canBeHit) {

					projectiles[i]->pierceEnemyCount += 1;
					//delete projectile if hit enemy and piercelimit is met
					if (projectiles[i]->pierceEnemyCount >= piecingcount) {
						projectiles[i]->dead = true;
					}

					enemys[j]->position -= Point2(25, 25) * Point2(cos(enemys[j]->rotation.z), sin(enemys[j]->rotation.z));
					// speed - iets
					enemys[j]->health -= 1;
					enemys[j]->speed *= 0.8f;
					enemys[j]->canBeHit = false;
					enemys[j]->lastHitTime = clock();

					if (enemys[j]->health == 2)
					{
						enemys[j]->addSprite("assets/enemyhit.tga");
					}
					else
					{
						enemys[j]->addSprite("assets/enemyhit2.tga");
					}
					if (enemys[j]->health <= 0)
					{
						coin = new Coin(player);
						bottomlayer->addChild(coin);
						coins.push_back(coin);
						coin->position = Point2(enemys[j]->position.x, enemys[j]->position.y);


						backlayer->removeChild(enemys[j]);
						delete enemys[j];
						enemys.erase(enemys.begin() + j);

					}
				}
			}
		}
		//if bullet is not in screen, Delete
		if (projectiles[i]->dead == true || projectiles[i] != nullptr && (projectiles[i]->position.x > SWIDTH || projectiles[i]->position.x < 0 || projectiles[i]->position.y < 0 || projectiles[i]->position.y > SHEIGHT)) {
			backlayer->removeChild(projectiles[i]);
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
		//outside of collision detection section
		for (int i = 0; i < enemys.size(); i++)
		{
			if (!enemys[i]->canBeHit) {
				if ((clock() - enemys[i]->lastHitTime) / CLOCKS_PER_SEC >= hitDelay) {
					enemys[i]->canBeHit = true;
				}
			}
		}

	}

	//Collision enemyies with player and damage
	for (int j = enemys.size() - 1; j >= 0; j--)
	{
		//Colision with player and enemy both get damage
		if (Vector2(player->position.x - enemys[j]->position.x, player->position.y - enemys[j]->position.y).getLengthSquared() < 25 * 25)
		{
			//backlayer->removeChild(enemys[j]);
			//delete enemys[j];
			//enemys.erase(enemys.begin() + j);


			enemys[j]->position -= Point2(30, 30) * Point2(cos(enemys[j]->rotation.z), sin(enemys[j]->rotation.z));
			
			std::cout << healthbar->scale.x << std::endl;

			
			if (player->health <= 90)
			{player->addSprite("assets/tankhit1.tga");}
			if (player->health <= 70)
			{player->addSprite("assets/tankhit2.tga");}
			if (player->health <= 50)
			{player->addSprite("assets/tankhit3.tga");}
			if (player->health <= 30)
			{player->addSprite("assets/tankhit4.tga");}



			player->health -= 2;//Damage done to the player
			healthbar->scale = Point2((float)player->health / 50, 0.3);
			if (player->health <= 0)
			{
				//player->dead = true;
				this->removeChild(player);
				delete player;
				//player = nullptr;
				UI_Back->addChild(endtextback);
				UI_Front->addChild(endtext);
			}


			enemys[j]->health -= 1;
			if (enemys[j]->health == 2)
			{
				enemys[j]->addSprite("assets/enemyhit.tga");
			}
			else
			{
				enemys[j]->addSprite("assets/enemyhit2.tga");
			}
			if (enemys[j]->health <= 0)
			{
				coin = new Coin(player);
				bottomlayer->addChild(coin);
				coins.push_back(coin);
				coin->position = Point2(enemys[j]->position.x, enemys[j]->position.y);

				
				backlayer->removeChild(enemys[j]);
				delete enemys[j];
				enemys.erase(enemys.begin() + j);

			}
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



	float maxRotationDifference = rotatespeed * deltaTime;



	float rotationDiff = std::max(-maxRotationDifference, std::min(rotationDifference, maxRotationDifference));

	//met hulp van Jarno Dijk en Joas heeft toegekeken.
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


	//std::cout << player->rotation.z << std::endl;
	

	// ############-- Draw border and lazer --##################std::cout << angleDifference << std::endl;
	ddClear();
	ddLine(player->position.x, player->position.y, mousex, mousey, RED);
	ddCircle(mousex, mousey, 10, RED);
	int border = 10;
	ddSquare(border, border, SWIDTH - (border * 2), SHEIGHT - (border * 2), WHITE);
}//###################################################################
