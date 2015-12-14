#pragma once

#include "constants.h"

struct Car
{
	Car() {};
	Texture carTexture;
	Sprite carSprite;
	Sprite leftWheel;
	Sprite rightWheel;

	float speed = 0;
};

void InitCar(Car& myCar);
void UpdateCar(Car& myCar, float time);
