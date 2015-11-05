#include <SFML/Graphics.hpp>
#include "character.h"
#include "bullet.h"


using namespace sf;
using namespace std;

struct Character;

struct Player:
	public Character
{
private:
	float CurrentFrame = 0;
public:
	enum
	{
		leftUp, leftDown, rightUp, rightDown, left, up, down, right, stay
	} dir;

	Player(Image & image, float X, float Y, int W, int H, String Name, float Health) :Character(image, X, Y, w, h, Name, health)
	{
		dir = stay;
		w = W;
		h = H;
		x = X;
		y = Y;
		health = 6;
		if (name == "Hero")
		{
			sprite.setTextureRect(IntRect(0, 45, w, h));
		}
	}

	//player control
	void control(float time, float gameTime, float &lastShot)
	{
		//move
		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = leftUp;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 168, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = leftDown;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 168, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = rightUp;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 296, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = rightDown;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 296, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = left;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 168, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = right;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 296, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = up;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 424, 56, 96));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = down;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 40, 56, 96));
		}
		//shoot
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			shoot(gameTime, lastShot, 4);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			shoot(gameTime, lastShot, 5);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			shoot(gameTime, lastShot, 6);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			shoot(gameTime, lastShot, 7);
		}

		//else
		//{
		//	dir = stay;
		//	sprite.setTextureRect(IntRect(0, 40, 56, 96));
		//}
	}

	//collisions
	void checkCollosion()//ф-ция взаимодействия с картой
	{
		for (int i = (y + h / 1.5) / TILE_SIDE; i < (y + h) / TILE_SIDE; i++)
			for (int j = (x / TILE_SIDE); j < (x + w) / TILE_SIDE; j++)
			{
				if (tileMap[i][j] == '0' || tileMap[i][j] == 's')
				{
					if (dy > 0)//вниз
					{
						y--;
					}
					if (dy < 0)//up
					{
						y++;
					}
					if (dx > 0)//right
					{
						//x = j * TILE_SIDE - w;
						x--;
					}
					if (dx < 0)//left
					{
						x++;
					}
				}
				else if (tileMap[i][j] == 'd' && dy > 0)
				{
					view.setCenter(view.getCenter().x, view.getCenter().y + WINDOW_HEIGHT);
					y = y + TILE_SIDE * 4 + h / 2;
				}
				else if (tileMap[i][j] == 'u' && dy < 0)
				{
					view.setCenter(view.getCenter().x, view.getCenter().y - WINDOW_HEIGHT);
					y = y - TILE_SIDE * 4 - h / 2;
				}
				else if (tileMap[i][j] == 'l' && dx < 0)
				{
					view.setCenter(view.getCenter().x - WINDOW_WIDTH, view.getCenter().y);
					x = x - TILE_SIDE * 4 - w - 5;
				}
				else if (tileMap[i][j] == 'r' && dx > 0)
				{
					view.setCenter(view.getCenter().x + WINDOW_WIDTH, view.getCenter().y);
					x = x + TILE_SIDE * 4 + w + 5;
				}
			}
		
	}

	//player shoot
	void shoot(float gameTime, float &lastShootPlayer, int dir)
	{
		for (int i = 0; i <= size(bullets); i++)
		{
			if (bullets[i].life == false && (gameTime > (lastShootPlayer + 0.5)))
			{
				bullets[i].isPlayers = true;
				bullets[i].life = true;
				bullets[i].x = x + w/2 - 16;
				bullets[i].y = y + 16;
				bullets[i].timeShot = gameTime;
				bullets[i].direction = dir;
				bullets[i].speed = 0.3;
				lastShootPlayer = bullets[i].timeShot;
				break;
			}
		}
	}

	//player update
	void update(float time, float gameTime, float &lastShootPlayer)
	{

		control(time, gameTime, lastShootPlayer);
		 
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
		//case stay: dx = 0; dy = 0;
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