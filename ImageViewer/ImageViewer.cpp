#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace sf;

//window
const int winW = 800;
const int winH = 600;

//#kartinki
int counter = 0;
//#zooma
int zoomCount = 1;

//mouse
float posX = 0;
float posY = 0;
float mouseX = 0;
float mouseY = 0;
float dx = 0;
float dy = 0;


float spritex = 0;
float spritey = 0;



bool isButtonPressed = false;
bool isLoaded = false;
bool isMoved = false;

Texture imageTexture;



void errorNoImagesInDir(RenderWindow & window)
{
	Vector2u windowSize = window.getSize();

	window.clear(Color(200, 200, 200));
	Text text;
	Font font;
	font.loadFromFile("font/times.ttf");
	text.setString("No images in given directory");
	text.setFont(font);
	text.setColor(Color::Black);
	text.setCharacterSize(20);

	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(window.getSize().x/2, window.getSize().y/2);

	window.draw(text);
}

void errorNoDirExists(RenderWindow & window)
{
	Vector2u windowSize = window.getSize();

	window.clear(Color(200, 200, 200));
	Text text;
	Font font;
	font.loadFromFile("font/times.ttf");
	text.setString("Given directory is not exist");
	text.setFont(font);
	text.setColor(Color::Black);
	text.setCharacterSize(20);

	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	window.draw(text);
}

//proverka na vzaimodeistvie s knopkami
int checkButtons(Sprite & plus, Sprite & minus, Sprite & left, Sprite & right, RenderWindow & window)
{
	if (Mouse::isButtonPressed(Mouse::Left) && isButtonPressed == false)
	{
		if (right.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			counter++;
			zoomCount = 1;
			isButtonPressed = true;
			isLoaded = false;
		}
		else if (left.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			counter--;
			zoomCount = 1;
			isButtonPressed = true;
			isLoaded = false;
		}
		else if (plus.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			zoomCount++;
			isButtonPressed = true;
		}
		else if (minus.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			zoomCount--;
			isButtonPressed = true;
		}
	}
	return 0;
}

//otrisovka knopok
void drawButtons(RenderWindow & window)
{
	//sprite
	Texture buttonLeaf;
	Texture zoomPlus;
	Texture zoomMinus;
	buttonLeaf.loadFromFile("images/leaf.png");
	zoomPlus.loadFromFile("images/plus.png");
	zoomMinus.loadFromFile("images/minus.png");
	Sprite left;
	Sprite right;
	Sprite plus;
	Sprite minus;

	//set texture
	left.setTexture(buttonLeaf);
	left.setRotation(180);
	right.setTexture(buttonLeaf);
	plus.setTexture(zoomPlus);
	minus.setTexture(zoomMinus);

	//razmer
	FloatRect imageSize = plus.getLocalBounds();

	//window size
	Vector2u windowSize = window.getSize();

	//centr kartinki - 0 koordinata
	plus.setOrigin(imageSize.width / 2, imageSize.height / 2);
	minus.setOrigin(imageSize.width / 2, imageSize.height / 2);
	left.setOrigin(imageSize.width / 2, imageSize.height / 2);
	right.setOrigin(imageSize.width / 2, imageSize.height / 2);

	//position
	left.setPosition(40, windowSize.y / 2);
	right.setPosition(windowSize.x - 40, windowSize.y / 2);
	plus.setPosition(windowSize.x / 2 - 30, windowSize.y - 40);
	minus.setPosition(windowSize.x / 2 + 30, windowSize.y - 40);

	checkButtons(plus, minus, left, right, window);

	//draw
	if (zoomCount < 7)
	{
		window.draw(plus);
	}
	if (zoomCount > 1)
	{
		window.draw(minus);
	}
	window.draw(right);
	window.draw(left);
}


//zadaem zoom
void setZoom(Sprite & imageSprite, RenderWindow & window)
{
	if (window.hasFocus())
	{
		//+- scale
		if (Keyboard::isKeyPressed(Keyboard::Up) && isButtonPressed == false)
		{
			isButtonPressed = true;
			zoomCount += 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && isButtonPressed == false)
		{
			isButtonPressed = true;
			zoomCount -= 1;
		}
	}

	//granici scale'a
	if (zoomCount > 7)
		zoomCount = 7;
	else if (zoomCount < 1)
		zoomCount = 1;

	//zadaem scale
	imageSprite.setScale(zoomCount, zoomCount);
}

//scale pri izmenenii okna ili esli kartinka bol'she okna
void setImgScale(Sprite & sprite, RenderWindow & window, Vector2u & windowSize, View & view)
{
	//img size
	FloatRect imageSize = sprite.getLocalBounds();

	//centriruem kartinku
	sprite.setOrigin(imageSize.width / 2, imageSize.height / 2);

	//scale kartinki
	if (imageSize.height > windowSize.y || imageSize.width > windowSize.x)
	{
		if ((windowSize.y) / (imageSize.height) < (windowSize.x) / (imageSize.width))
		{
			sprite.setScale((windowSize.y) / (imageSize.height) * zoomCount, (windowSize.y) / (imageSize.height) * zoomCount);
		}
		else
		{
			sprite.setScale((windowSize.x) / (imageSize.width) * zoomCount, (windowSize.x) / (imageSize.width) * zoomCount);
		}
	}

	//kamera
	window.setView(view);

	/*
	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		mouseX = Mouse::getPosition(window).x;
		mouseY = Mouse::getPosition(window).y;
	}


	Vector2i mousePos = Mouse::getPosition(window);





	if (Mouse::isButtonPressed(Mouse::Left))
	{

		
		//posX = -(mouseX - mousePos.x) - windowSize.x / 2;
		//posY = -(mouseY - mousePos.y) - windowSize.y / 2;
		

		if (mouseX - mousePos.x != 0 && mouseX - mousePos.x != 0)
		{
			isMoved = true;
			posX = -(mouseX - mousePos.x);
			posY = -(mouseY - mousePos.y);
		}
		isButtonPressed = true;
		//spritex = sprite.getPosition().x + posX;
		//spritey = sprite.getPosition().y + posY;
	}

	dx = (windowSize.x / 2 - sprite.getPosition().x);
	dy = (windowSize.y / 2 - sprite.getPosition().y);

	if (isMoved == false)
	{
		sprite.setPosition(windowSize.x / 2, windowSize.y / 2);
	}
	else
	{

		//sprite.setPosition(posX + dx, posY + dy);

		dx = sprite.getPosition().x;
		dy = sprite.getPosition().y;

	}

	//sprite.setOrigin(sprite.getOrigin().x + spritex, sprite.getOrigin().y + spritey);

	sprite.setPosition(spritex + sprite.getGlobalBounds().width, spritey + sprite.getGlobalBounds().height);
	//spritex += posX;
	//spritey += posY;

	//sprite.setPosition(posX + dx, posY + dy);


	//sprite.move(dx, dy);

	//cout << sprite.getOrigin().x << endl;

	//cout << dx - windowSize.x/2 << endl;
	*/
	sprite.setPosition(window.getSize().x/2, window.getSize().y/2);
}

//pokazivaem kartinku/soobshenie ob oshibke
void showImg(char *fileName, RenderWindow & window, char *dirName, float dX, float dY)
{
	//est' li oshibka
	bool isError = false;

	//window size
	Vector2u windowSize = window.getSize();

	//kamera
	View view(FloatRect(0.f, 0.f, windowSize.x, windowSize.y));

	//polniy put' is kornya k failu
	char neededDirName[150] = {};

	//put' v papku
	strncpy(neededDirName, dirName, strcspn(dirName, "*"));
	//put' k failu
	strcat(neededDirName, fileName);

	//razmer
	Vector2u imgSize = imageTexture.getSize();

	//zagruzka textur
	if (isLoaded == false)
	{
		if (imageTexture.loadFromFile(neededDirName))
		{
			isLoaded = true;
		}
		else
		{
			Vector2u windowSize = window.getSize();

			window.clear(Color(200, 200, 200));
			Text text;
			Font font;
			font.loadFromFile("font/times.ttf");
			text.setString("Can not load the image");
			text.setFont(font);
			text.setColor(Color::Black);
			text.setCharacterSize(20);

			FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.width / 2, textRect.height / 2);
			text.setPosition(view.getCenter().x, view.getCenter().y);

			window.draw(text);
			isError = true;
		}
	}

	if (!isError)
	{
		//delaem sprite
		Sprite imageSprite;
		imageSprite.setTexture(imageTexture);
		imageSprite.setOrigin(window.getSize().x/2, window.getSize().y/2);


		//scale
		setZoom(imageSprite, window);
		setImgScale(imageSprite, window, windowSize, view);

		
	


		window.draw(imageSprite);
	}
}

//proveryaem yavlyaetsya li fail v direktorii kartinkoi
int getExpansions(char *fileName)
{
	char expansions[4][6] = { "jpeg", "jpg", "png", "bmp" };

	//yavlyaetsya li fail kartinkoi
	for (int i = 0; i < size(expansions); i++)
	{
		if (strchr(fileName, '.') != 0 && strcmp(strchr(fileName, '.') + 1, expansions[i]) == 0 && strlen(fileName) > 2)
		{
			return 1;
		}
	}
	return 0;
}

//rabotaem s poluchennoi dir
void workWithFiles(char imagesInDirectory[100][50], char *directoryPath, RenderWindow & window, int imageCount, float dX, float dY)
{
	//vivod tekushei kartinki
	//Texture imageTexture;

	//polniy put' is kornya k failu
	char neededDirName[150] = {};

	//put' v papku
	strncpy(neededDirName, directoryPath, strcspn(directoryPath, "*"));

	//put' k failu
	strcat(neededDirName, imagesInDirectory[counter]);

	if (window.hasFocus())
	{

		//menyaem kartinki
		if (Keyboard::isKeyPressed(Keyboard::Right) && isButtonPressed == false)
		{
			counter++;
			zoomCount = 1;
			isButtonPressed = true;
			isLoaded = false;
			isMoved = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && isButtonPressed == false)
		{
			counter--;
			zoomCount = 1;
			isButtonPressed = true;
			isLoaded = false;
			isMoved = false;
		}
	}

	//perehod v nachalo/konec
	if (counter >= imageCount)
	{
		counter = 0;
	}
	else if (counter < 0)
	{
		counter = imageCount - 1;
	}

	showImg(imagesInDirectory[counter], window, directoryPath, dX, dY);
	drawButtons(window);



	//zagolovok
	window.setTitle(imagesInDirectory[counter]);
}

int main()
{
	float dX = 0;
	float dY = 0;

	bool isCorrectDir = true;

	RenderWindow window(VideoMode(winW, winH), "");

	//zadannii put'
	char directoryPath[100] = {};//("C:\\img\\*");

	//input path
	cout << "Input directory" << endl;
	cout << "Correct input is: C:\\images\\*" << endl;
	cout << "------------------------------" << endl;
	cin >> directoryPath;

	//vse chto v puti
	char filesInDirectory[100][50] = {};

	//tol'ko izobrazheniya v puti
	char imagesInDirectory[100][50] = {};

	//kol-vo img
	int imageCount = 0;

	HANDLE handle;
	WIN32_FIND_DATA findData;

	handle = FindFirstFile(directoryPath, &findData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		isCorrectDir = false;
	}
	else
	{
		short k = 0;

		//nazvaniya failov i dir
		do
		{
			strcpy(filesInDirectory[k], findData.cFileName);
			k++;
		} while (FindNextFile(handle, &findData) != 0);

		//nazvaniya kartinok v dir
		int j = 0;
		for (int k = 0; k < size(filesInDirectory); k++)
		{
			if (strlen(filesInDirectory[k]) > 2 && getExpansions(filesInDirectory[k]))
			{
				strcpy(imagesInDirectory[j], filesInDirectory[k]);
				j++;
			}
			imageCount = j;
		}
	}
	FindClose(handle);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
				if (event.type == Event::MouseMoved)
				{
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						spritex = event.mouseMove.x;
						spritey = event.mouseMove.y;
					}
				}
		}


		window.clear(Color(200, 200, 200));

		if (imageCount > 0 && isCorrectDir == true)
		{
			workWithFiles(imagesInDirectory, directoryPath, window, imageCount, dX, dY);

			//proverka na nazhatie klavish
			if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Mouse::isButtonPressed(Mouse::Left))
				isButtonPressed = false;


			if (Mouse::isButtonPressed(Mouse::Left))
			{
				isButtonPressed = true;
			}
		}
		else if (imageCount == 0 && isCorrectDir == true)
		{
			errorNoImagesInDir(window);
		}
		else if (isCorrectDir == false)
		{
			errorNoDirExists(window);
		}
		
		window.display();
	}
	return 0;
}