#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "constants.h"
#include "ai.h"

using namespace std;

void DrawWindow(sf::RectangleShape, sf::RenderWindow & window)
{
	int posx = SPACE_BETWEEN_CELL;
	int posy = SPACE_BETWEEN_CELL;


	sf::RectangleShape rectangle(sf::Vector2f(CELL_SIDE, CELL_SIDE));
	rectangle.setFillColor(sf::Color::White);

	for (int line = 0; line < FIELD_CELLS; line++)
	{
		rectangle.setPosition(posx, posy);
		for (int colomn = 0; colomn < FIELD_CELLS; colomn++)
		{
			rectangle.setPosition(posx, posy);
			posy = posy + CELL_SIZE_PLUS_SPACE;
			window.draw(rectangle);
		}
		posx = posx + CELL_SIZE_PLUS_SPACE;
		posy = SPACE_BETWEEN_CELL;
	}
	posx = SPACE_BETWEEN_CELL;
	posy = SPACE_BETWEEN_CELL;

	//menu
	sf::RectangleShape rectangleMenu(sf::Vector2f(MENU_CELL_SIZE.x, MENU_CELL_SIZE.y));
	rectangleMenu.setFillColor(sf::Color::White);
	rectangleMenu.setPosition(MENU_CELL_POSITION.x, MENU_CELL_POSITION.y);
	window.draw(rectangleMenu);

	//refresh
	sf::Texture refreshTexture;
	refreshTexture.loadFromFile("image/refresh.png");
	sf::Sprite refreshSprite;
	refreshSprite.setTexture(refreshTexture);
	refreshSprite.setPosition(REFRESH_SPRITE_POSITION.x, REFRESH_SPRITE_POSITION.y);
	window.draw(refreshSprite);

	//exit
	sf::Texture exitTexture;
	exitTexture.loadFromFile("image/exit.png");
	sf::Sprite exitSprite;
	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(EXIT_POSITION.x, EXIT_POSITION.y);
	window.draw(exitSprite);
}

void DrawMarksInCell(sf::RenderWindow& window, int field[FIELD_CELLS][FIELD_CELLS], sf::Sprite& crossSprite, sf::Sprite& roundSprite)
{
	for (int line = 0; line < FIELD_CELLS; line++)
	{
		for (int colomn = 0; colomn < FIELD_CELLS; colomn++)
		{	
			
			if (field[line][colomn] == 1)
			{
				crossSprite.setPosition(colomn * CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL, line* CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL);
				window.draw(crossSprite);
			}
			else if (field[line][colomn] == 2)
			{
				roundSprite.setPosition(colomn * CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL, line* CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL);
				window.draw(roundSprite);
			}
		}
	}
}

int PutMarkInCell(sf::RenderWindow& window, bool& isPlayersTurn, int& turnCounter, int field[FIELD_CELLS][FIELD_CELLS])
{
	turnCounter = 0;
	sf::Texture crossWinTexture;
	crossWinTexture.loadFromFile("image/xwins.png");
	sf::Sprite crossWinSprite;
	crossWinSprite.setTexture(crossWinTexture);


	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;


	for (int line = 0; line < FIELD_CELLS; line++)
	{
		for (int colomn = 0; colomn < FIELD_CELLS; colomn++)
		{
			if (field[line][colomn] != 0)
			{
				turnCounter += 1;
			}
		}
	}

	//заполняем массив при ходе
	if (sf::Event::GainedFocus && sf::Event::MouseEntered)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (SPACE_BETWEEN_CELL <= mouseX && mouseX <= CELL_SIZE_PLUS_SPACE)
			{
				if (SPACE_BETWEEN_CELL <= mouseY && mouseY <= CELL_SIZE_PLUS_SPACE)
				{
					if (field[0][0] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[0][0] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[0][0] = 1;
							isPlayersTurn = false;
						}
					}
				}
				else if (SECOND_CELL_POSITION_START <= mouseY && mouseY <= SECOND_CELL_POSITION_END)
				{
					if (field[1][0] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[1][0] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[1][0] = 1;
							isPlayersTurn = false;
						}
					}
				}
				else if (THIRD_CELL_POSITION_START <= mouseY && mouseY <= THIRD_CELL_POSITION_END)
				{
					if (field[2][0] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[2][0] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[2][0] = 1;
							isPlayersTurn = false;
						}
					}
				}
			}
			else if (SECOND_CELL_POSITION_START <= mouseX && mouseX <= SECOND_CELL_POSITION_END)
			{
				if (SPACE_BETWEEN_CELL <= mouseY && mouseY <= CELL_SIZE_PLUS_SPACE)
				{
					if (field[0][1] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[0][1] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[0][1] = 1;
							isPlayersTurn = false;
						}
					}
				}


				else if (SECOND_CELL_POSITION_START <= mouseY && mouseY <= SECOND_CELL_POSITION_END)
				{
					if (field[1][1] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[1][1] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[1][1] = 1;
							isPlayersTurn = false;
						}
					}
				}
				else if (THIRD_CELL_POSITION_START <= mouseY && mouseY <= THIRD_CELL_POSITION_END)
				{
					if (field[2][1] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[2][1] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[2][1] = 1;
							isPlayersTurn = false;
						}
					}
				}
			}
			else if (THIRD_CELL_POSITION_START <= mouseX && mouseX <= THIRD_CELL_POSITION_END)
			{
				if (SPACE_BETWEEN_CELL <= mouseY && mouseY <= CELL_SIZE_PLUS_SPACE)
				{
					if (field[0][2] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[0][2] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[0][2] = 1;
							isPlayersTurn = false;
						}
					}
				}


				else if (SECOND_CELL_POSITION_START <= mouseY && mouseY <= SECOND_CELL_POSITION_END)
				{
					if (field[1][2] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[1][2] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[1][2] = 1;
							isPlayersTurn = false;
						}
					}
				}
				else if (THIRD_CELL_POSITION_START <= mouseY && mouseY <= THIRD_CELL_POSITION_END)
				{
					if (field[2][2] == 0)
					{
						if (isPlayersTurn == false)
						{
							field[2][2] = 2;
							isPlayersTurn = true;
						}
						else
						{
							field[2][2] = 1;
							isPlayersTurn = false;
						}
					}
				}
			}
		}
	}
	return turnCounter;
}

void DrawXWinSprite(sf::Sprite& xWinSprite, sf::RenderWindow& window)
{
	xWinSprite.setPosition(XWIN_SPRITE_POSITION.x, XWIN_SPRITE_POSITION.y);
	window.draw(xWinSprite);
}

void DrawOWinSprite(sf::Sprite& oWinSprite, sf::RenderWindow& window)
{
	oWinSprite.setPosition(OWIN_SPRITE_POSITION.x, OWIN_SPRITE_POSITION.y);
	window.draw(oWinSprite);
}

int CheckEndGame(sf::RenderWindow& window, int field[FIELD_CELLS][FIELD_CELLS], int turnCounter)
{
	//draw
	sf::Texture drawTexture;
	drawTexture.loadFromFile("image/draw.png");
	sf::Sprite drawSprite;
	drawSprite.setTexture(drawTexture);
	//xwin
	sf::Texture xWinTexture;
	xWinTexture.loadFromFile("image/xwins.png");
	sf::Sprite xWinSprite;
	xWinSprite.setTexture(xWinTexture);
	//owin
	sf::Texture oWinTexture;
	oWinTexture.loadFromFile("image/owins.png");
	sf::Sprite oWinSprite;
	oWinSprite.setTexture(oWinTexture);
	

	//check cross win
	if ((field[0][0] == field[1][0]) && (field[1][0] == field[2][0]) && (field[0][0] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if ((field[0][0] == field[0][1]) && (field[0][1] == field[0][2]) && (field[0][0] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if ((field[1][0] == field[1][1]) && (field[1][1] == field[1][2]) && (field[1][0] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if ((field[0][1] == field[1][1]) && (field[1][1] == field[2][1]) && (field[0][1] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if (field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][0] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if (field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[0][2] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;

	}
	else if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if (field[2][0] == field[1][1] && field[1][1] == field[0][2] && field[2][0] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	//check round win
	else if ((field[0][0] == field[1][0]) && (field[1][0] == field[2][0]) && (field[0][0] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if ((field[0][0] == field[0][1]) && (field[0][1] == field[0][2]) && (field[0][0] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if ((field[1][0] == field[1][1]) && (field[1][1] == field[1][2]) && (field[1][0] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if ((field[0][1] == field[1][1]) && (field[1][1] == field[2][1]) && (field[0][1] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][0] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[0][2] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[2][0] == field[1][1] && field[1][1] == field[0][2] && field[2][0] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	//draw
	else if (turnCounter >= 9)
	{
		drawSprite.setPosition(DRAW_SPRITE_POSITION.x, DRAW_SPRITE_POSITION.y);
		window.draw(drawSprite);
		return 1;
	}
	return 0;
}

void CheckMenuUsing(sf::RenderWindow& window, int& playerCount, int& turnCounter, bool& isPlayersTurn, int field[FIELD_CELLS][FIELD_CELLS])
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseX >= 676 && mouseX <= 804 && mouseY >= 360 && mouseY <= 488)
		{
			for (int line= 0; line< FIELD_CELLS; line++)
			{
				for (int colomn = 0; colomn < FIELD_CELLS; colomn++)
				{
					field[line][colomn] = 0;
				}
			}
			playerCount = 0;
			turnCounter = 0;
			isPlayersTurn = true;
		}
		else if (mouseX >= 676 && mouseX <= 804 && mouseY >= 150 && mouseY <= 278)
		{
			for (int line= 0; line< FIELD_CELLS; line++)
			{
				for (int colomn = 0; colomn < FIELD_CELLS; colomn++)
				{
					field[line][colomn] = 0;
				}
			}
			turnCounter = 0;
			isPlayersTurn = true;
		}
	}
}

//start menu. choose number of players 1\2
void ChoosePlayersNumber(sf::RenderWindow& window, int& playerCount, sf::Sprite& currentSprite)
{
	if (playerCount == 0)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		if (mouseX >= ONE_PLAYER_SPRITE_POSITION_X.x && mouseX <= ONE_PLAYER_SPRITE_POSITION_X.y && mouseY >= ONE_PLAYER_SPRITE_POSITION_Y.x && mouseY <= ONE_PLAYER_SPRITE_POSITION_Y.y)
		{
			currentSprite.setPosition(CURRENTSPRITE_POSITION_IF_ONE_PLAYER.x, CURRENTSPRITE_POSITION_IF_ONE_PLAYER.y);
			window.draw(currentSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playerCount = 1;
			}
		}
		else if (mouseX >= TWO_PLAYERS_SPRITE_POSITION_X.x && mouseX <= TWO_PLAYERS_SPRITE_POSITION_X.y && mouseY >= TWO_PLAYERS_SPRITE_POSITION_Y.x && mouseY <= TWO_PLAYERS_SPRITE_POSITION_Y.y)
		{
			currentSprite.setPosition(CURRENTSPRITE_POSITION_IF_TWO_PLAYERS.x, CURRENTSPRITE_POSITION_IF_TWO_PLAYERS.y);
			window.draw(currentSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playerCount = 2;
			}
		}
	}

}

void DrawStartMenu(sf::RectangleShape& rectangleStart, sf::Sprite& textSprite, sf::Sprite& oneSprite, sf::Sprite& twoSprite, sf::RenderWindow& window)
{
	window.draw(rectangleStart);
	window.draw(textSprite);
	window.draw(oneSprite);
	window.draw(twoSprite);
}

int main()
{
	bool isPlayersTurn = true;
	int field[FIELD_CELLS][FIELD_CELLS] =
	{
		{ 0,0,0 },{ 0,0,0 },{ 0,0,0 }
	};
	int turnCounter = 0;
	int playerCount = 0;

	sf::RectangleShape rectangleStart(sf::Vector2f(830, 620));
	rectangleStart.setFillColor(sf::Color::White);
	rectangleStart.setPosition(SPACE_BETWEEN_CELL, SPACE_BETWEEN_CELL);

	//cross\round sprites
	sf::Texture crossTexture;
	sf::Texture roundTexture;
	crossTexture.loadFromFile("image/cross.png");
	roundTexture.loadFromFile("image/round.png");
	sf::Sprite crossSprite;
	sf::Sprite roundSprite;
	crossSprite.setTexture(crossTexture);
	roundSprite.setTexture(roundTexture);

	//text
	sf::Texture textTexture;
	textTexture.loadFromFile("image/text.png");
	sf::Sprite textSprite;
	textSprite.setTexture(textTexture);
	textSprite.setPosition(100, 100);

	//1 player
	sf::Texture oneTexture;
	oneTexture.loadFromFile("image/1.png");
	sf::Sprite oneSprite;
	oneSprite.setTexture(oneTexture);
	oneSprite.setPosition(100, 260);

	//2 player
	sf::Texture twoTexture;
	twoTexture.loadFromFile("image/2.png");
	sf::Sprite twoSprite;
	twoSprite.setTexture(twoTexture);
	twoSprite.setPosition(100, 370);

	//current player choise
	sf::Texture currentTexture;
	currentTexture.loadFromFile("image/current.png");
	sf::Sprite currentSprite;
	currentSprite.setTexture(currentTexture);

	sf::RenderWindow window(sf::VideoMode(850, 640), "Tic-Tac-Toe", sf::Style::Close);

	sf::RectangleShape rectangle(sf::Vector2f(CELL_SIDE, CELL_SIDE));
	rectangle.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear();

		if (playerCount == 0)
		{
			DrawStartMenu(rectangleStart, textSprite, oneSprite, twoSprite, window);
			ChoosePlayersNumber(window, playerCount, currentSprite);
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				DrawStartMenu(rectangleStart, textSprite, oneSprite, twoSprite, window);
				ChoosePlayersNumber(window, playerCount, currentSprite);
			}
		}

		if (playerCount != 0)
		{
			DrawWindow(rectangle, window);
			CheckMenuUsing(window, playerCount, turnCounter, isPlayersTurn, field);
			DrawMarksInCell(window, field, crossSprite, roundSprite);
			if (CheckEndGame(window, field, turnCounter) == 0)
			{
				if (playerCount == 1)
				{
					PcTurn(window, turnCounter, field, isPlayersTurn);
				}
				PutMarkInCell(window, isPlayersTurn, turnCounter, field);
				CheckEndGame(window, field, turnCounter);
			}
		}
		window.display();
	}
	return 0;
}
