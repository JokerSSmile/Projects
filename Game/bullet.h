#include <SFML/Graphics.hpp>



struct
{
private:

	float dy;
	float dx;
	float speed = 0.2;
	int h = 32;
	int w = 32;
public:
	int direction;
	float x = 0;
	float y = 0;
	bool life = false;
	float timeShot;
	Sprite bulletSprite;

	void checkCollision()
	{
		for (int k = 0; k < size(bullets); k++)
		{
			if (bullets[k].life == true)
			{
				for (int i = (y + 16) * 1.5 / TILE_SIDE ; i < (y + h) / TILE_SIDE; i++)
				{
					for (int j = x / TILE_SIDE; j < (x + w) / TILE_SIDE; j++)
					{
						if (tileMap[i][j] == '0' || tileMap[i][j] == 's')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
						{
							bullets[k].life = false;
						}
					}
				}
			}
		}
	}

	void update(float time, RenderWindow & window)
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
		}

		

		x += dx * time;
		y += dy * time;

		checkCollision();
		bulletSprite.setPosition(x, y);

		for (int i = 0; i < size(bullets); i++)
		{
			if (bullets[i].life == true)
			{
				window.draw(bullets[i].bulletSprite);
			}
		}
	}

	void deleteBullet(float gameTime)
	{
		for (int i = 0; i < size(bullets); i++)
		{
			if (bullets[i].life == true)
			{
				if (gameTime > bullets[i].timeShot + 1)
					bullets[i].life = false;
			}
		}
	}
}bullets[50];