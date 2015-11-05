#include <SFML/Graphics.hpp>


const int SIZE_BULLETS = 50;


struct
{
private:

	float dy;
	float dx;
public:
	int h = 32;
	int w = 32;
	int direction;
	float x = 0;
	float y = 0;
	bool life = false;
	float timeShot;
	Sprite bulletSprite;
	bool isPlayers = false;
	float speed;

	void checkCollision()
	{
		if (life == true)
		{
			for (int i = (y + h*1.5) / TILE_SIDE; i < (y + h * 1.5) / TILE_SIDE; i++)
				for (int j = (x / TILE_SIDE); j < (x + w) / TILE_SIDE; j++)
				{
					if (tileMap[i][j] == '0' || tileMap[i][j] == 's')
					{
						life = false;
						
					}
				}
		}
	}

	void deleteBullet(float gameTime)
	{
		if (life == true)
		{
			if (gameTime > timeShot + 1)
			{
				isPlayers = false;
				life = false;
				x = 0;
				y = 0;
			}

		}
	}


	void update(float time, RenderWindow & window, float gameTime)
	{

		Texture bulletTexture;
		bulletTexture.loadFromFile("images/bullet.png");
		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setTextureRect(IntRect(128, 32, 32, 32));
		

		switch (direction)
		{
			case 0: dx = -speed*0.66; dy = -speed*0.66; break;
			case 1: dx = -speed*0.66; dy = speed*0.66; break;
			case 2: dx = speed*0.66; dy = -speed*0.66; break;
			case 3: dx = speed*0.66; dy = speed*0.66; break;
			case 4: dx = -speed; dy = 0; break;
			case 5: dx = 0; dy = -speed; break;
			case 6: dx = 0; dy = speed; break;
			case 7: dx = speed; dy = 0; break;
			case 8: dx = 0; dy = speed; break;
		}

		

		x += dx * time;
		y += dy * time;

		bulletSprite.setPosition(x, y);

		deleteBullet(gameTime);
		checkCollision();

		cout << isPlayers << endl;


		if (life == true)
		{
			window.draw(bulletSprite);
		}


	}

}bullets[SIZE_BULLETS];