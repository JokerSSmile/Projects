#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


int turn = 1;
int field[3][3] =
{
	{0,0,0}, {0,0,0}, {0,0,0}
};
int turnCounter = 0;
int playerCount = 0;


//рисуем интерфейс
void drawWindow(sf::RectangleShape, sf::RenderWindow & window)
{
	int posx = 10;
	int posy = 10;


	sf::RectangleShape rectangle(sf::Vector2f(200, 200));
	rectangle.setFillColor(sf::Color::White);

	for (int i = 0; i < 3; i++)
	{
		rectangle.setPosition(posx, posy);
		for (int j = 0; j < 3; j++)
		{
			rectangle.setPosition(posx, posy);
			posy = posy + 210;
			window.draw(rectangle);
		}
		posx = posx + 210;
		posy = 10;
	}
	posx = 10;
	posy = 10;

	//menu
	sf::RectangleShape rectangleMenu(sf::Vector2f(200, 620));
	rectangleMenu.setFillColor(sf::Color::White);
	rectangleMenu.setPosition(640, 10);
	window.draw(rectangleMenu);

	//refresh
	sf::Texture refreshTexture;
	refreshTexture.loadFromFile("image/refresh.png");
	sf::Sprite refreshSprite;
	refreshSprite.setTexture(refreshTexture);
	refreshSprite.setPosition(676, 150);
	window.draw(refreshSprite);

	//exit
	sf::Texture exitTexture;
	exitTexture.loadFromFile("image/exit.png");
	sf::Sprite exitSprite;
	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(676, 360);
	window.draw(exitSprite);
}


// выводим х и о на экран
void drawxo(sf::RenderWindow & window)
{

	//textures/sprites
	sf::Texture crossTexture;
	sf::Texture roundTexture;
	crossTexture.loadFromFile("image/cross.png");
	roundTexture.loadFromFile("image/round.png");
	sf::Sprite crossSprite;
	sf::Sprite roundSprite;
	crossSprite.setTexture(crossTexture);
	roundSprite.setTexture(roundTexture);


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{	
			
			if (field[i][j] == 1)
			{
				crossSprite.setPosition(j * 210 + 46, i * 210 + 46);
				window.draw(crossSprite);
			}
			else if (field[i][j] == 2)
			{
				roundSprite.setPosition(j * 210 + 46, i * 210 + 46);
				window.draw(roundSprite);
			}
		}
	}
}


// проставляем х и о при нажатиях
int  isMouseOnCell(sf::RenderWindow & window, int turn)
{
	turnCounter = 0;
	sf::Texture crossWinTexture;
	crossWinTexture.loadFromFile("image/xwins.png");
	sf::Sprite crossWinSprite;
	crossWinSprite.setTexture(crossWinTexture);


	float MX = sf::Mouse::getPosition(window).x;
	float MY = sf::Mouse::getPosition(window).y;


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] != 0)
			{
				turnCounter += 1;
			}
		}
	}
	

	if (turnCounter % 2 == 0)
		turn = 1;
	else if (turnCounter % 2 == 1)
		turn = 2;


	//заполняем массив при ходе
	if (sf::Event::GainedFocus && sf::Event::MouseEntered)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (10 <= MX && MX <= 210)
			{
				if (10 <= MY && MY <= 210)
				{
					if (field[0][0] == 0)
					{
						if (turn == 2)
						{
							field[0][0] = 2;
							turn = 1;
						}
						else
						{
							field[0][0] = 1;
							turn = 2;
						}
					}
				}
				else if (220 <= MY && MY <= 420)
				{
					if (field[1][0] == 0)
					{
						if (turn == 2)
						{
							field[1][0] = 2;
							turn = 1;
						}
						else
						{
							field[1][0] = 1;
							turn = 2;
						}
					}
				}
				else if (430 <= MY && MY <= 630)
				{
					if (field[2][0] == 0)
					{
						if (turn == 2)
						{
							field[2][0] = 2;
							turn = 1;
						}
						else
						{
							field[2][0] = 1;
							turn = 2;
						}
					}
				}
			}
			else if (220 <= MX && MX <= 420)
			{
				if (10 <= MY && MY <= 210)
				{
					if (field[0][1] == 0)
					{
						if (turn == 2)
						{
							field[0][1] = 2;
							turn = 1;
						}
						else
						{
							field[0][1] = 1;
							turn = 2;
						}
					}
				}


				else if (220 <= MY && MY <= 420)
				{
					if (field[1][1] == 0)
					{
						if (turn == 2)
						{
							field[1][1] = 2;
							turn = 1;
						}
						else
						{
							field[1][1] = 1;
							turn = 2;
						}
					}
				}
				else if (430 <= MY && MY <= 630)
				{
					if (field[2][1] == 0)
					{
						if (turn == 2)
						{
							field[2][1] = 2;
							turn = 1;
						}
						else
						{
							field[2][1] = 1;
							turn = 2;
						}
					}
				}
			}
			else if (430 <= MX && MX <= 630)
			{
				if (10 <= MY && MY <= 210)
				{
					if (field[0][2] == 0)
					{
						if (turn == 2)
						{
							field[0][2] = 2;
							turn = 1;
						}
						else
						{
							field[0][2] = 1;
							turn = 2;
						}
					}
				}


				else if (220 <= MY && MY <= 420)
				{
					if (field[1][2] == 0)
					{
						if (turn == 2)
						{
							field[1][2] = 2;
							turn = 1;
						}
						else
						{
							field[1][2] = 1;
							turn = 2;
						}
					}
				}
				else if (430 <= MY && MY <= 630)
				{
					if (field[2][2] == 0)
					{
						if (turn == 2)
						{
							field[2][2] = 2;
							turn = 1;
						}
						else
						{
							field[2][2] = 1;
							turn = 2;
						}
					}
				}
			}
		}
	}
	return turnCounter;
}


//проверяем на победу или ничью
int checkWin(sf::RenderWindow & window)
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
	

	//проверка на победу х
	if (((field[0][0] == field[1][0]) && (field[1][0] == field[2][0]) && (field[0][0] == 1)) || ((field[0][0] == field[0][1]) && (field[0][1] == field[0][2]) && (field[0][0] == 1)))
	{
		xWinSprite.setPosition(40, 240);
		window.draw(xWinSprite);
		return 1;
	}
	else if (((field[1][0] == field[1][1]) && (field[1][1] == field[1][2]) && (field[1][0] == 1)) || ((field[0][1] == field[1][1]) && (field[1][1] == field[2][1]) && (field[0][1] == 1)))
	{
		xWinSprite.setPosition(40, 240);
		window.draw(xWinSprite);
		return 1;
	}
	else if ((field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][0] == 1) || (field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[0][2] == 1))
	{
		xWinSprite.setPosition(40, 240);
		window.draw(xWinSprite);
		return 1;
	}
	else if ((field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] == 1) || (field[2][0] == field[1][1] && field[1][1] == field[0][2] && field[2][0] == 1))
	{
		xWinSprite.setPosition(40, 240);
		window.draw(xWinSprite);
		return 1;
	}
	//проверка на победу o
	else if (((field[0][0] == field[1][0]) && (field[1][0] == field[2][0]) && (field[0][0] == 2)) || ((field[0][0] == field[0][1]) && (field[0][1] == field[0][2]) && (field[0][0] == 2)))
	{
		oWinSprite.setPosition(40, 240);
		window.draw(oWinSprite);
		return 1;
	}
	else if (((field[1][0] == field[1][1]) && (field[1][1] == field[1][2]) && (field[1][0] == 2)) || ((field[0][1] == field[1][1]) && (field[1][1] == field[2][1]) && (field[0][1] == 2)))
	{
		oWinSprite.setPosition(40, 240);
		window.draw(oWinSprite);
		return 1;
	}
	else if ((field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][0] == 2) || (field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[0][2] == 2))
	{
		oWinSprite.setPosition(40, 240);
		window.draw(oWinSprite);
		return 1;
	}
	else if ((field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] == 2) || (field[2][0] == field[1][1] && field[1][1] == field[0][2] && field[2][0] == 2))
	{
		oWinSprite.setPosition(40, 240);
		window.draw(oWinSprite);
		return 1;
	}
	//draw
	else if (turnCounter >= 9)
	{
		drawSprite.setPosition(110, 240);
		window.draw(drawSprite);
		return 1;
	}
	return 0;
}

void firstPCTurn()
{
	field[1][1] = 1;
	turn = 2;
}

void secondPCTurn()
{
	if (field[0][0] == 0 && field[0][2] == 0 && field[2][0] == 0 && field[2][2] == 0)
	{
		if (field[0][2] == 0)
		{
			field[0][2] = 1;
			turn = 2;
		}
		else
		{
			field[0][0] = 1;
			turn = 2;
		}
	}
	else if ((field[0][1] == 0 && field[1][0] == 0 && field[2][1] == 0 && field[1][2] == 0))
	{

		if (field[2][0] == 0)
		{
			field[2][0] = 1;
			turn = 2;
		}
		else
		{
			field[0][2] = 1;
			turn = 2;
		}
	}
}

void thirdPCTurn()
{
	if (field[0][2] == 1 && field[1][1] == 1 && field[2][0] == 0)
	{
		field[2][0] = 1;
		turn = 2;
	}
	else if (field[1][0] == 2 && field[2][0] == 2 && field[0][0] == 0)
	{
		field[0][0] = 1;
		turn = 2;
	}
	else if (field[0][2] == 1 && field[2][0] == 2)
	{
		if (field[2][2] == 0)
		{
			if (field[1][2] == 0)
			{
				field[2][2] = 1;
				turn = 2;
			}
			else if (field[1][2] == 2)
			{
				field[0][0] = 1;
				turn = 2;
			}
		}
		else if (field[2][2] == 2)
		{
			field[2][1] = 1;
			turn = 2;
		}
	}
	else if (field[0][2] == 2)
	{
		if (field[0][0] == 2)
		{
			field[0][1] = 1;
			turn = 2;
		}
		else if (field[0][1] == 2)
		{
			field[0][0] = 1;
			turn = 2;
		}
		else if (field[1][0] == 2)
		{
			field[2][1] = 1;
			turn = 2;
		}
		else if (field[1][2] == 2)
		{
			field[2][2] = 1;
			turn = 2;
		}
		else if (field[2][1] == 2)
		{
			field[1][0] = 1;
			turn = 2;
		}
		else if (field[2][2] == 2)
		{
			field[1][2] = 1;
			turn = 2;
		}
	}
	else if (field[0][2] == 0)
	{
		field[0][2] = 1;
		turn = 2;
	}
}

void forthPCTurn()
{
	if (field[0][2] == 1 && field[2][0] == 2)
	{
		if (field[2][2] == 1)
		{
			if (field[1][2] == 0)
			{
				field[1][2] = 1;
				turn = 2;
			}

			else if (field[1][2] == 2 && field[0][0] == 0)
			{
				field[0][0] = 1;
				turn = 2;
			}
			else if (field[0][0] == 2 && field[1][2] == 2 && field)
			{
				field[1][0] = 1;
				turn = 2;
			}
		}
		else if (field[2][2] == 2)
		{
			if (field[1][2] == 2 && field[0][1] == 0 && field[2][1] == 1)
			{
				if (field[0][1] == 0)
				{
					field[0][1] = 1;
				}
			}
			else if (field[1][2] == 2 && field[2][2] == 2 && field[1][1] == 1)
			{
				if (field[0][1] == 0)
				{
					field[0][1] = 1;
					turn = 2;
				}
			}
			else if (field[0][1] == 2 && field[2][1] == 1)
			{
				if (field[1][0] == 0)
				{
					field[1][0] = 1;
					turn = 2;
				}
			}
			else if (field[0][0] == 1 && field[1][0] == 2 && field[2][0] == 2)
			{
				if (field[0][1] == 0)
				{
					field[0][1] = 1;
					turn = 2;
				}
			}
		}
		else if (field[2][2] == 0)
		{
			if (field[0][0] == 1 && field[1][2] == 2)
			{
				if (field[2][1] == 2)
				{
					if (field[0][1] == 0)
					{
						field[0][1] = 0;
						turn = 2;
					}
				}
				else if (field[0][1] == 2)
				{
					if (field[2][2] == 0)
					{
						field[2][2] = 1;
						turn = 2;
					}
				}
				else if (field[0][1] == 0 && field[1][0] == 2 && field[2][0] == 2)
				{
					field[0][1] = 1;
					turn = 2;
				}
			}
			else if (field[0][0] == 1 && field[1][0] == 2 && field[2][0] == 2)
			{
				if (field[2][2] == 0)
				{
					field[2][2] = 1;
					turn = 2;
				}
				else
				{
					field[0][1] = 1;
					turn = 2;
				}
			}
		}
	}
	else if (field[0][2] == 2)
	{
		if (field[0][0] == 2)
		{
			if (field[2][1] == 0)
			{
				field[2][1] = 1;
				turn = 2;
			}
			else if (field[2][1] == 2)
			{
				field[1][2] = 1;
				turn = 2;
			}
		}
		else if (field[0][1] == 2 && field[0][0] == 1)
		{
			if (field[1][0] == 0)
			{
				field[1][0] = 1;
				turn = 2;
			}
			else field[2][2] = 1;
		}
		else if (field[1][0] == 2 && field[2][1] == 1)
		{
			if (field[2][2] == 0)
			{
				field[2][2] = 1;
				turn = 2;
			}
			else field[0][1] = 1;
			turn = 2;
		}
		else if (field[1][2] == 2 && field[2][2] == 1)
		{
			if (field[2][1] == 0)
				field[2][1] = 1;
			else
			{
				field[0][0] = 1;
			}
		}
		else if (field[2][2] == 2 && field[1][2] == 1)
		{
			if (field[1][0] == 0)
				field[1][0] = 1;
			else field[0][1] = 1;
		}
		else if (field[2][1] == 2)
		{
			if (field[1][2] == 0)
				field[1][2] = 1;
			else field[0][0] = 1;
		}
	}
	else if (field[2][2] == 2 && field[1][2] == 2 && field[0][1] == 0 && field[2][1] == 1)
	{
		field[0][1] = 1;
		turn = 2;
	}
}

void fifthPCTurn()
{
	if (field[0][1] == 0)
		field[0][1] = 1;
	else if (field[2][1] == 0)
		field[2][1] = 1;
	else if (field[1][0] == 1 && field[2][1] == 1)
	{
		if (field[0][0] == 0)
			field[0][0] = 1;
		else if (field[1][2] == 0)
			field[1][2] = 1;
	}
	else if (field[0][0] == 2 && field[0][2] == 2 && field[1][2] == 1)
	{
		if (field[1][0] == 0)
		{
			field[1][0] = 1;
			turn = 2;
		}
		else field[2][2] = 1;
	}
	else if (field[0][1] == 1 && field[1][2] == 1 && field[0][2] == 2)
	{
		if (field[2][1] == 0)
			field[2][1] = 1;
		else field[0][0] = 1;
	}
}

// ход пк
void  pcTurn(sf::RenderWindow & window, int turnCounter)
{
	if (turnCounter == 0)
	{
		firstPCTurn();
	}
	else if (turnCounter == 2)
	{
		secondPCTurn();
	}
	else if (turnCounter == 4)
	{
		thirdPCTurn();
	}
	else if (turnCounter == 6)
	{
		forthPCTurn();
	}
	else if (turnCounter == 8)
	{
		fifthPCTurn();
	}
}


void menuUsed(sf::RenderWindow & window)
{
	float MX = sf::Mouse::getPosition(window).x;
	float MY = sf::Mouse::getPosition(window).y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (MX >= 676 && MX <= 804 && MY >= 360 && MY <= 488)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					field[i][j] = 0;
				}
			}
			playerCount = 0;
			turnCounter = 0;
			turn = 1;
		}
		else if (MX >= 676 && MX <= 804 && MY >= 150 && MY <= 278)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					field[i][j] = 0;
				}
			}
			turnCounter = 0;
			turn = 1;
		}
	}
}


void playersNumber(sf::RenderWindow & window)
{
	if (playerCount == 0)
	{
		float MX = sf::Mouse::getPosition(window).x;
		float MY = sf::Mouse::getPosition(window).y;

		//menu vibora kol-va igrokov
		sf::RectangleShape rectangleStart(sf::Vector2f(830, 620));
		rectangleStart.setFillColor(sf::Color::White);
		rectangleStart.setPosition(10, 10);
		window.draw(rectangleStart);

		//text
		sf::Texture textTexture;
		textTexture.loadFromFile("image/text.png");
		sf::Sprite textSprite;
		textSprite.setTexture(textTexture);
		textSprite.setPosition(100, 100);
		window.draw(textSprite);

		//1 player
		sf::Texture oneTexture;
		oneTexture.loadFromFile("image/1.png");
		sf::Sprite oneSprite;
		oneSprite.setTexture(oneTexture);
		oneSprite.setPosition(100, 260);
		window.draw(oneSprite);

		//2 player
		sf::Texture twoTexture;
		twoTexture.loadFromFile("image/2.png");
		sf::Sprite twoSprite;
		twoSprite.setTexture(twoTexture);
		twoSprite.setPosition(100, 370);
		window.draw(twoSprite);

		//current player choise
		sf::Texture currentTexture;
		currentTexture.loadFromFile("image/current.png");
		sf::Sprite currentSprite;
		currentSprite.setTexture(currentTexture);


		if (MX >= 100 && MX <= 486 && MY >= 260 && MY <= 361)
		{
			currentSprite.setPosition(40, 270);
			window.draw(currentSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playerCount = 1;
			}
		}
		else if (MX >= 100 && MX <= 559 && MY >= 370 && MY <= 471)
		{
			currentSprite.setPosition(40, 380);
			window.draw(currentSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playerCount = 2;
			}
		}
	}

}



int main()
{
	//okno
	sf::RenderWindow window(sf::VideoMode(850, 640), "Tic-Tac-Toe", sf::Style::Close);

	//kvadrati
	sf::RectangleShape rectangle(sf::Vector2f(200, 200));
	rectangle.setFillColor(sf::Color::Green);

	//poka okno otkrito
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

		//ochistka
		window.clear();

		if (playerCount == 0)
		{
			playersNumber(window);
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playersNumber(window);
			}
		}

		if (playerCount != 0)
		{
			drawWindow(rectangle, window);
			menuUsed(window);
			drawxo(window);
			if (checkWin(window) == 0)
			{
				if (playerCount == 1)
				{
					pcTurn(window, turnCounter);
				}
				isMouseOnCell(window, turn);
				checkWin(window);
			}
		}
		window.display();
	}
	return 0;
}