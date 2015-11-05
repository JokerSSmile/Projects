#include <SFML/Graphics.hpp>
#include <string>
#include <ostream>

using namespace sf;
using namespace std;

struct Enemy:
	public Character
{
private:
	float moveTimer = 0;
	float currentFrame = 0;
	int randNum;
public:
	float lastShootEnemyStand = 0;
	Enemy() {};
	Enemy(Image & image, float X, float Y, int W, int H, String Name, float Health) :Character(image, X, Y, w, h, Name, health)
	{
		w = W;
		h = H;
		x = X;
		y = Y;
		health = Health;
		if (name == "EnemyFly")
		{
			dx = -0.1;
		}
		if (name == "StandAndShoot")
		{
			
		}
	}

	void checkCollosionFly()//ф-ция взаимодействия с картой
	{
		for (int i = y / TILE_SIDE; i < (y + h) / TILE_SIDE; i++)
			for (int j = x / TILE_SIDE; j < (x + w) / TILE_SIDE; j++)
			{
				if (tileMap[i][j] == '0' || tileMap[i][j] == 's')
				{
					if (dx > 0)//right
					{
						x = j * TILE_SIDE - w;
						//dx = -0.1;
					}
					else if (dx < 0)//left
					{
						x = j * TILE_SIDE + TILE_SIDE;
						//dx = 0.1;
					}
					else if (dy > 0)
					{
						y = i * TILE_SIDE;
						//dy = -0.1;
					}
					else if (dy < 0)
					{
						y = i * TILE_SIDE;
						//dy = 0.1;
					}
					dy = -dy;
					dx = -dx;
				}
			}
	}

	void shoot(float gameTime, int dir)
	{
		for (int i = 0; i <= size(bullets); i++)
		{
			if (bullets[i].life == false && (gameTime > (lastShootEnemyStand + 2)))
			{
				bullets[i].isPlayers = false;
				bullets[i].life = true;
				bullets[i].x = x + w / 2 - 16;
				bullets[i].y = y + 16;
				bullets[i].timeShot = gameTime;
				bullets[i].direction = dir;
				bullets[i].speed = 0.2;
				lastShootEnemyStand = bullets[i].timeShot;
				cout << bullets[i].bulletSprite.getPosition().x << endl;
				break;
			}
		}
	}


	void update(float time, float gameTime, RenderWindow & window)
	{
		if (name == "EnemyFly")
		{
			currentFrame += 0.005 * time;
			if (currentFrame > 2) currentFrame -= 2;
			sprite.setTextureRect(IntRect(57 * int(currentFrame), 0, 57, 45));
			checkCollosionFly();
		}

		else if (name == "StandAndShoot")
		{
			shoot(gameTime, 4);
			sprite.setScale(2, 2);
			if (lastShootEnemyStand + 0.3 <= gameTime)
			{
				sprite.setTextureRect(IntRect(0, 0, 38, 43));
			}
			else
			{
				sprite.setTextureRect(IntRect(38, 0, 38, 43));
			}
		}
		
		x += dx * time;
		y += dy * time;


		sprite.setPosition(x, y);
	}
	
}enemies[10];
