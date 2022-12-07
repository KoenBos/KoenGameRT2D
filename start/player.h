
#ifndef PLAYER_H
#define PLAYER_H

#include <rt2d/entity.h>

/// @brief The MyEntity class is the Entity implementation.
class Player : public Entity
{
public:
	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();
	float speed;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
	float currentRotation;
};

#endif /* MYENTITY_H */
