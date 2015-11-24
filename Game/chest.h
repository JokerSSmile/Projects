#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace sf;


struct Chest
{
private:
	Texture chestTexture;
	Sprite chestSpriteOpened;
	Sprite chestSpriteClosed;
	bool isLoadedTexture = false;
public:
	float x;
	float y;
	bool isOpened = false;
	Chest() {};
	Chest(float X, float Y)
	{
		x = X;
		y = Y;
	}
	enum
	{
		IncreaseSpeed, IncreaseDamage, IncreaseHealth, Bomb
	} filling;

	void LoadTexture(Chest* chest)
	{
		chestTexture.loadFromFile("images/chest.png");
		chestSpriteOpened.setTextureRect(IntRect(32, 0, 32, 32));
		chestSpriteClosed.setTextureRect(IntRect(0, 0, 32, 32));
	}

	void SetFilling(Chest* chest)
	{
		srand(time(0));
		int random = 1 + rand() % 3;
		switch (filling)
		{
		case 0: filling = IncreaseSpeed; break;
		case 1: filling = IncreaseDamage; break;
		case 2: filling = IncreaseHealth; break;
		case 3: filling = Bomb; break;
		}
	}

	void Update(Chest* chest, RenderWindow& window)
	{
		if (&isLoadedTexture == false)
		{
			cout << "loaded" << endl;
			LoadTexture(chest);
			isLoadedTexture = true;
		}
		SetFilling(chest);
		chestSpriteClosed.setPosition(x, y);
		chestSpriteOpened.setPosition(x, y);
		if (isOpened == false)
		{
			//cout << "124124" << endl;
			window.draw(chestSpriteClosed);
		}
		else
		{
			window.draw(chestSpriteOpened);
		}
	}
};
