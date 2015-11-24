#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;


sf::String mapString[WIDTH_MAP] = {
	"000000000000000000000000000000000000000000000",
	"000000000000000000000000000000000000000000000",
	"00           0000           0000           00",
	"00     sss   0000           0000 ss     ss 00",
	"00           r00l           r00l           00",
	"00           0000           0000 s       s 00",
	"00           0000           0000 s       s 00",
	"00           0000           0000           00",
	"0000000d00000000000000d00000000000000d0000000",
	"000000000000000000000000000000000000000000000",
	"000000000000000000000000000000000000000000000",
	"0000000u00000000000000u00000000000000u0000000",
	"00           0000           0000           00",
	"00   s       0000  s     s  0000           00",
	"00           r00l           r00l           00",
	"00           0000           0000     sss   00",
	"00           0000  s     s  0000           00",
	"00           0000           0000           00",
	"000000000000000000000000000000000000000000000",
	"000000000000000000000000000000000000000000000",
};




enum DoorPosition
{
	NOTDOOR, UP, DOWN, LEFT, RIGHT
};

struct 
{
	int x;
	int y;
	Sprite sprite;
	DoorPosition pos;
	String TileMap;
}mapStruct[SIZE_MAP_STRUCT];

struct tileMap
{
private:
	bool isMapSpritesLoaded = false;
public:
	Image rockImage;
	Texture rockTexture;
	Sprite rockSprite;
	Image doorImage;
	Texture doorTexture;
	Sprite doorSprite;

	void LoadMapSprites()
	{
		//rock
		rockImage.loadFromFile("images/Rock1.png");
		rockTexture.loadFromImage(rockImage);
		rockSprite.setTexture(rockTexture);

		//door
		doorImage.loadFromFile("images/Door.png");
		doorTexture.loadFromImage(doorImage);
		doorSprite.setTexture(doorTexture);
		doorSprite.setScale(2, 2);
	}

	void drawMap(RenderWindow & window)
	{
		if (isMapSpritesLoaded == false)
		{
			LoadMapSprites();
			isMapSpritesLoaded = true;
		}

		int counter = 0;

		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (mapString[i][j] == 's')
				{
					mapStruct[counter].y = i * TILE_SIDE;
					mapStruct[counter].x = j * TILE_SIDE;
					mapStruct[counter].sprite = rockSprite;
					counter++;
				}
				else if (mapString[i][j] == 'u')
				{
					mapStruct[counter].y = i * TILE_SIDE - TILE_SIDE;
					mapStruct[counter].x = j * TILE_SIDE;
					mapStruct[counter].sprite = doorSprite;
					mapStruct[counter].pos = UP;
					counter++;
				}
				else if (mapString[i][j] == 'd')
				{
					mapStruct[counter].y = i * TILE_SIDE;
					mapStruct[counter].x = j * TILE_SIDE;
					mapStruct[counter].sprite = doorSprite;
					mapStruct[counter].pos = DOWN;
					counter++;
				}
				else if (mapString[i][j] == 'r')
				{
					mapStruct[counter].y = i * TILE_SIDE;
					mapStruct[counter].x = j * TILE_SIDE;
					mapStruct[counter].sprite = doorSprite;
					mapStruct[counter].pos = RIGHT;
					counter++;
				}
				else if (mapString[i][j] == 'l')
				{
					mapStruct[counter].y = i * TILE_SIDE;
					mapStruct[counter].x = j * TILE_SIDE - TILE_SIDE;
					mapStruct[counter].sprite = doorSprite;
					mapStruct[counter].pos = LEFT;
					counter++;
				}
			}
		}

		drawTiles(window);
	}

	void drawTiles(RenderWindow & window)
	{
		for (int i = 0; i < SIZE_MAP_STRUCT; i++)
		{
			if (mapStruct[i].pos == 0)
			{
				mapStruct[i].sprite.setPosition(mapStruct[i].x, mapStruct[i].y);
			}
			else
			{
				if (mapStruct[i].pos == UP)
				{
					mapStruct[i].sprite.setTextureRect(IntRect(0, 0, 64, 64));
					mapStruct[i].sprite.setPosition(mapStruct[i].x, mapStruct[i].y);
				}
				else if (mapStruct[i].pos == DOWN)
				{
					mapStruct[i].sprite.setTextureRect(IntRect(64, 0, 64, 64));
					mapStruct[i].sprite.setPosition(mapStruct[i].x, mapStruct[i].y);
				}
				else if (mapStruct[i].pos == LEFT)
				{
					mapStruct[i].sprite.setTextureRect(IntRect(192, 0, 64, 64));
					mapStruct[i].sprite.setPosition(mapStruct[i].x, mapStruct[i].y);
				}
				else if (mapStruct[i].pos == RIGHT)
				{
					mapStruct[i].sprite.setTextureRect(IntRect(128, 0, 64, 64));
					mapStruct[i].sprite.setPosition(mapStruct[i].x, mapStruct[i].y);
				}
			}
			window.draw(mapStruct[i].sprite);
		}
	}
};
