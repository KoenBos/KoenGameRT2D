/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H
#define PI 3.14159265358979323846

#include <rt2d/scene.h>

#include "player.h"
#include "enemy.h"
#include "projectile.h"

 /// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	std::vector<Projectile*> projectiles;

private:
	/// @brief the rotating square in the middle of the screen
	Player* player;
	Enemy* enemy;
	Projectile* projectile;
	/// @brief a Timer to rotate the color every n seconds
	Timer t;
	bool power = false;
};

#endif /* SCENE00_H */
