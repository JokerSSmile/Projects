#pragma once

#include "car.h"
#include "constants.h"

struct Application
{
	Application() {};
	RectangleShape background;
	RectangleShape ground;
};

void InitApp(Application& app);
void ProcessEvents(RenderWindow& window);
void DrawWindow(RenderWindow& window, Car& myCar, Application& app);
