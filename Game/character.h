#include <SFML/Graphics.hpp>
#include <iostream>

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