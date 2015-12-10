#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

//window
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int MAX_ZOOM = 7;

const Vector2i RIGHT_BUTTON_SPRITE_SHIFT = { 40, 0 };
const Vector2i LEFT_BUTTON_SPRITE_SHIFT = { 40, 0 };
const Vector2i ZOOM_BUTTON_SPRITE_SHIFT = { 30, 40 };

vector<string> EXPANSIONS = { "jpeg", "jpg", "png", "bmp" };

Texture imageTexture;

struct
{
	Font font;
} ErrorFont;

struct
{
	int counter = 0;
	int zoomCount = 1;
	int imageCount = 0;
	bool isLoaded = false;
	bool isCorrectDir = true;
	bool isButtonPressed = false;
	char directoryPath[250] = {};
	char imagesInDirectory[200][150] = {};
} settings;

void ErrorNoImagesInDir(RenderWindow & window)
{
	Vector2u windowSize = window.getSize();

	window.clear(Color(200, 200, 200));
	Text text;
	text.setString("No images in given directory");
	text.setFont(ErrorFont.font);
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
	text.setString("Given directory is not exist");
	text.setFont(ErrorFont.font);
	text.setColor(Color::Black);
	text.setCharacterSize(20);
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	window.draw(text);
}

void ErrorCantLoadImg(RenderWindow& window, View& view, bool& isError)
{
	Vector2u windowSize = window.getSize();
	window.clear(Color(200, 200, 200));
	Text text;
	text.setString("Can not load the image");
	text.setFont(ErrorFont.font);
	text.setColor(Color::Black);
	text.setCharacterSize(20);
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(view.getCenter().x, view.getCenter().y);
	window.draw(text);
	isError = true;
}

void OnNextImage(bool& isLoaded, bool& isButtonPressed, int& zoomCount)
{
	zoomCount = 1;
	isButtonPressed = true;
	isLoaded = false;
}

int CheckButtons(Sprite & plus, Sprite & minus, Sprite & left, Sprite & right, RenderWindow & window, bool& isLoaded, int& counter, bool& isButtonPressed, int& zoomCount)
{
	Vector2f mousePos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };
	if (Mouse::isButtonPressed(Mouse::Left) && isButtonPressed == false)
	{
		if (right.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			counter++;
			OnNextImage(isLoaded, isButtonPressed, zoomCount);
		}
		else if (left.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			counter--;
			OnNextImage(isLoaded, isButtonPressed, zoomCount);
		}
		else if (plus.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			zoomCount++;
			isButtonPressed = true;
		}
		else if (minus.getGlobalBounds().contains(mousePos.x, mousePos.y))
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

	left.setPosition(LEFT_BUTTON_SPRITE_SHIFT.x, windowSize.y / 2);
	right.setPosition(windowSize.x - RIGHT_BUTTON_SPRITE_SHIFT.x, windowSize.y / 2);
	plus.setPosition(windowSize.x / 2 - ZOOM_BUTTON_SPRITE_SHIFT.x, windowSize.y - ZOOM_BUTTON_SPRITE_SHIFT.y);
	minus.setPosition(windowSize.x / 2 + ZOOM_BUTTON_SPRITE_SHIFT.x, windowSize.y - ZOOM_BUTTON_SPRITE_SHIFT.y);

	CheckButtons(plus, minus, left, right, window, settings.isLoaded, settings.counter, settings.isButtonPressed, settings.zoomCount);

	if (settings.zoomCount < MAX_ZOOM)
	{
		window.draw(plus);
	}
	if (settings.zoomCount > 1)
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
		if (Keyboard::isKeyPressed(Keyboard::Up) && settings.isButtonPressed == false)
		{
			settings.isButtonPressed = true;
			settings.zoomCount += 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && settings.isButtonPressed == false)
		{
			settings.isButtonPressed = true;
			settings.zoomCount -= 1;
		}
	}

	//set scale
	if (settings.zoomCount > MAX_ZOOM)
	{
		settings.zoomCount = MAX_ZOOM;
	}
	else if (settings.zoomCount < 1)
	{
		settings.zoomCount = 1;
	}

	imageSprite.setScale(settings.zoomCount, settings.zoomCount);
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
			sprite.setScale((windowSize.y) / (imageSize.height) * settings.zoomCount, (windowSize.y) / (imageSize.height) * settings.zoomCount);
		}
		else
		{
			sprite.setScale((windowSize.x) / (imageSize.width) * settings.zoomCount, (windowSize.x) / (imageSize.width) * settings.zoomCount);
		}
	}

	window.setView(view);

	sprite.setPosition(window.getSize().x/2, window.getSize().y/2);
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

	if (settings.isLoaded == false)
	{
		if (imageTexture.loadFromFile(neededDirName))
		{
			settings.isLoaded = true;
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

		SetZoom(imageSprite, window, settings.isButtonPressed, settings.zoomCount);
		SetImgScale(imageSprite, window, windowSize, view, settings.zoomCount);
		window.draw(imageSprite);
	}
}

bool isCorrectExpansion(char *fileName)
{
	for (vector<string>::iterator exp = EXPANSIONS.begin(); exp != EXPANSIONS.end(); ++exp)
	{
		const char* str = exp->c_str();
		if (strchr(fileName, '.') != 0 && strcmp(strchr(fileName, '.') + 1, str) == 0 && strlen(fileName) > 2)
		{
			return 1;
		}
	}
	return 0;
}

void WorkWithFiles(char imagesInDirectory[200][150], char* directoryPath, int imageCount, bool& isLoaded, int& counter, bool& isButtonPressed, int& zoomCount)
{
	//path to file from drive
	char neededDirName[150] = {};

	//path to dir
	strncpy(neededDirName, directoryPath, strcspn(directoryPath, "*"));

	//path to file
	strcat(neededDirName, imagesInDirectory[settings.counter]);

	//change img
	if (Keyboard::isKeyPressed(Keyboard::Right) && settings.isButtonPressed == false)
	{
		settings.counter++;
		OnNextImage(settings.isLoaded, settings.isButtonPressed, settings.zoomCount);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && settings.isButtonPressed == false)
	{
		settings.counter--;
		OnNextImage(settings.isLoaded, settings.isButtonPressed, settings.zoomCount);
	}

	if (settings.counter >= settings.imageCount)
	{
		settings.counter = 0;
	}
	else if (settings.counter < 0)
	{
		settings.counter = settings.imageCount - 1;
	}
}

void StartInput(char directoryPath[250])
{
	cout << "Input directory" << endl;
	cout << "Correct input is: C:\\images\\*" << endl;
	cout << "------------------------------" << endl;
	cin >> directoryPath;
}

void GetFiles(char directoryPath[2500], bool& isCorrectDir, char imagesInDirectory[200][150], int& imageCount)
{
	char filesInDirectory[100][50] = {};

	HANDLE handle;
	WIN32_FIND_DATA findData;

	handle = FindFirstFile(directoryPath, &findData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		settings.isCorrectDir = false;
	}
	else
	{
		short k = 0;
		do
		{
			strcpy(filesInDirectory[k], findData.cFileName);
			k++;
		} while (FindNextFile(handle, &findData) != 0);

		int j = 0;
		for (int k = 0; k < size(filesInDirectory); k++)
		{
			if (strlen(filesInDirectory[k]) > 2 && isCorrectExpansion(filesInDirectory[k]))
			{
				strcpy(imagesInDirectory[j], filesInDirectory[k]);
				j++;
			}
			settings.imageCount = j;
		}
	}
	FindClose(handle);
}

void CheckButtonPressed(bool& isButtonPressed)
{
	if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Mouse::isButtonPressed(Mouse::Left))
		settings.isButtonPressed = false;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		settings.isButtonPressed = true;
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
	ErrorFont.font.loadFromFile("font/times.ttf");

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");
	StartInput(settings.directoryPath);
	GetFiles(settings.directoryPath, settings.isCorrectDir, settings.imagesInDirectory, settings.imageCount);

	while (window.isOpen())
	{
		ProcessEvents(window);

		window.clear(Color(200, 200, 200));

		if (settings.imageCount > 0 && settings.isCorrectDir == true)
		{
			WorkWithFiles(settings.imagesInDirectory, settings.directoryPath, settings.imageCount, settings.isLoaded, settings.counter, settings.isButtonPressed, settings.zoomCount);
			DrawImg(settings.imagesInDirectory[settings.counter], window, settings.directoryPath, settings.isLoaded, settings.isButtonPressed, settings.zoomCount);
			DrawButtons(window, settings.isLoaded, settings.counter, settings.isButtonPressed, settings.zoomCount);
			window.setTitle(settings.imagesInDirectory[settings.counter]);
			CheckButtonPressed(settings.isButtonPressed);
		}
		else if (settings.imageCount == 0 && settings.isCorrectDir == true)
		{
			ErrorNoImagesInDir(window);
		}
		else if (settings.isCorrectDir == false)
		{
			ErrorNoDirExists(window);
		}
		
		window.display();
	}
	return 0;
}