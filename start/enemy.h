
#ifndef ENEMY_H
#define ENEMY_H

#include <rt2d/entity.h>
#include "player.h"

 /// @brief The MyEntity class is the Entity implementation.
class Enemy : public Entity
{
public:
	/// @brief Constructor
	Enemy(Player* player);
	/// @brief Destructor
	virtual ~Enemy();
	float speed;
	float currentRotation;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */

	Player* _player;
};

#endif /* MYENTITY_H */
