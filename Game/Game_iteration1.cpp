#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "map.h"
#include "view.h"
#include "player.h"
#include "enemy.h"
#include "doors.h"


using namespace sf;
using namespace std;

void DrawHealth(float health, RenderWindow & window, View & view)
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

	for (i = 1; i <= health; i += 1)
	{
		fullHP.setPosition(view.getCenter().x - WINDOW_WIDTH/2 + i * 35, view.getCenter().y - WINDOW_HEIGHT/2 + 10);
		window.draw(fullHP);
	}
	if (health - int(health) != 0)
	{
		halfHP.setPosition(view.getCenter().x - WINDOW_WIDTH/2 + i * 35, view.getCenter().y - WINDOW_HEIGHT/2 + 10);
		window.draw(halfHP);
	}
}

void DrawMap(Sprite & doorSprite, Sprite & rockSprite, RenderWindow & window)
{
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (tileMap[i][j] == 's')
			{
				rockSprite.setTextureRect(IntRect(0, 0, TILE_SIDE, TILE_SIDE));
				rockSprite.setPosition(j * TILE_SIDE, i * TILE_SIDE);
				window.draw(rockSprite);
			}
			else if (tileMap[i][j + 1] == 'u')
			{
				doorSprite.setTextureRect(IntRect(0, 0, TILE_SIDE, TILE_SIDE));
				doorSprite.setPosition(j * TILE_SIDE + TILE_SIDE/2, i * TILE_SIDE - TILE_SIDE);
				doorSprite.setRotation(0);
				window.draw(doorSprite);
			}
			else if (tileMap[i][j + 1] == 'd')
			{
				doorSprite.setTextureRect(IntRect(0, 0, TILE_SIDE, TILE_SIDE));
				doorSprite.setPosition(j * TILE_SIDE + 160, i * TILE_SIDE + 128);
				doorSprite.setRotation(180);
				window.draw(doorSprite);
			}
			else if (tileMap[i][j + 1] == 'r')
			{
				doorSprite.setTextureRect(IntRect(0, 0, TILE_SIDE, TILE_SIDE));
				doorSprite.setPosition(j * TILE_SIDE + 192, i * TILE_SIDE);
				doorSprite.setRotation(90);
				window.draw(doorSprite);
			}
			else if (tileMap[i][j + 1] == 'l')
			{
				doorSprite.setTextureRect(IntRect(0, 0, TILE_SIDE, TILE_SIDE));
				doorSprite.setPosition(j * TILE_SIDE, i * TILE_SIDE + TILE_SIDE * 2);
				doorSprite.setRotation(270);
				window.draw(doorSprite);
			}
		}
}

int main()
{
	bool isShoot = false;
	float lastShoot = 0;


	//rock
	Image rockImage;
	rockImage.loadFromFile("images/Rock.png");
	Texture rockTexture;
	rockTexture.loadFromImage(rockImage);
	Sprite rockSprite;
	rockSprite.setTexture(rockTexture);
	
	//door
	Image doorImage;
	doorImage.loadFromFile("images/Door.png");
	Texture doorTexture;
	doorTexture.loadFromImage(doorImage);
	Sprite doorSprite;
	doorSprite.setTexture(doorTexture);
	doorSprite.setScale(2, 2);

	//background
	Image mapBackground;
	mapBackground.loadFromFile("images/bigMap1.png");
	Texture mapBackgroundTexture;
	mapBackgroundTexture.loadFromImage(mapBackground);
	Sprite mapBackgroundSprite;
	mapBackgroundSprite.setTexture(mapBackgroundTexture);

	//hero
	Image heroImage;
	heroImage.loadFromFile("images/charaset.png");

	//enemy image
	Image enemyImage;
	enemyImage.loadFromFile("images/fly.png");

	
	//mass of enemies
	Enemy enemies[10] = 
	{
		{enemyImage, FLY1_POSITION_X, FLY1_POSITION_Y, FLY_WIDTH, FLY_HEIGHT, "EnemyFly", 1},
		{enemyImage, FLY2_POSITION_X, FLY2_POSITION_Y, FLY_WIDTH, FLY_HEIGHT, "EnemyFly", 1}
	};


	//sozdanie igroka
	Player p(heroImage, PLAYER_POSITION_X, PLAYER_POSITION_Y, PLAYER_WIDTH, PLAYER_HEIGHT, "Hero", 6);

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");

	view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	Clock clock;
	Clock gameTimer;
	float gameTime;


	//время
	float hitTimer = 0;



	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;

		//
		if (p.health > 0)
		{
			gameTime = gameTimer.getElapsedTime().asSeconds();
		}


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		

		p.update(time, gameTime, lastShoot);
		
		//enemy update
		for (int i = 0; i < 2; i++)
		{
			enemies[i].update(time);
		}


		window.setView(view);
		window.clear();

		//zadnii fon
		window.draw(mapBackgroundSprite);

		//drawing map
		DrawMap(doorSprite, rockSprite, window);
		
		//check colisions with player
		for (int i = 0; i < 2; i++)
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

		//cout << isShoot << endl;

		//cout << p.dir << endl;


		//HP bar
		DrawHealth(p.health, window, view);
		
		//while HP > 0 draw  
		if (p.health > 0)
		{
			window.draw(p.sprite);
		}
		for (int i = 0; i < 2; i++)
		{
			if (enemies[i].health > 0)
				window.draw(enemies[i].sprite);
		}

		for (int i = 0; i < size(bullets); i++)
		{
			if (bullets[i].life == true)
			{
				bullets[i].deleteBullet(gameTime);
				bullets[i].update(time, window);
			}
		}



		window.display();
	}

	return 0;
}