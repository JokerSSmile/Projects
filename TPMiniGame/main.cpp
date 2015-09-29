#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


int turn = 1;
int field[3][3] =
{
	{0,0,0}, {0,0,0}, {0,0,0}
};
int turnCounter = 0;







//рисуем поле 3x3
void drawField(sf::RectangleShape, sf::RenderWindow & window)
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
				if (i == 0 && j == 0)
				{
					crossSprite.setPosition(46, 46);
					window.draw(crossSprite);
				}
				if (i == 0 && j == 1)
				{
					crossSprite.setPosition(256, 46);
					window.draw(crossSprite);
				}
				if (i == 0 && j == 2)
				{
					crossSprite.setPosition(466, 46);
					window.draw(crossSprite);
				}
				if (i == 1 && j == 0)
				{
					crossSprite.setPosition(46, 256);
					window.draw(crossSprite);
				}
				if (i == 1 && j == 1)
				{
					crossSprite.setPosition(256, 256);
					window.draw(crossSprite);
				}
				if (i == 1 && j == 2)
				{
					crossSprite.setPosition(466, 256);
					window.draw(crossSprite);
				}
				if (i == 2 && j == 0)
				{
					crossSprite.setPosition(46, 466);
					window.draw(crossSprite);
				}
				if (i == 2 && j == 1)
				{
					crossSprite.setPosition(256, 466);
					window.draw(crossSprite);
				}
				if (i == 2 && j == 2)
				{
					crossSprite.setPosition(466, 466);
					window.draw(crossSprite);
				}
			}
			else if (field[i][j] == 2)
			{
				if (i == 0 && j == 0)
				{
					roundSprite.setPosition(46, 46);
					window.draw(roundSprite);
				}
				if (i == 0 && j == 1)
				{
					roundSprite.setPosition(256, 46);
					window.draw(roundSprite);
				}
				if (i == 0 && j == 2)
				{
					roundSprite.setPosition(466, 46);
					window.draw(roundSprite);
				}
				if (i == 1 && j == 0)
				{
					roundSprite.setPosition(46, 256);
					window.draw(roundSprite);
				}
				if (i == 1 && j == 1)
				{
					roundSprite.setPosition(256, 256);
					window.draw(roundSprite);
				}
				if (i == 1 && j == 2)
				{
					roundSprite.setPosition(466, 256);
					window.draw(roundSprite);
				}
				if (i == 2 && j == 0)
				{
					roundSprite.setPosition(46, 466);
					window.draw(roundSprite);
				}
				if (i == 2 && j == 1)
				{
					roundSprite.setPosition(256, 466);
					window.draw(roundSprite);
				}
				if (i == 2 && j == 2)
				{
					roundSprite.setPosition(466, 466);
					window.draw(roundSprite);
				}
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if ((10 <= MX && MX <= 210) && (10 <= MY && MY <= 210) && field[0][0] == 0)
		{
			if (turn == 2)
			{
				field[0][0] = 2;
				turn = 1;
			}
		}
		else if ((220 <= MX && MX <= 420) && (10 <= MY && MY <= 210) && field[0][1] == 0)
		{
			if (turn == 2)
			{
				field[0][1] = 2;
				turn = 1;

			}
		}
		else if ((430 <= MX && MX <= 630) && (10 <= MY && MY <= 210) && field[0][2] == 0)
		{
			if (turn == 2)
			{
				field[0][2] = 2;
				turn = 1;
			}
		}
		else if ((10 <= MX && MX <= 210) && (220 <= MY && MY <= 420) && field[1][0] == 0)
		{
			if (turn == 2)
			{
				field[1][0] = 2;
				turn = 1;
			}
		}
		else if ((220 <= MX && MX <= 420) && (220 <= MY && MY <= 420) && field[1][1] == 0)
		{	
			if (turn == 2)
			{
				field[1][1] = 2;
				turn = 1;
			}
		}
		else if ((430 <= MX && MX <= 630) && (220 <= MY && MY <= 420) && field[1][2] == 0)
		{
			if (turn == 2)
			{
				field[1][2] = 2;
				turn = 1;
			}
		}
		else if ((10 <= MX && MX <= 210) && (430 <= MY && MY <= 630) && field[2][0] == 0)
		{
			if (turn == 2)
			{
				field[2][0] = 2;
				turn = 1;
			}
		}
		else if ((220 <= MX && MX <= 420) && (430 <= MY && MY <= 630) && field[2][1] == 0)
		{
			if (turn == 2)
			{
				field[2][1] = 2;
				turn = 1;
			}
		}
		else if ((430 <= MX && MX <= 630) && (430 <= MY && MY <= 630) && field[2][2] == 0)
		{
			if (turn == 2)
			{
				field[2][2] = 2;
				turn = 1;
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



// ход пк
void  pcTurn(sf::RenderWindow & window, int turnCounter)
{
	if (turnCounter == 0)
	{
		field[1][1] = 1;
		turn = 2;
	}
	else if (turnCounter == 2)
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
				std::cout << "1541543145" << std::endl;
			}
			else
			{
				field[0][2] = 1;
				turn = 2;
			}
		}
	}
	else if (turnCounter == 4)
	{
		
		if (field[0][2] == 1 && field[1][1] == 1 && field[2][0] == 0)
		{
			field[2][0] = 1;
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
	else if (turnCounter == 6)
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
	else if (turnCounter == 8)
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
}


int main()
{


	//okno
	sf::RenderWindow window(sf::VideoMode(640, 640), "Dota 3");

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

		drawField(rectangle, window);
		drawxo(window);
		if (checkWin(window) == 0)
		{
			pcTurn(window, turnCounter);
			isMouseOnCell(window, turn);
			checkWin(window);
		}
		window.display();
	}
	return 0;
}