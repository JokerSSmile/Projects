#include <SFML/Graphics.hpp>


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
	Enemy() {};
	Enemy(Image & image, float X, float Y, int W, int H, String Name, float Health) :Character(image, X, Y, w, h, Name, health)
	{
		w = W;
		h = H;
		x = X;
		y = Y;
		if (name == "EnemyFly")
		{
			dx = 0.1;
			health = 1.0;
		}
		else if (name == "Zombie")
		{
			dx = 0;
			health = 1.5;
		}
	}

	void checkCollosion()//�-��� �������������� � ������
	{
		
		for (int i = y / TILE_SIDE; i < (y + h) / TILE_SIDE; i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / TILE_SIDE; j < (x + w) / TILE_SIDE; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (tileMap[i][j] == '0' || tileMap[i][j] == 's')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
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
						y = i * TILE_SIDE - h;
						//dy = -0.1;
					}
					else if (dy < 0)
					{	
						y = i * TILE_SIDE + h;
						//dy = 0.1;
					}
					dy = -dy;
					dx = -dx;
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
		x += dx * time;
		y += dy * time;
		sprite.setPosition(x, y);
	}
	
}enemies[10];
