#include "car.h"

void InitCar(Car& myCar)
{
	myCar.carTexture.loadFromFile("images/car.png");

	//texture
	myCar.carSprite.setTexture(myCar.carTexture);
	myCar.rightWheel.setTexture(myCar.carTexture);
	myCar.leftWheel.setTexture(myCar.carTexture);

	//texture rect
	myCar.carSprite.setTextureRect(IntRect(45, 0, 830, 240));
	myCar.rightWheel.setTextureRect(IntRect(145, 305, 130, 130));
	myCar.leftWheel.setTextureRect(IntRect(145, 305, 130, 130));

	//origin
	myCar.carSprite.setOrigin(myCar.carSprite.getGlobalBounds().width / 2, myCar.carSprite.getGlobalBounds().height);
	myCar.rightWheel.setOrigin(float(myCar.rightWheel.getGlobalBounds().width / 2), float(myCar.rightWheel.getGlobalBounds().height / 2));
	myCar.leftWheel.setOrigin(float(myCar.leftWheel.getGlobalBounds().width / 2), float(myCar.leftWheel.getGlobalBounds().height / 2));

	//scale
	myCar.carSprite.setScale(0.3, 0.3);
	myCar.leftWheel.setScale(0.3, 0.3);
	myCar.rightWheel.setScale(0.3, 0.3);

	//position
	myCar.carSprite.setPosition(200, WINDOW_SIZE.y * 2 / 3 - 5);
	myCar.rightWheel.setPosition(float(myCar.carSprite.getPosition().x + RIGHT_WHEEL_POS.x), float(myCar.carSprite.getPosition().y - RIGHT_WHEEL_POS.y));
	myCar.leftWheel.setPosition(float(myCar.carSprite.getPosition().x - LEFT_WHEEL_POS.x), float(myCar.carSprite.getPosition().y - LEFT_WHEEL_POS.y));
}

void UpdateRotation(Car& myCar)
{
	myCar.rightWheel.rotate(float(float(180 * myCar.speed) / (M_PI * WHEEL_RADIUS)));
	myCar.leftWheel.rotate(float(float(180 * myCar.speed) / (M_PI * WHEEL_RADIUS)));
}

void UpdateSpeed(Car& myCar, float time)
{
	if (myCar.carSprite.getPosition().x < WINDOW_SIZE.x / 2)
	{
		myCar.speed += ACCELERATION * time;
	}
	else
	{
		myCar.speed -= ACCELERATION* time;
	}
}

void UpdateCarsPosition(Car& myCar)
{
	myCar.carSprite.move(myCar.speed, 0);
	myCar.leftWheel.setPosition(float(myCar.carSprite.getPosition().x - LEFT_WHEEL_POS.x), float(myCar.carSprite.getPosition().y - LEFT_WHEEL_POS.y));
	myCar.rightWheel.setPosition(float(myCar.carSprite.getPosition().x + RIGHT_WHEEL_POS.x), float(myCar.carSprite.getPosition().y - RIGHT_WHEEL_POS.y));
}

void UpdateCar(Car& myCar, float time)
{
	UpdateSpeed(myCar, time);
	UpdateCarsPosition(myCar);
	UpdateRotation(myCar);
}
