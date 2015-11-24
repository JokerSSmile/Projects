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
	float speed = 0.1;
public:
	enum
	{
		leftUp, leftDown, rightUp, rightDown, left, up, down, right, stay
	} dir;
	float damage = 1;

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
	}

	void setFrame(float time)
	{
		CurrentFrame += 0.005 * time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
	}

	//player Control
	void Control(float time, float gameTime, float &lastShot)
	{
		//move
		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = leftUp;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 60, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = leftDown;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 60, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = rightUp;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 34, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = rightDown;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 34, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = left;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 60, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = right;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 34, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = up;
			setFrame(time);
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 0, 36, 26));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = down;
			setFrame(time);
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
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			Shoot(gameTime, lastShot, 5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			Shoot(gameTime, lastShot, 6);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			Shoot(gameTime, lastShot, 7);
		}
	}
	
	//player shoots
	void Shoot(float gameTime, float &lastShootPlayer, int dir)
	{
		for (int i = 0; i <= SIZE_BULLETS; i++)
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
				bullets[i].damage = damage;
				lastShootPlayer = bullets[i].timeShot;
				break;
			}
		}
	}
	
	void SetLastNotCollidedPosition()
	{
		if (dx > 0)
		{
			x = playerOldPosition.x - 1;
		}
		else if (dx < 0)
		{
			x = playerOldPosition.x + 1;
		}
		if (dy > 0)
		{
			y = playerOldPosition.y - 1;
		}
		else if (dy < 0)
		{
			y = playerOldPosition.y + 1;
		}
	}

	void CheckCollision(bool &canMove, Sprite& wallSprite, View& view)
	{
		for (int i = 0; i < SIZE_MAP_STRUCT; i++)
		{
			if (Collision::PixelPerfectTest(sprite, mapStruct[i].sprite))
				{
					//if collides with rock
					if (mapStruct[i].pos == NOTDOOR)
					{
						canMove = false;
						SetLastNotCollidedPosition();
						break;
					}

					//if collides with door
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
				SetLastNotCollidedPosition();
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

	void setSpeed()
	{
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
	}

	void Update(float time, float gameTime, float &lastShootPlayer, Sprite & wallSprite, View & view)
	{
		bool canMove = true;
		
		Control(time, gameTime, lastShootPlayer);
		CheckCollision(canMove, wallSprite, view);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			canMove = true;
		}



		if (canMove == true)
		{
			setSpeed();
			x += dx * time;
			y += dy * time;
		}


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