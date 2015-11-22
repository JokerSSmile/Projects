#pragma once
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
	Vector2f playerOldPosition = {x, y};
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
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		cout << playerOldPosition.x << endl;
	}

	//player Control
	void Control(float time, float gameTime, float &lastShot)
	{
		//move
		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = leftUp;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 60, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = leftDown;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 60, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = rightUp;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 34, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = rightDown;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 34, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = left;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 60, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = right;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 34, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = up;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 0, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = down;
			speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 0, 36, 26));
		}
		else
		{
			dir = stay;
			sprite.setTextureRect(IntRect(0, 0, 36, 26));
		}

		//Shoot
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			Shoot(gameTime, lastShot, 4);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			Shoot(gameTime, lastShot, 5);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			Shoot(gameTime, lastShot, 6);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			Shoot(gameTime, lastShot, 7);
		}
	}
	
	//player shoot
	void Shoot(float gameTime, float &lastShootPlayer, int dir)
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
	
	
	void CheckCollision(bool &canMove, Sprite & wallSprite, View & view)
	{
		for (int i = 0; i < size(mapStruct); i++)
		{
			if (mapStruct[i].x != 1 && Collision::PixelPerfectTest(sprite, mapStruct[i].sprite))
				{
					if (mapStruct[i].pos == NOTDOOR)
					{
						canMove = false;
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
							x--;
						}
						if (dx < 0)//left
						{
							x++;
						}
						//canMove = false;
						//break;
					}
					else if (mapStruct[i].pos == RIGHT)
					{
						view.setCenter(view.getCenter().x + WINDOW_WIDTH, view.getCenter().y);
						x += TILE_SIDE * 4 + w;
						break;
					}
					else if (mapStruct[i].pos == LEFT)
					{
						view.setCenter(view.getCenter().x - WINDOW_WIDTH, view.getCenter().y);
						x -= TILE_SIDE * 4 + w;
						break;
					}
					else if (mapStruct[i].pos == UP)
					{
						view.setCenter(view.getCenter().x, view.getCenter().y - WINDOW_HEIGHT);
						y -= TILE_SIDE * 4 + h ;
						break;
					}
					else if (mapStruct[i].pos == DOWN)
					{
						view.setCenter(view.getCenter().x, view.getCenter().y + WINDOW_HEIGHT);
						y += TILE_SIDE * 4 + h;
						break;
					}				
				}
			else if (Collision::PixelPerfectTest(sprite, wallSprite))
			{
				canMove = false;
				break;
			}
			else
			{
				playerOldPosition.x = x;
				playerOldPosition.y = y;
				canMove = true;
			}
		}
	}
	
	//player update
	void Update(float time, float gameTime, float &lastShootPlayer, Sprite & wallSprite, View & view)
	{
		bool canMove = true;
		
		Control(time, gameTime, lastShootPlayer);

		//CheckCollision(canMove, wallSprite, view);

		cout << size(mapStruct) << endl;

		CheckCollision(canMove, wallSprite, view);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			canMove = true;
		}

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
		case stay: dx = 0; dy = 0;
		}

		//cout << canMove << endl;
		if (canMove == true)
		{
			x += dx * time;
			y += dy * time;
		}
		else
		{
			x = playerOldPosition.x;
			y = playerOldPosition.y;
			canMove = true;
		}

		speed = 0;
		sprite.setPosition(x, y);
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