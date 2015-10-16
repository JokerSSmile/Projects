#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;


struct Character;

struct Enemy : public Character
{
private:
	float moveTimer = 0;
	float currentFrame = 0;
	int randNum;
public:
	Enemy(Image & image, float X, float Y, int W, int H, String Name) :Character(image, X, Y, w, h, Name)
	{
		w = W;
		h = H;
		x = X;
		y = Y;
		if (name == "EnemyFly")
		{
			randNum = rand() % 2;
			if (randNum == 0)	dx = 0.1;
			else dx = -0.1;
		}
	}

	void checkCollosion()//ф-ция взаимодействия с картой
	{
		for (int i = (y+h/1.5) / 64; i < (y + h) / 64; i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 64; j < (x + w/1.25) / 64; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'r')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dx > 0)//right
					{
						x = j * 64 - w;
						dx = -0.1;
					}
					else if (dx < 0)//left
					{
						x = j * 64 + 64;
						dx = 0.1;
					}
				}
			}
	}


	void update(float time)
	{
		if (name == "EnemyFly")
		{
			currentFrame += 0.005 * time;
			if (currentFrame > 2) currentFrame -= 2;
			sprite.setTextureRect(IntRect(57 * int(currentFrame), 0, 57, 45));

		}
		checkCollosion();
		x += dx*time;
		sprite.setPosition(x, y);
	}
};
