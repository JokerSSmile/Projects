#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace sf;

//window
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const char EXPANSIONS[4][6] = { "jpeg", "jpg", "png", "bmp" };

Texture imageTexture;

void ErrorNoImagesInDir(RenderWindow & window)
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

void ErrorNoDirExists(RenderWindow & window)
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

void IfNext(bool& isLoaded, bool& isButtonPressed, int& zoomCount)
{
	zoomCount = 1;
	isButtonPressed = true;
	isLoaded = false;
}

int CheckButtons(Sprite & plus, Sprite & minus, Sprite & left, Sprite & right, RenderWindow & window, bool& isLoaded, int& counter, bool& isButtonPressed, int& zoomCount)
{
	if (Mouse::isButtonPressed(Mouse::Left) && isButtonPressed == false)
	{
		if (right.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			counter++;
			IfNext(isLoaded, isButtonPressed, zoomCount);
		}
		else if (left.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			counter--;
			IfNext(isLoaded, isButtonPressed, zoomCount);
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

void DrawButtons(RenderWindow & window, bool& isLoaded, int& counter, bool& isButtonPressed, int& zoomCount)
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

	left.setTexture(buttonLeaf);
	left.setRotation(180);
	right.setTexture(buttonLeaf);
	plus.setTexture(zoomPlus);
	minus.setTexture(zoomMinus);

	FloatRect imageSize = plus.getLocalBounds();

	Vector2u windowSize = window.getSize();

	plus.setOrigin(imageSize.width / 2, imageSize.height / 2);
	minus.setOrigin(imageSize.width / 2, imageSize.height / 2);
	left.setOrigin(imageSize.width / 2, imageSize.height / 2);
	right.setOrigin(imageSize.width / 2, imageSize.height / 2);

	left.setPosition(40, windowSize.y / 2);
	right.setPosition(windowSize.x - 40, windowSize.y / 2);
	plus.setPosition(windowSize.x / 2 - 30, windowSize.y - 40);
	minus.setPosition(windowSize.x / 2 + 30, windowSize.y - 40);

	CheckButtons(plus, minus, left, right, window, isLoaded, counter, isButtonPressed, zoomCount);

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

void SetZoom(Sprite & imageSprite, RenderWindow & window, bool& isButtonPressed, int& zoomCount)
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

	//set scale
	if (zoomCount > 7)
	{
		zoomCount = 7;
	}
	else if (zoomCount < 1)
	{
		zoomCount = 1;
	}

	imageSprite.setScale(zoomCount, zoomCount);
}

void SetImgScale(Sprite & sprite, RenderWindow & window, Vector2u & windowSize, View & view, int& zoomCount)
{
	//img size
	FloatRect imageSize = sprite.getLocalBounds();
	sprite.setOrigin(imageSize.width / 2, imageSize.height / 2);

	//scale of img
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

	window.setView(view);

	sprite.setPosition(window.getSize().x/2, window.getSize().y/2);
}

void ErrorCantLoadImg(RenderWindow& window, View& view, bool& isError)
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

void DrawImg(char *fileName, RenderWindow & window, char *dirName, bool& isLoaded, bool& isButtonPressed, int& zoomCount)
{
	bool isError = false;
	Vector2u windowSize = window.getSize();

	View view(FloatRect(0.f, 0.f, windowSize.x, windowSize.y));

	//full path
	char neededDirName[150] = {};

	//path to dir
	strncpy(neededDirName, dirName, strcspn(dirName, "*"));
	strcat(neededDirName, fileName);

	Vector2u imgSize = imageTexture.getSize();

	if (isLoaded == false)
	{
		if (imageTexture.loadFromFile(neededDirName))
		{
			isLoaded = true;
		}
		else
		{
			ErrorCantLoadImg(window, view, isError);
		}
	}

	if (!isError)
	{
		Sprite imageSprite;
		imageSprite.setTexture(imageTexture);
		imageSprite.setOrigin(window.getSize().x/2, window.getSize().y/2);

		SetZoom(imageSprite, window, isButtonPressed, zoomCount);
		SetImgScale(imageSprite, window, windowSize, view, zoomCount);
		window.draw(imageSprite);
	}
}

bool GetExpansions(char *fileName)
{
	for (int i = 0; i < size(EXPANSIONS); i++)
	{
		if (strchr(fileName, '.') != 0 && strcmp(strchr(fileName, '.') + 1, EXPANSIONS[i]) == 0 && strlen(fileName) > 2)
		{
			return 1;
		}
	}
	return 0;
}

void WorkWithFiles(char imagesInDirectory[100][50], char* directoryPath, int imageCount, bool& isLoaded, int& counter, bool& isButtonPressed, int& zoomCount)
{
	//path to file from drive
	char neededDirName[150] = {};

	//path to dir
	strncpy(neededDirName, directoryPath, strcspn(directoryPath, "*"));

	//path to file
	strcat(neededDirName, imagesInDirectory[counter]);

	//change img
	if (Keyboard::isKeyPressed(Keyboard::Right) && isButtonPressed == false)
	{
		counter++;
		IfNext(isLoaded, isButtonPressed, zoomCount);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && isButtonPressed == false)
	{
		counter--;
		IfNext(isLoaded, isButtonPressed, zoomCount);
	}

	if (counter >= imageCount)
	{
		counter = 0;
	}
	else if (counter < 0)
	{
		counter = imageCount - 1;
	}
}

void StartInput(char directoryPath[100])
{
	cout << "Input directory" << endl;
	cout << "Correct input is: C:\\images\\*" << endl;
	cout << "------------------------------" << endl;
	cin >> directoryPath;
}

void GetFiles(char directoryPath[100], bool& isCorrectDir, char imagesInDirectory[100][50], int& imageCount)
{
	//vse chto v puti
	char filesInDirectory[100][50] = {};

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
			if (strlen(filesInDirectory[k]) > 2 && GetExpansions(filesInDirectory[k]))
			{
				strcpy(imagesInDirectory[j], filesInDirectory[k]);
				j++;
			}
			imageCount = j;
		}
	}
	FindClose(handle);
}

void CheckButtonPressed(bool& isButtonPressed)
{
	if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Mouse::isButtonPressed(Mouse::Left))
		isButtonPressed = false;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isButtonPressed = true;
	}
}

void ProcessEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

int main()
{
	float dX = 0;
	float dY = 0;
	int counter = 0;
	int zoomCount = 1;
	int imageCount = 0;
	bool isLoaded = false;
	bool isCorrectDir = true;
	bool isButtonPressed = false;
	char directoryPath[100] = {};
	char imagesInDirectory[100][50] = {};

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");
	StartInput(directoryPath);
	GetFiles(directoryPath, isCorrectDir, imagesInDirectory, imageCount);

	while (window.isOpen())
	{
		ProcessEvents(window);

		window.clear(Color(200, 200, 200));

		if (imageCount > 0 && isCorrectDir == true)
		{
			WorkWithFiles(imagesInDirectory, directoryPath, imageCount, isLoaded, counter, isButtonPressed, zoomCount);
			DrawImg(imagesInDirectory[counter], window, directoryPath, isLoaded, isButtonPressed, zoomCount);
			DrawButtons(window, isLoaded, counter, isButtonPressed, zoomCount);
			window.setTitle(imagesInDirectory[counter]);
			CheckButtonPressed(isButtonPressed);
		}
		else if (imageCount == 0 && isCorrectDir == true)
		{
			ErrorNoImagesInDir(window);
		}
		else if (isCorrectDir == false)
		{
			ErrorNoDirExists(window);
		}
		
		window.display();
	}
	return 0;
}