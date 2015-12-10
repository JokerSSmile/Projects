#include "pendulum.h"

void ProcessEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void DrawWindow(RenderWindow& window, Pendulum& myPendulum)
{
	window.clear(Color(220, 220, 220));
	window.draw(myPendulum.LeftWheelSprite);
	window.draw(myPendulum.RightWheelSprite);
	window.draw(myPendulum.cap);
	window.draw(myPendulum.cargo);
	window.display();
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "7.3",Style::Close, settings);

	Clock clock;
	Time updateTime = Time::Zero;

	Pendulum *myPendulum = new Pendulum;
	InitSprites(*myPendulum);
	InitShapes(*myPendulum);

	while (window.isOpen())
	{
		updateTime += clock.restart();
		while (updateTime > FPS_LIMIT)
		{
			updateTime -= FPS_LIMIT;
			ProcessEvents(window);
			UpdatePendulum(*myPendulum);
			UpdateGear(*myPendulum);
		}
		DrawWindow(window, *myPendulum);
	}
	delete myPendulum;
	return 0;
}
