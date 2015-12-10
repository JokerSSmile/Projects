#include "pendulum.h"

void InitSprites(Pendulum& myPendulum)
{
	myPendulum.RightWheelTexture.loadFromFile("images/6.png");
	myPendulum.RightWheelSprite.setTexture(myPendulum.RightWheelTexture);
	myPendulum.RightWheelSprite.setOrigin(myPendulum.RightWheelSprite.getGlobalBounds().width / 2, myPendulum.RightWheelSprite.getGlobalBounds().height / 2);
	myPendulum.RightWheelSprite.setScale(1.2, 1.2);
	myPendulum.RightWheelSprite.setPosition(RIGHT_WHEEL_START_POSITION.x, RIGHT_WHEEL_START_POSITION.y);
	myPendulum.RightWheelSprite.setRotation(21);

	myPendulum.LeftWheelTexture.loadFromFile("images/6.png");
	myPendulum.LeftWheelSprite.setTexture(myPendulum.LeftWheelTexture);
	myPendulum.LeftWheelSprite.setOrigin(myPendulum.LeftWheelSprite.getGlobalBounds().width / 2, myPendulum.LeftWheelSprite.getGlobalBounds().height / 2);
	myPendulum.RightWheelSprite.setScale(1.1, 1.1);
	myPendulum.LeftWheelSprite.setPosition(LEFT_WHEEL_START_POSITION.x - (myPendulum.RightWheelSprite.getGlobalBounds().width) / 1.3, LEFT_WHEEL_START_POSITION.y);
};

void InitShapes(Pendulum& myPendulum)
{
	myPendulum.cap.setPointCount(4);
	myPendulum.cap.setPoint(0, Vector2f(550, 100));
	myPendulum.cap.setPoint(1, Vector2f(480, 150));
	myPendulum.cap.setPoint(2, Vector2f(550, 130));
	myPendulum.cap.setPoint(3, Vector2f(620, 150));
	myPendulum.cap.setFillColor(Color::Blue);
	myPendulum.cap.setOrigin(myPendulum.cap.getPoint(0));
	myPendulum.cap.setPosition(myPendulum.cap.getPoint(0));
	myPendulum.cap.setRotation(20);

	myPendulum.cargo.setPointCount(7);
	myPendulum.cargo.setPoint(0, Vector2f(545, 120));
	myPendulum.cargo.setPoint(1, Vector2f(545, 400));
	myPendulum.cargo.setPoint(2, Vector2f(525, 450));
	myPendulum.cargo.setPoint(3, Vector2f(550, 460));
	myPendulum.cargo.setPoint(4, Vector2f(575, 450));
	myPendulum.cargo.setPoint(5, Vector2f(555, 400));
	myPendulum.cargo.setPoint(6, Vector2f(555, 120));
	myPendulum.cargo.setFillColor(Color::Blue);
	myPendulum.cargo.setOrigin(myPendulum.cap.getPoint(0));
	myPendulum.cargo.setPosition(myPendulum.cap.getPoint(0));
	myPendulum.cargo.setRotation(20);
};

void UpdateIfRightMove(Pendulum& myPendulum)
{
	if (int(myPendulum.cargo.getRotation()) >= 0 && int(myPendulum.cargo.getRotation()) <= LEFT_BORDER)
	{
		myPendulum.cargo.setRotation(myPendulum.cargo.getRotation() - myPendulum.speed);
		myPendulum.speed = myPendulum.speed + ACCELERATION;
	}
	else if (int(myPendulum.cargo.getRotation()) <= (CIRCLE_ANGLE - 1) && int(myPendulum.cargo.getRotation()) >= RIGHT_BORDER)
	{
		myPendulum.cargo.setRotation(myPendulum.cargo.getRotation() - myPendulum.speed);
		myPendulum.speed = myPendulum.speed - ACCELERATION;
	}
	if (int(myPendulum.cargo.getRotation()) == RIGHT_BORDER)
	{
		myPendulum.speed = 0;
		myPendulum.isMovingLeft = false;
	}
}

void UpdateIfLeftMove(Pendulum& myPendulum)
{
	if (int(myPendulum.cargo.getRotation()) <= CIRCLE_ANGLE - 1 && int(myPendulum.cargo.getRotation()) >= RIGHT_BORDER)
	{
		myPendulum.cargo.setRotation(myPendulum.cargo.getRotation() + myPendulum.speed);
		myPendulum.speed = myPendulum.speed + ACCELERATION;
	}
	else if (int(myPendulum.cargo.getRotation()) >= 0 && int(myPendulum.cargo.getRotation()) <= 20)
	{
		myPendulum.cargo.setRotation(myPendulum.cargo.getRotation() + myPendulum.speed);
		myPendulum.speed = myPendulum.speed - ACCELERATION;
	}
	if (int(myPendulum.cargo.getRotation()) == 20)
	{
		myPendulum.speed = 0;
		myPendulum.isMovingLeft = true;
	}
}

void UpdatePendulum(Pendulum& myPendulum)
{
	if (myPendulum.isMovingLeft == true)
	{
		UpdateIfRightMove(myPendulum);
	}
	else
	{
		UpdateIfLeftMove(myPendulum);
	}

	//the same with cap
	myPendulum.cap.setRotation(myPendulum.cargo.getRotation());
};

void UpdateGear(Pendulum& myPendulum)
{
	if (myPendulum.isMovingLeft == true)
	{
		myPendulum.LeftWheelSprite.setRotation(myPendulum.LeftWheelSprite.getRotation() - WHEEL_SPEED);
		myPendulum.RightWheelSprite.setRotation(myPendulum.RightWheelSprite.getRotation() + WHEEL_SPEED);
	}
	else
	{
		myPendulum.LeftWheelSprite.setRotation(myPendulum.LeftWheelSprite.getRotation() + WHEEL_SPEED);
		myPendulum.RightWheelSprite.setRotation(myPendulum.RightWheelSprite.getRotation() - WHEEL_SPEED);
	}
};

