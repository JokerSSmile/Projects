#include "constants.h"
#include "application.h"


int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "7.3", Style::Close, settings);

	Clock clock;

	Car *myCar = new Car;
	Application *myApplication = new Application;
	
	InitCar(*myCar);
	InitApp(*myApplication);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;

		{
			ProcessEvents(window);
			UpdateCar(*myCar, time);
		}
		DrawWindow(window, *myCar, *myApplication);
	}
	delete myCar;
	return 0;
}
