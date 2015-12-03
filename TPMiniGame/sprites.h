#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

struct Sprites
{
public:
	Sprites() {};
	//start
	sf::RectangleShape rectangleStart;

	//cross\round sprites
	sf::Texture crossTexture;
	sf::Texture roundTexture;
	sf::Sprite crossSprite;
	sf::Sprite roundSprite;

	//text
	sf::Texture textTexture;
	sf::Sprite textSprite;

	//1 player
	sf::Texture oneTexture;
	sf::Sprite oneSprite;

	//2 player
	sf::Texture twoTexture;
	sf::Sprite twoSprite;

	//current player choise
	sf::Texture currentTexture;
	sf::Sprite currentSprite;

	//cells
	sf::RectangleShape rectangle;

	void SetStartRectangle()
	{
		rectangleStart.setSize(sf::Vector2f(RECTANGLESTART_SIZE.x, RECTANGLESTART_SIZE.y));
		rectangleStart.setFillColor(sf::Color::White);
		rectangleStart.setPosition(SPACE_BETWEEN_CELL, SPACE_BETWEEN_CELL);
	}

	void SetMarks()
	{
		crossTexture.loadFromFile("image/cross.png");
		roundTexture.loadFromFile("image/round.png");
		roundSprite.setTexture(roundTexture);
		crossSprite.setTexture(crossTexture);
	}

	void SetText()
	{
		textTexture.loadFromFile("image/text.png");
		textSprite.setTexture(textTexture);
		textSprite.setPosition(100, 100);
	}

	void SetChoosePlayersCount()
	{
		oneTexture.loadFromFile("image/1.png");
		oneSprite.setTexture(oneTexture);
		oneSprite.setPosition(100, 260);

		//2 player
		twoTexture.loadFromFile("image/2.png");
		twoSprite.setTexture(twoTexture);
		twoSprite.setPosition(100, 370);
	}

	void SetCurrentChoise()
	{
		currentTexture.loadFromFile("image/current.png");
		currentSprite.setTexture(currentTexture);
	}
};
