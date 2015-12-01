#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <random>
#include "time.h"

using namespace sf;

enum
{
	IncreaseSpeed, IncreaseDamage, Health, Bomb
} filling;

struct Chest
{
private:
	Texture chestTexture;
	Texture increaseSpeedTexture;
	Texture IncreaseDamageTexture;
	Texture HealthTexture;
	Texture BombTexture;
public:
	int level;
	float x;
	float y;
	int h;
	int w;
	Sprite chestSpriteOpened;
	Sprite chestSpriteClosed;
	Sprite increaseSpeedSprite;
	Sprite IncreaseDamageSprite;
	Sprite HealthSprite;
	Sprite BombSprite;

	bool isOpened = false;
	int present;
	bool areTexturesLoaded = false;
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

	void LoadTextures()
	{
		if (areTexturesLoaded == false)
		{
			increaseSpeedTexture.loadFromFile("images/increaseSpeed.png");
			IncreaseDamageTexture.loadFromFile("images/IncreaseDamage.png");
			HealthTexture.loadFromFile("images/addHeart.png");
			BombTexture.loadFromFile("images/addBomb.png");

			increaseSpeedSprite.setTexture(increaseSpeedTexture);
			IncreaseDamageSprite.setTexture(IncreaseDamageTexture);
			HealthSprite.setTexture(HealthTexture);
			BombSprite.setTexture(BombTexture);

			areTexturesLoaded = true;
		}
	}

	int RandomNumber()
	{
		return (double)rand() / (RAND_MAX + 1) * 4;
	}

	void SetFilling()
	{
		int rand = RandomNumber();
		if (rand == 0)
		{
			filling = IncreaseSpeed;
		}
		else if (rand == 1)
		{
			filling = IncreaseDamage;
		}
		else if (rand == 2)
		{
			filling = Health;
		}
		else if (rand == 3)
		{
			filling = Bomb;
		}
	}

	void CheckOpening(Player& p)
	{
		if (Collision::PixelPerfectTest(p.sprite, chestSpriteClosed))
		{
			isOpened = true;
		}
	}

	void GiveFirstPresent()
	{
		//cout << "1" << endl;
		
	}

	void GiveSecondPresent()
	{
		//cout << "2" << endl;
	}

	void GiveThirdPresent()
	{
		//cout << "3" << endl;
	}

	void GiveForhPresent()
	{
		//cout << "4" << endl;
	}

	void SetPresent()
	{
		SetFilling();
		switch (filling)
		{
		case IncreaseSpeed: GiveFirstPresent(); break;
		case IncreaseDamage: GiveSecondPresent(); break;
		case Health: GiveThirdPresent(); break;
		case Bomb: GiveForhPresent(); break;
		}
	}

	void Update(RenderWindow& window, Player& p)
	{
		chestSpriteOpened.setTexture(chestTexture);
		chestSpriteClosed.setTexture(chestTexture);
		LoadTextures();
		if (isOpened == false)
		{
			SetPresent();
			chestSpriteClosed.setPosition(x - w / 2, y - h / 2);
			CheckOpening(p);
			window.draw(chestSpriteClosed);
		}
		else
		{
			chestSpriteOpened.setPosition(x - w / 2, y - h / 2);
			window.draw(chestSpriteOpened);
		}
		window.draw(BombSprite);
	}
};
