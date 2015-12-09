#pragma once

#include "constants.h"

struct Pendulum
{
	Pendulum() {};
	Texture LeftWheelTexture;
	Texture RightWheelTexture;
	Sprite LeftWheelSprite;
	Sprite RightWheelSprite;
	ConvexShape cap;
	ConvexShape cargo;
	bool isLeft = false;
	float speed = 0;
};

void InitSprites(Pendulum*& myPendulum);
void InitShapes(Pendulum*& myPendulum);
void UpdatePendulum(Pendulum*& myPendulum);
void UpdateGear(Pendulum*& myPendulum);
void DestroyPendulum(Pendulum*& myPendulum);
