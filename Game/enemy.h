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

	void checkCollosion()//�-��� �������������� � ������
	{
		for (int i = (y+h/1.5) / 64; i < (y + h) / 64; i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 64; j < (x + w/1.25) / 64; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'r')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
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
