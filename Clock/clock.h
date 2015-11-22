#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "constants.h"

using namespace sf;
using namespace std;

struct AnalogClock
{
	RenderWindow* window;
	CircleShape* dial;
	RectangleShape* hourHand;
	RectangleShape* minuteHand;
	RectangleShape* secondHand;
	CircleShape* label;
	CircleShape* clockCenter;
};

void InitializeClock(AnalogClock& myClock);
void DrawLabels(AnalogClock& myClock);
void DeleteClock(AnalogClock& myClock);
