#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include "clock.h"

void InitializeClock(AnalogClock& myClock)
{
	ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	myClock.window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Clock", Style::Default, settings);

	//set hour hand
	myClock.hourHand = new RectangleShape(Vector2f(HOUR_HAND_SIZE));
	myClock.hourHand->setOrigin(HOUR_HAND_SIZE.x / 2, HOUR_HAND_SIZE.y);
	myClock.hourHand->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	myClock.hourHand->setFillColor(Color::Black);

	//set minute hand
	myClock.minuteHand = new RectangleShape(Vector2f(MINUTE_HAND_SIZE));
	myClock.minuteHand->setOrigin(MINUTE_HAND_SIZE.x / 2, MINUTE_HAND_SIZE.y);
	myClock.minuteHand->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	myClock.minuteHand->setFillColor(Color::Green);

	//set second hand
	myClock.secondHand = new RectangleShape(Vector2f(SECOND_HAND_SIZE));
	myClock.secondHand->setOrigin(SECOND_HAND_SIZE.x / 2, SECOND_HAND_SIZE.y);
	myClock.secondHand->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	myClock.secondHand->setFillColor(Color::Red);

	//set dial
	myClock.dial = new CircleShape(DIAL_RADIUS);
	myClock.dial->setOrigin(DIAL_RADIUS, DIAL_RADIUS);
	myClock.dial->setOutlineThickness(5);
	myClock.dial->setFillColor(Color::White);
	myClock.dial->setOutlineColor(Color::Black);
	myClock.dial->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	myClock.dial->setPointCount(60);

	//set clock center
	myClock.clockCenter = new CircleShape(CENTER_CIRCLE_RADIUS);
	myClock.clockCenter->setOrigin(CENTER_CIRCLE_RADIUS, CENTER_CIRCLE_RADIUS);
	myClock.clockCenter->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	myClock.clockCenter->setFillColor(Color::Blue);

	//set labels
	myClock.label = new CircleShape(5);
	myClock.label->setOrigin(LABEL_RADIUS, LABEL_RADIUS);
}

void DrawLabels(AnalogClock& myClock)
{
	Vector2i position = { 0, 0 };

	for (int i = 0; i < 12; i++)
	{
		if ((i) % 3 == 0)
		{
			myClock.label->setFillColor(Color::Blue);
		}
		else
		{
			myClock.label->setFillColor(Color::Black);
		}
		position.x = WINDOW_WIDTH / 2 + DIAL_RADIUS * sin(2 * M_PI / 12 * i);
		position.y = WINDOW_HEIGHT / 2 + DIAL_RADIUS * cos(2 * M_PI / 12 * i);
		myClock.label->setPosition(position.x, position.y);
		myClock.window->draw(*myClock.label);
	}
}

void DeleteClock(AnalogClock& myClock)
{
	delete myClock.window;
	delete myClock.dial;
	delete myClock.hourHand;
	delete myClock.minuteHand;
	delete myClock.secondHand;
	delete myClock.label;
}
