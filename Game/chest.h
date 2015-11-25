#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace sf;


struct Chest
{
private:
	Texture chestTexture;
public:
	int level;
	float x;
	float y;
	int h;
	int w;
	Sprite chestSpriteOpened;
	Sprite chestSpriteClosed;
	bool isOpened = false;
	int present;
	enum 
	{
		IncreaseSpeed, IncreaseDamage, Health, Bomb
	} filling;
	Chest() {};
	Chest(float X, float Y, int Level)
	{
		x = X;
		y = Y;
		chestTexture.loadFromFile("images/chest.png");
		chestSpriteOpened.setTextureRect(IntRect(64, 0, 64, 64));
		chestSpriteClosed.setTextureRect(IntRect(0, 0, 64, 64));
		h = chestSpriteClosed.getGlobalBounds().height;
		w = chestSpriteClosed.getGlobalBounds().width;
		level = Level;
	}

	/*
	void SetFilling()
	{
		srand(time(0)*100);
		int random = 1 + rand() % 3;
		switch (filling)
		{
		case 0: filling = IncreaseSpeed; break;
		case 1: filling = IncreaseDamage; break;
		case 2: filling = Health; break;
		case 3: filling = Bomb; break;
		}
	}
	*/

	int SetFilling()
	{
		srand(time(0) * 100);
		int random = (1 + rand() % 3);

	}

	void CheckOpening(Player& p)
	{
		if (Collision::PixelPerfectTest(p.sprite, chestSpriteClosed))
		{
			isOpened = true;
		}
	}

	void Update(RenderWindow& window, Player& p)
	{
		chestSpriteOpened.setTexture(chestTexture);
		chestSpriteClosed.setTexture(chestTexture);
		if (isOpened == false)
		{
			chestSpriteClosed.setPosition(x - w / 2, y - h / 2);
			CheckOpening(p);
			window.draw(chestSpriteClosed);
		}
		else
		{
			
			chestSpriteOpened.setPosition(x - w / 2, y - h / 2);
			window.draw(chestSpriteOpened);
		}
	}
};
