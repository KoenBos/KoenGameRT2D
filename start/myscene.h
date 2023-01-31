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
#include <rt2d/text.h>

#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "basicentity.h"
#include "ImageButton.h"
#include "coin.h"

 /// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();
	/// @brief the wave you are in
	int currentWave;		  
	/// @brief the enemies that spawn in a wave (goes up every wave)
	int enemiesPerWave;		  
	/// @brief text to see what wave your in
	Text* wavetext;
	/// @brief text to show your money
	Text* moneytext;
	/// @brief the gameover text background
	Text* endtextback;
	/// @brief the gameover text foreground
	Text* endtext;
	/// @brief your amount of money
	int money;
	/// @brief a boolian for when you can shoot
	bool canShoot;
	/// @brief a shoot delay in seconds
	double shootDelay; // delay in seconds
	/// @brief a delay for when the enemies can be hit aggain in seconds
	double hitDelay; // delay for enemies hit
	/// @brief the last time the enemie was shot in seconds
	double lastShotTime;
	/// @brief the current time for the delays
	double currentTime;
	/// @brief the speed wich you can rotate
	float rotatespeed;
	/// @brief the amount of enemies a bullet can pierce thrue
	int piecingcount;

	/// @brief if the startgame button is pressed it is true.
	bool startGame;

	/// @brief is the wave still going then not start the next wave
	bool nextwave;
	
	/// @brief button for speed upgrade
	ImageButton* speedButton;
	/// @brief button for firerate upgrade
	ImageButton* firerateButton;
	/// @brief button for rotatespeedupgrade
	ImageButton* rotatespeedButton;
	/// @brief button for piercing upgrade
	ImageButton* piercingButton;
	/// @brief button for start
	ImageButton* startButton;
	/// @brief button for next wave
	ImageButton* nextwaveButton;

	 /**
	@brief runt als je klikt op de firerate upgrade knop drukt
	 **/
	void clickfirerate();
	/**
	@brief runt als je klikt op de rotate upgrade knop drukt
	**/
	void clickrotatespeed();
	/**
	@brief runt als je klikt op de speed upgrade knop drukt
	**/
	void clickpiercing();
	/**
	@brief runt als je klikt op de piercing upgrade knop drukt
	**/
	void clickspeed();
	/**
	@brief runt als je klikt op de start knop drukt
	**/
	void startgame();
	/**
	@brief runt als je klikt op de nextwave knop drukt
	**/
	void nextwavefunction();


	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	std::vector<Projectile*> projectiles;
	std::vector<Enemy*> enemys;
	std::vector<Coin*> coins;
	//std::vector<Text*> text;
	float deltaY;
	float deltaX;
	float angle;

private:
	/// @brief the rotating tank in the middle of the screen that can shoot and buy upgrades.
	Player* player;
	/// @brief coins that drop from the enemies
	Coin* coin;
	/// @brief the green little shits that come to the tank
	Enemy* enemy;
	/// @brief 
	Projectile* projectile;
	BasicEntity* background;
	BasicEntity* bottomlayer;
	BasicEntity* backlayer;
	BasicEntity* healthbar;
	BasicEntity* healthbarback;
	BasicEntity* spawner_Top;
	BasicEntity* spawner_Down;
	BasicEntity* spawner_Left;
	BasicEntity* spawner_Right;
	BasicEntity* upgrade_background;
	BasicEntity* wave_background;
	BasicEntity* UI_Back;
	BasicEntity* UI_Front;
	BasicEntity* startScreen;
	BasicEntity* startbackground;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;
	bool power = false;
};

#endif /* SCENE00_H */
