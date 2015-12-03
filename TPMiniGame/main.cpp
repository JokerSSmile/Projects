#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "constants.h"
#include "ai.h"
#include "sprites.h"

using namespace std;

void DrawWindow(sf::RenderWindow & window)
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

void DrawMarksInCell(sf::RenderWindow& window, int field[FIELD_CELLS][FIELD_CELLS], Sprites& mySprites)
{
	mySprites.SetMarks();
	for (int line = 0; line < FIELD_CELLS; line++)
	{
		for (int colomn = 0; colomn < FIELD_CELLS; colomn++)
		{	
			
			if (field[line][colomn] == 1)
			{
				mySprites.crossSprite.setPosition(colomn * CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL, line* CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL);
				window.draw(mySprites.crossSprite);
			}
			else if (field[line][colomn] == 2)
			{
				mySprites.roundSprite.setPosition(colomn * CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL, line* CELL_SIZE_PLUS_SPACE + SPACE_BETWEEN_MARK_AND_CELL);
				window.draw(mySprites.roundSprite);
			}
		}
	}
}

void FillCell(int line, int colomn, int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	if (field[line][colomn] == 0)
	{
		if (isPlayersTurn == false)
		{
			field[line][colomn] = 2;
			isPlayersTurn = true;
		}
		else
		{
			field[line][colomn] = 1;
			isPlayersTurn = false;
		}
	}
}

void SetTurnCounter(int field[FIELD_CELLS][FIELD_CELLS], int& turnCounter)
{
	turnCounter = 0;
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
}

bool isMouseInRange(sf::Vector2i& rangeX, sf::Vector2i& rangeY, sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	//cout << rangeX.x << "  " << rangeX.y << "   " << mouseX << endl;

	if (rangeX.x <= mouseX && mouseX <= rangeX.y && rangeY.x <= mouseY && mouseY <= rangeY.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int PutMarkInCell(sf::RenderWindow& window, bool& isPlayersTurn, int& turnCounter, int field[FIELD_CELLS][FIELD_CELLS])
{
	SetTurnCounter(field, turnCounter);
	
	//заполняем массив при ходе
	if (sf::Event::GainedFocus && sf::Event::MouseEntered)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (isMouseInRange(sf::Vector2i(SPACE_BETWEEN_CELL, CELL_SIZE_PLUS_SPACE), sf::Vector2i(SPACE_BETWEEN_CELL, CELL_SIZE_PLUS_SPACE), window))
			{
				FillCell(FIRST_LINE, FIRST_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(SPACE_BETWEEN_CELL, CELL_SIZE_PLUS_SPACE), sf::Vector2i(SECOND_CELL_POSITION_START, SECOND_CELL_POSITION_END), window))
			{
				FillCell(SECOND_LINE, FIRST_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(SPACE_BETWEEN_CELL, CELL_SIZE_PLUS_SPACE), sf::Vector2i(THIRD_CELL_POSITION_START, THIRD_CELL_POSITION_END), window))
			{
				FillCell(THIRD_LINE, FIRST_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(SECOND_CELL_POSITION_START, SECOND_CELL_POSITION_END), sf::Vector2i(SPACE_BETWEEN_CELL, CELL_SIZE_PLUS_SPACE), window))
			{
				FillCell(FIRST_LINE, SECOND_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(SECOND_CELL_POSITION_START, SECOND_CELL_POSITION_END), sf::Vector2i(SECOND_CELL_POSITION_START, SECOND_CELL_POSITION_END), window))
			{
				FillCell(SECOND_LINE, SECOND_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(SECOND_CELL_POSITION_START, SECOND_CELL_POSITION_END), sf::Vector2i(THIRD_CELL_POSITION_START, THIRD_CELL_POSITION_END), window))
			{
				FillCell(THIRD_LINE, SECOND_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(THIRD_CELL_POSITION_START, THIRD_CELL_POSITION_END), sf::Vector2i(SPACE_BETWEEN_CELL, CELL_SIZE_PLUS_SPACE), window))
			{
				FillCell(FIRST_LINE, THIRD_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(THIRD_CELL_POSITION_START, THIRD_CELL_POSITION_END), sf::Vector2i(SECOND_CELL_POSITION_START, SECOND_CELL_POSITION_END), window))
			{
				FillCell(SECOND_LINE, THIRD_COLOMN, field, isPlayersTurn);
			}
			else if (isMouseInRange(sf::Vector2i(THIRD_CELL_POSITION_START, THIRD_CELL_POSITION_END), sf::Vector2i(THIRD_CELL_POSITION_START, THIRD_CELL_POSITION_END), window))
			{
				FillCell(THIRD_LINE, THIRD_COLOMN, field, isPlayersTurn);
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

bool CheckCrossWin(int field[FIELD_CELLS][FIELD_CELLS], sf::RenderWindow& window)
{
	//xwin
	sf::Texture xWinTexture;
	xWinTexture.loadFromFile("image/xwins.png");
	sf::Sprite xWinSprite;
	xWinSprite.setTexture(xWinTexture);

	//check cross win
	if ((field[FIRST_LINE][FIRST_COLOMN] == field[SECOND_LINE][FIRST_COLOMN]) && (field[SECOND_LINE][FIRST_COLOMN] == field[THIRD_LINE][FIRST_COLOMN]) && (field[FIRST_LINE][FIRST_COLOMN] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if ((field[FIRST_LINE][FIRST_COLOMN] == field[FIRST_LINE][SECOND_COLOMN]) && (field[FIRST_LINE][SECOND_COLOMN] == field[FIRST_LINE][THIRD_COLOMN]) && (field[FIRST_LINE][FIRST_COLOMN] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if ((field[SECOND_LINE][FIRST_COLOMN] == field[SECOND_LINE][SECOND_COLOMN]) && (field[SECOND_LINE][SECOND_COLOMN] == field[SECOND_LINE][THIRD_COLOMN]) && (field[SECOND_LINE][FIRST_COLOMN] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if ((field[FIRST_LINE][SECOND_COLOMN] == field[SECOND_LINE][SECOND_COLOMN]) && (field[SECOND_LINE][SECOND_COLOMN] == field[THIRD_LINE][SECOND_COLOMN]) && (field[FIRST_LINE][SECOND_COLOMN] == 1))
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if (field[THIRD_LINE][FIRST_COLOMN] == field[THIRD_LINE][SECOND_COLOMN] && field[THIRD_LINE][SECOND_COLOMN] == field[THIRD_LINE][THIRD_COLOMN] && field[THIRD_LINE][FIRST_COLOMN] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if (field[FIRST_LINE][THIRD_COLOMN] == field[SECOND_LINE][THIRD_COLOMN] && field[SECOND_LINE][THIRD_COLOMN] == field[THIRD_LINE][THIRD_COLOMN] && field[FIRST_LINE][THIRD_COLOMN] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;

	}
	else if (field[FIRST_LINE][FIRST_COLOMN] == field[SECOND_LINE][SECOND_COLOMN] && field[SECOND_LINE][SECOND_COLOMN] == field[THIRD_LINE][THIRD_COLOMN] && field[FIRST_LINE][FIRST_COLOMN] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
	else if (field[THIRD_LINE][FIRST_COLOMN] == field[SECOND_LINE][SECOND_COLOMN] && field[SECOND_LINE][SECOND_COLOMN] == field[FIRST_LINE][THIRD_COLOMN] && field[THIRD_LINE][FIRST_COLOMN] == 1)
	{
		DrawXWinSprite(xWinSprite, window);
		return 1;
	}
}

bool CheckRoundWin(int field[FIELD_CELLS][FIELD_CELLS], sf::RenderWindow& window)
{
	//owin
	sf::Texture oWinTexture;
	oWinTexture.loadFromFile("image/owins.png");
	sf::Sprite oWinSprite;
	oWinSprite.setTexture(oWinTexture);

	//check round win
	if ((field[FIRST_LINE][FIRST_COLOMN] == field[SECOND_LINE][FIRST_COLOMN]) && (field[SECOND_LINE][FIRST_COLOMN] == field[THIRD_LINE][FIRST_COLOMN]) && (field[FIRST_LINE][FIRST_COLOMN] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if ((field[FIRST_LINE][FIRST_COLOMN] == field[FIRST_LINE][SECOND_COLOMN]) && (field[FIRST_LINE][SECOND_COLOMN] == field[FIRST_LINE][THIRD_COLOMN]) && (field[FIRST_LINE][FIRST_COLOMN] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if ((field[SECOND_LINE][FIRST_COLOMN] == field[SECOND_LINE][SECOND_COLOMN]) && (field[SECOND_LINE][SECOND_COLOMN] == field[SECOND_LINE][THIRD_COLOMN]) && (field[SECOND_LINE][FIRST_COLOMN] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if ((field[FIRST_LINE][SECOND_COLOMN] == field[SECOND_LINE][SECOND_COLOMN]) && (field[SECOND_LINE][SECOND_COLOMN] == field[THIRD_LINE][SECOND_COLOMN]) && (field[FIRST_LINE][SECOND_COLOMN] == 2))
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[THIRD_LINE][FIRST_COLOMN] == field[THIRD_LINE][SECOND_COLOMN] && field[THIRD_LINE][SECOND_COLOMN] == field[THIRD_LINE][THIRD_COLOMN] && field[THIRD_LINE][FIRST_COLOMN] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[FIRST_LINE][THIRD_COLOMN] == field[SECOND_LINE][THIRD_COLOMN] && field[SECOND_LINE][THIRD_COLOMN] == field[THIRD_LINE][THIRD_COLOMN] && field[FIRST_LINE][THIRD_COLOMN] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[FIRST_LINE][FIRST_COLOMN] == field[SECOND_LINE][SECOND_COLOMN] && field[SECOND_LINE][SECOND_COLOMN] == field[THIRD_LINE][THIRD_COLOMN] && field[FIRST_LINE][FIRST_COLOMN] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
	else if (field[THIRD_LINE][FIRST_COLOMN] == field[SECOND_LINE][SECOND_COLOMN] && field[SECOND_LINE][SECOND_COLOMN] == field[FIRST_LINE][THIRD_COLOMN] && field[THIRD_LINE][FIRST_COLOMN] == 2)
	{
		DrawOWinSprite(oWinSprite, window);
		return 1;
	}
}

bool CheckEndGame(sf::RenderWindow& window, int field[FIELD_CELLS][FIELD_CELLS], int turnCounter)
{
	//draw
	sf::Texture drawTexture;
	drawTexture.loadFromFile("image/draw.png");
	sf::Sprite drawSprite;
	drawSprite.setTexture(drawTexture);

	if (CheckCrossWin(field, window) || CheckRoundWin(field, window))
	{
		return 1;
	}
	
	if (turnCounter >= MAX_TURNS)
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
		if (isMouseInRange(sf::Vector2i(EXIT_POSITION.x, EXIT_POSITION.x + SPRITE_SIDE), sf::Vector2i(EXIT_POSITION.y, EXIT_POSITION.y + SPRITE_SIDE), window))
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
		else if (isMouseInRange(sf::Vector2i(REFRESH_SPRITE_POSITION.x, REFRESH_SPRITE_POSITION.x + SPRITE_SIDE), sf::Vector2i(REFRESH_SPRITE_POSITION.y, REFRESH_SPRITE_POSITION.x + SPRITE_SIDE), window))
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
void ChoosePlayersNumber(sf::RenderWindow& window, int& playerCount, Sprites& mySprites)
{
	mySprites.SetCurrentChoise();
	if (playerCount == 0)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		if (isMouseInRange(sf::Vector2i(ONE_PLAYER_SPRITE_POSITION_X.x, ONE_PLAYER_SPRITE_POSITION_X.y), sf::Vector2i(ONE_PLAYER_SPRITE_POSITION_Y.x, ONE_PLAYER_SPRITE_POSITION_Y.y), window))
		{
			mySprites.currentSprite.setPosition(CURRENTSPRITE_POSITION_IF_ONE_PLAYER.x, CURRENTSPRITE_POSITION_IF_ONE_PLAYER.y);
			window.draw(mySprites.currentSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playerCount = 1;
			}
		}
		else if (isMouseInRange(sf::Vector2i(TWO_PLAYERS_SPRITE_POSITION_X.x, TWO_PLAYERS_SPRITE_POSITION_X.y), sf::Vector2i(TWO_PLAYERS_SPRITE_POSITION_Y.x, TWO_PLAYERS_SPRITE_POSITION_Y.y), window))
		{
			mySprites.currentSprite.setPosition(CURRENTSPRITE_POSITION_IF_TWO_PLAYERS.x, CURRENTSPRITE_POSITION_IF_TWO_PLAYERS.y);
			window.draw(mySprites.currentSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playerCount = 2;
			}
		}
	}

}

void DrawStartMenu(Sprites& mySprites, sf::RenderWindow& window)
{
	mySprites.SetStartRectangle();
	mySprites.SetText();
	mySprites.SetChoosePlayersCount();
	window.draw(mySprites.rectangleStart);
	window.draw(mySprites.textSprite);
	window.draw(mySprites.oneSprite);
	window.draw(mySprites.twoSprite);
}

void ProcessEvents(sf::RenderWindow& window)
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
}

void StartScreen(int& playerCount, Sprites& mySprites, sf::RenderWindow& window)
{
		DrawStartMenu(mySprites, window);
		ChoosePlayersNumber(window, playerCount, mySprites);
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			DrawStartMenu(mySprites, window);
			ChoosePlayersNumber(window, playerCount, mySprites);
		}
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

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Tic-Tac-Toe", sf::Style::Close);

	Sprites mySprites;

	while (window.isOpen())
	{
		ProcessEvents(window);

		window.clear();
		
		if (playerCount == 0)
		{
			StartScreen(playerCount, mySprites, window);
		}
		if (playerCount != 0)
		{
			DrawWindow(window);
			CheckMenuUsing(window, playerCount, turnCounter, isPlayersTurn, field);
			DrawMarksInCell(window, field, mySprites);
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
