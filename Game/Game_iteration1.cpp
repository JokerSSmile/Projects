#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "view.h"

using namespace sf;
using namespace std;


struct Character
{
public:
	float dx, dy, x, y, speed;
	int w, h, health;
	bool life;
	Texture texture;
	Sprite sprite;
	String name;
	Character(Image & image, float X, float Y, int W, int H, String Name)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
		name = Name;
		speed = 0;
		health = 100;
		dx = 0;
		dy = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};


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
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 64; j < (x + w) / 64; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
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
		//if 
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
			randNum = rand()%2;
			cout << randNum << endl;
			if (randNum == 0)	dx = 0.1;
			else dx = -0.1;
		}
	}

	void checkCollosion()//ф-ция взаимодействия с картой
	{
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 64; j < (x + w) / 64; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'r')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dx > 0)//right
					{
						x = j*64 - w;
						dx = -0.1;
					}
					else if (dx < 0)//left
					{
						x = j*64 +64;
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


int main()
{
	//karta i taili
	Image map_image;
	map_image.loadFromFile("images/Rock.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	//background
	Image mapBackground;
	mapBackground.loadFromFile("images/bigMap.png");
	Texture mapBackgroundTexture;
	mapBackgroundTexture.loadFromImage(mapBackground);
	Sprite mapBackgroundSprite;
	mapBackgroundSprite.setTexture(mapBackgroundTexture);

	//hero
	Image heroImage;
	heroImage.loadFromFile("images/charaset.png");

	//enemy image
	Image enemyImage;
	enemyImage.loadFromFile("images/fly.png");

	//enemy
	Enemy e1(enemyImage, 128, 128, 57, 45, "EnemyFly");
	Enemy e2(enemyImage, 250, 350, 57, 45, "EnemyFly");


	//sozdanie igroka
	Player p(heroImage, 250, 200, 56, 96, "Hero");


	

	RenderWindow window(sf::VideoMode(960, 640), "Game");

	view.reset(FloatRect(0, 0, 960, 640));


	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		p.update(time);
		e1.update(time);
		e2.update(time);



		if (int(p.x - p.w/2)  == int(e1.x - e1.w/2))
		{
			//cout << "12314" << endl;
		}


		viewmap(time);
		window.setView(view);
		window.clear();


		window.draw(mapBackgroundSprite);


		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 'r')
				{
					s_map.setTextureRect(IntRect(0, 0, 64, 64));
					s_map.setPosition(j * 64, i * 64);
					window.draw(s_map);
				}
			}
	
		if (int(p.x) == int(e1.x))
		{
			e1.health = 0;
			cout << "34" << endl;
		}
		//draw
		window.draw(p.sprite);
		if (e1.health > 0)
		{
			window.draw(e1.sprite);
		}
		if (e2.health > 0)
		{
			window.draw(e2.sprite);
		}


		window.display();
	}

	return 0;
}