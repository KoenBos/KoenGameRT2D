
#ifndef COIN_H
#define COIN_H

#include <rt2d/entity.h>
#include "player.h"

 /// @brief The MyEntity class is the Entity implementation.
class Coin : public Entity
{
public:
	/// @brief Constructor
	Coin(Player* player);
	bool followplayer;
	float followspeed;
	/// @brief Destructor
	virtual ~Coin();


	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */

	Player* _player;

};

#endif /* MYENTITY_H */
