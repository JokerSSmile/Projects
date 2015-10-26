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

int mouseX = 0;
int mouseY = 0;

bool isMousePressed = false;

//zadaem zoom
void setZoom(Sprite & imageSprite, RenderWindow & window)
{
	if (window.hasFocus())
	{
		//+- scale
		if (Keyboard::isKeyPressed(Keyboard::Up) && isMousePressed == false)
		{
			isMousePressed = true;
			zoomCount += 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && isMousePressed == false)
		{
			isMousePressed = true;
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
int setImgScale(Sprite & sprite, RenderWindow & window, Vector2u & windowSize, View & view)
{
	//img size
	FloatRect imageSize = sprite.getLocalBounds();

	//centriruem kartinku
	sprite.setOrigin(imageSize.width / 2, imageSize.height / 2);
	sprite.setPosition(Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	

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

	//proverka razmera
	if (imageSize.height * imageSize.width < 6250000)
	{
		return 1;
	}
}

//pokazivaem kartinku/soobshenie ob oshibke
void showImg(Texture & imageTexture, char *fileName, RenderWindow & window, char *dirName)
{
	//window size
	Vector2u windowSize = window.getSize();

	//kamera
	View view(FloatRect(0.f, 0.f, windowSize.x, windowSize.y));

	//polniy put' is kornya k failu
	char neededDirName[30] = {};

	//put' v papku
	strncpy(neededDirName, dirName, strcspn(dirName, "*"));
	//put' k failu
	strcat(neededDirName, fileName);

	//razmer
	Vector2u imgSize = imageTexture.getSize();

	
	if (!imageTexture.loadFromFile(neededDirName))
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
	}

	//delaem sprite
	imageTexture.loadFromFile(neededDirName);
	Sprite imageSprite;
	imageSprite.setTexture(imageTexture);

	//scale
	setImgScale(imageSprite, window, windowSize, view);
	setZoom(imageSprite, window);



	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (mouseX == 0 && mouseY == 0)
		{
			mouseX = Mouse::getPosition(window).x;
			mouseY = Mouse::getPosition(window).y;
		}
	}


	if (Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2i mousePos = Mouse::getPosition(window);
		//cout << mouseX << "____" << mousePos.x << endl;
		imageSprite.setPosition(windowSize.x/2 + (mouseX - mousePos.x), windowSize.y/2 + (mouseY - mousePos.y));
		window.draw(imageSprite);
	}















	//vivod
	if (setImgScale(imageSprite, window, windowSize, view) == 1)
	{
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

//
void workWithFiles(char imagesInDirectory[50][30], char *directoryPath, RenderWindow & window, int imageCount)
{
	//vivod tekushei kartinki
	Texture imageTexture;

	//polniy put' is kornya k failu
	char neededDirName[30] = {};

	//put' v papku
	strncpy(neededDirName, directoryPath, strcspn(directoryPath, "*"));

	//put' k failu
	strcat(neededDirName, imagesInDirectory[counter]);

	if (window.hasFocus())
	{
		//menyaem kartinki
		if (Keyboard::isKeyPressed(Keyboard::Right) && isMousePressed == false)
		{
			counter++;
			zoomCount = 1;
			isMousePressed = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && isMousePressed == false)
		{
			counter--;
			zoomCount = 1;
			isMousePressed = true;
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

	showImg(imageTexture, imagesInDirectory[counter], window, directoryPath);

	//zagolovok
	window.setTitle(imagesInDirectory[counter]);
}

int main()
{
	bool isMoved = false;

	RenderWindow window(VideoMode(winW, winH), "");

	//zadannii put'
	char directoryPath[20] = ("C:\\img\\*");

	//vse chto v puti
	char filesInDirectory[50][30] = {};

	//tol'ko izobrazheniya v puti
	char imagesInDirectory[50][30] = {};

	//kol-vo img
	int imageCount = 0;

	HANDLE handle;
	WIN32_FIND_DATA findData;

	handle = FindFirstFile(directoryPath, &findData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		cout << "Error" << endl;
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
				
			}
		}

		window.clear(Color(200, 200, 200));

		workWithFiles(imagesInDirectory, directoryPath, window, imageCount);

		//proverka na nazhatie klavish
		if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
			isMousePressed = false;

		if (!Mouse::isButtonPressed(Mouse::Left))
		{
			mouseX = 0;
			mouseY = 0;
		}

		window.display();
	}
	return 0;
}