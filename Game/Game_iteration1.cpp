#include <SFML/Graphics.hpp>
#include <iostream>
#include "collision.h"
#include "constants.h"
#include "map.h"
#include "view.h"
#include "player.h"
#include "enemy.h"
#include "chest.h"


using namespace sf;
using namespace std;


int InitializeLevel(Player & player)
{
	if (player.x > 0 && player.x < WINDOW_WIDTH)
	{
		if (player.y > 0 && player.y < WINDOW_HEIGHT)
		{
			return 1;
		}
		else if (player.y > WINDOW_HEIGHT && player.y < WINDOW_HEIGHT * 2)
		{
			return 4;
		}
		else if (player.y > WINDOW_HEIGHT * 2 && player.y < WINDOW_HEIGHT * 3)
		{
			return 7;
		}
	}
	else if (player.x > WINDOW_WIDTH && player.x < WINDOW_WIDTH * 2)
	{
		if (player.y > 0 && player.y < WINDOW_HEIGHT)
		{
			return 2;
		}
		else if (player.y > WINDOW_HEIGHT && player.y < WINDOW_HEIGHT * 2)
		{
			return 5;
		}
		else if (player.y > WINDOW_HEIGHT * 2 && player.y < WINDOW_HEIGHT * 3)
		{
			return 8;
		}
	}
	else if (player.x > WINDOW_WIDTH * 2 && player.x < WINDOW_WIDTH * 3)
	{
		if (player.y > 0 && player.y < WINDOW_HEIGHT)
		{
			return 3;
		}
		else if (player.y > WINDOW_HEIGHT && player.y < WINDOW_HEIGHT * 2)
		{
			return 6;
		}
		else if (player.y > WINDOW_HEIGHT * 2 && player.y < WINDOW_HEIGHT * 3)
		{
			return 9;
		}
	}
}

void DrawPlayersHealth(float health, RenderWindow & window, View & view)
{
	int i;

	Texture heartTexture;
	heartTexture.loadFromFile("images/hearts.png");
	Sprite fullHP;
	fullHP.setTexture(heartTexture);
	fullHP.setTextureRect(IntRect(0,0,16,16));
	fullHP.setScale(2, 2);
	Sprite halfHP;
	halfHP.setTexture(heartTexture);
	halfHP.setTextureRect(IntRect(16, 0, 16, 16));
	halfHP.setScale(2, 2);

	if (health > 0)
	{
		for (i = 1; i <= health; i += 1)
		{
			fullHP.setPosition(view.getCenter().x - WINDOW_WIDTH / 2 + i * 35, view.getCenter().y - WINDOW_HEIGHT / 2 + 10);
			window.draw(fullHP);
		}
		if (health - int(health) != 0)
		{
			halfHP.setPosition(view.getCenter().x - WINDOW_WIDTH / 2 + i * 35, view.getCenter().y - WINDOW_HEIGHT / 2 + 10);
			window.draw(halfHP);
		}
	}
}

void DrawBackground(RenderWindow & window, Sprite & wallBackgroundSprite, Sprite & floorBackgroundSprite)
{
	//background
	wallBackgroundSprite.setOrigin(wallBackgroundSprite.getGlobalBounds().width / 2, wallBackgroundSprite.getGlobalBounds().height / 2);
	wallBackgroundSprite.setPosition(view.getCenter().x, view.getCenter().y);
	floorBackgroundSprite.setOrigin(floorBackgroundSprite.getGlobalBounds().width / 2, floorBackgroundSprite.getGlobalBounds().height / 2);
	floorBackgroundSprite.setPosition(view.getCenter().x, view.getCenter().y);
	window.draw(wallBackgroundSprite);
	window.draw(floorBackgroundSprite);
}

void CheckEnemyCollidesPlayer(float& gameTime, float& hitTimer, Player& p, Enemies enemies[10])
{
	//check colisions enemies with player
	for (int i = 0; i < SIZE_ENEMIES; i++)
	{
		if (p.sprite.getGlobalBounds().contains(enemies[i].x + (enemies[i].sprite.getGlobalBounds().width / 2), enemies[i].y + (enemies[i].sprite.getGlobalBounds().height / 2)))
		{
			if (gameTime > hitTimer + 1 || hitTimer == 0)
			{
				p.health -= 0.5;
				hitTimer = gameTime;
			}
		}
	}
}

void CheckBulletsCollisionWithEntities(Player& p, Enemies enemies[SIZE_ENEMIES], float gameTime, Bullets bullets[SIZE_BULLETS], float& time, RenderWindow& window, Texture& bulletTexture)
{
	//going through bullets mass and delete/update it. Check collisions with player, enemies
	for (int i = 0; i < SIZE_BULLETS; i++)
	{
		if (bullets[i].life == true)
		{
			for (int k = 0; k < SIZE_ENEMIES; k++)
			{
				if (enemies[k].health > 0)
				{
					if (bullets[i].isPlayers == true)
					{
						if (enemies[k].sprite.getGlobalBounds().contains(bullets[i].x + BULLET_SIDE / 2, bullets[i].y + BULLET_SIDE / 2))
						{
							bullets[i].life = false;
							enemies[k].health -= p.damage;
						}
					}
				}
			}
			if (bullets[i].isPlayers == false)
			{
				if (p.sprite.getGlobalBounds().contains(bullets[i].x + BULLET_SIDE / 2, bullets[i].y + BULLET_SIDE / 2))
				{
					bullets[i].life = false;
					bullets[i].isPlayers = false;
					p.health -= enemies[i].damage;
				}
			}
			bullets[i].Update(time, window, gameTime, bulletTexture);
			bullets[i].DeleteBullet(gameTime);
		}
	}
}

void DrawEnemies(RenderWindow& window, int level, Enemies enemies[SIZE_ENEMIES])
{
	for (int i = 0; i < SIZE_ENEMIES; i++)
	{
		if (enemies[i].health > 0)
		{
			if (enemies[i].level == level)
			{
				window.draw(enemies[i].sprite);
			}
		}
		else
		{
			enemies[i].x = 0;
			enemies[i].y = 0;
		}
	}
}

void DrawPlayer(Player& p, RenderWindow& window)
{
	//while HP > 0 draw player 
	if (p.health > 0)
	{
		window.draw(p.sprite);
	}
}

void UpdateEnemies(Enemies enemies[SIZE_ENEMIES], float time, float gameTime, RenderWindow& window, int level)
{
	//enemy update
	for (int i = 0; i < SIZE_ENEMIES; i++)
	{
		if (enemies[i].health > 0)
		{
			enemies[i].Update(time, gameTime, window, level);
		}
	}
}

bool CheckIsLevelCleared(int level, Enemies enemies[SIZE_ENEMIES])
{
	bool isAllDead = true;

	for (int i = 0; i < SIZE_ENEMIES; i++)
	{
		if (enemies[i].level == level)
		{
			if (enemies[i].health > 0)
			{
				isAllDead = false;
			}
		}
		//cout << isAllDead << endl;
	}
	return isAllDead;
}

int main()
{
	//players last shoot time
	float lastShootPlayer = 0;

	//map struct
	tileMap myMap;
	
	//background wall
	Image wallBackground;
	wallBackground.loadFromFile("images/walls.png");
	Texture wallBackgroundTexture;
	wallBackgroundTexture.loadFromImage(wallBackground);
	Sprite wallBackgroundSprite;
	wallBackgroundSprite.setTexture(wallBackgroundTexture);

	//background floor
	Image floorBackground;
	floorBackground.loadFromFile("images/floor.png");
	Texture floorBackgroundTexture;
	floorBackgroundTexture.loadFromImage(floorBackground);
	Sprite floorBackgroundSprite;
	floorBackgroundSprite.setTexture(floorBackgroundTexture);

	//hero
	Image heroImage;
	heroImage.loadFromFile("images/body_1.png");

	//enemy image
	Image enemyImage;
	enemyImage.loadFromFile("images/fly.png");

	//standAndShoot
	Image standAndShootImage;
	standAndShootImage.loadFromFile("images/StandAndShoot.png");

	//bullets
	Texture bulletTexture;
	bulletTexture.loadFromFile("images/bullets.png");

	//mass of enemies
	Enemies enemies[10] =
	{
		{ enemyImage, FLY1_POSITION_X, FLY1_POSITION_Y, FLY_WIDTH, FLY_HEIGHT, "EnemyFly", 1, 1 },
		{ enemyImage, FLY2_POSITION_X, FLY2_POSITION_Y, FLY_WIDTH, FLY_HEIGHT, "EnemyFly", 1, 1 },
		{ standAndShootImage, 1400, 400, 38, 43, "EnemyStandAndShoot", 3, 2 },
		{ standAndShootImage, 1500, 400, 38, 43, "EnemyStandAndShoot", 3, 2 },
		{ standAndShootImage, 1300, 400, 38, 43, "EnemyStandAndShoot", 3, 2 }
	};
	
	//create player
	Player p(heroImage, PLAYER_POSITION_X, PLAYER_POSITION_Y, PLAYER_WIDTH, PLAYER_HEIGHT, "Hero", 6);

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");

	view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	//clock
	Clock clock;
	Clock gameTimer;

	//last player hit time
	float hitTimer = 0;

	//game time
	float gameTime;

	//level
	int level = 1;

	while (window.isOpen())
	{
		level = InitializeLevel(p);

		//time
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;

		//game time
		if (p.health > 0)
		{
			gameTime = gameTimer.getElapsedTime().asSeconds();
		}

		//event
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		
			//player update
		p.Update(time, gameTime, lastShootPlayer, wallBackgroundSprite, view);
		
		UpdateEnemies(enemies, time, gameTime, window, level);

		//view
		window.setView(view);

		//clear screen
		window.clear();
		
		CheckEnemyCollidesPlayer(gameTime, hitTimer, p, enemies);

		DrawBackground(window, wallBackgroundSprite, floorBackgroundSprite);

		DrawPlayersHealth(p.health, window, view);
		
		DrawEnemies(window, level, enemies);
		
		CheckBulletsCollisionWithEntities(p, enemies, gameTime, bullets, time, window, bulletTexture);
		
		DrawPlayer(p, window);
		
		myMap.drawMap(window);

		if (CheckIsLevelCleared(level, enemies))
		{
			Chest *chest = new Chest;
			chest->Update(chest, window);
		}

		window.display();
	}
	return 0;
}
