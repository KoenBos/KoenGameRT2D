
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <rt2d/entity.h>

/// @brief The MyEntity class is the Entity implementation.
class Projectile : public Entity
{
public:
	/// @brief Constructor
	Projectile();
	/// @brief Destructor
	virtual ~Projectile();
	float speed;
	float currentRotation;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
