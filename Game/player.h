#include <SFML/Graphics.hpp>
#include "character.h"

using namespace sf;
using namespace std;

struct Character;

struct Player :public Character
{
private:
	//float x, y = 0;
	float CurrentFrame = 0;
public:
	enum
	{
		leftUp, leftDown, rightUp, rightDown, left, up, down, right, stay
	} dir;

	Player(Image & image, float X, float Y, int W, int H, String Name) :Character(image, X, Y, w, h, Name)
	{
		dir = stay;
		w = W;
		h = H;
		x = X;
		y = Y;
		if (name == "Hero")
		{
			sprite.setTextureRect(IntRect(0, 45, w, h));
		}
	}
	void control(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = leftUp;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 168, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = leftDown;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 168, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = rightUp;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 296, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = rightDown;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 296, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dir = left;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 168, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dir = right;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 296, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = up;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 424, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = down;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 40, 56, 96));
		}
	}

	void checkCollosion()//ф-ция взаимодействия с картой
	{
		for (int i = (y+h/1.5) / 64; i < (y + h) / 64; i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 64; j < (x + w/1.25) / 64; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'r')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y--;
					}
					if (dy < 0)//up
					{
						y++;
					}
					if (dx > 0)//right
					{
						x--;
					}
					if (dx < 0)//left
					{
						x++;
					}
				}
			}
	}


	void update(float time)
	{
		control(time);
		switch (dir)
		{
		case right: dx = speed; dy = 0; break;
		case left: dx = -speed; dy = 0; break;
		case down: dx = 0; dy = speed; break;
		case up: dx = 0; dy = -speed; break;
		case leftUp: dx = -speed*0.66; dy = -speed*0.66; break;
		case leftDown: dx = -speed*0.66; dy = speed*0.66; break;
		case rightUp: dx = speed*0.66; dy = -speed*0.66; break;
		case rightDown: dx = speed*0.66; dy = speed*0.66; break;
		}

		x += dx * time;
		y += dy * time;


		speed = 0;
		sprite.setPosition(x, y);

		checkCollosion();//вызываем функцию, отвечающую за взаимодействие с картой
	}

	float getPlayerCoordinateX()
	{
		return x;
	}
	float getPlayerCoordinateY()
	{
		return y;
	}
};
