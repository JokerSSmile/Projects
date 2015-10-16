#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "view.h"
#include "player.h"
#include "enemy.h"

using namespace sf;
using namespace std;



int main()
{
	//karta i taili
	Image map_image;
	map_image.loadFromFile("images/Rock.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	//background
	Image mapBackground;
	mapBackground.loadFromFile("images/bigMap.png");
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

	//enemy
	Enemy e1(enemyImage, 128, 128, 57, 45, "EnemyFly");
	Enemy e2(enemyImage, 250, 350, 57, 45, "EnemyFly");


	//sozdanie igroka
	Player p(heroImage, 250, 200, 56, 96, "Hero");


	

	RenderWindow window(sf::VideoMode(960, 640), "Game");

	view.reset(FloatRect(0, 0, 960, 640));


	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		p.update(time);
		e1.update(time);
		e2.update(time);




		viewmap(time);
		window.setView(view);
		window.clear();


		window.draw(mapBackgroundSprite);


		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 'r')
				{
					s_map.setTextureRect(IntRect(0, 0, 64, 64));
					s_map.setPosition(j * 64, i * 64);
					window.draw(s_map);
				}
			}
	

		//draw
		window.draw(p.sprite);
		if (e1.health > 0)
		{
			window.draw(e1.sprite);
		}
		if (e2.health > 0)
		{
			window.draw(e2.sprite);
		}


		window.display();
	}

	return 0;
}