#include "constants.h"
#include "program.h"

void ProcessEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void DrawWindow(RenderWindow& window, Car& myCar)
{
	window.clear(Color(220, 220, 220));
	window.draw(myCar.ground);
	window.draw(myCar.background);
	window.draw(myCar.leftWheel);
	window.draw(myCar.rightWheel);
	window.draw(myCar.carSprite);
	window.display();
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "7.3", Style::Close, settings);

	Clock clock;
	Time updateTime = Time::Zero;

	Car *myCar = new Car;
	
	InitCar(*myCar);

	while (window.isOpen())
	{
		updateTime += clock.restart();
		while (updateTime > FPS_LIMIT)
		{
			updateTime -= FPS_LIMIT;
			ProcessEvents(window);
			UpdateCar(*myCar);
		}
		DrawWindow(window, *myCar);
	}
	delete myCar;
	return 0;
}
