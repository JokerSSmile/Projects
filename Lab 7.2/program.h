#pragma once
#include "constants.h"

using namespace sf;
using namespace std;

struct Block
{
	Block(float positionx, float positiony)
	{
		position.x = positionx;
		position.y = positiony;
		startPosition = { positionx, positiony };
	}
	RectangleShape figure;
	Vector2f startPosition;
	Vector2f position;
	Vector2i size;
};