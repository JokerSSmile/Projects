#include "application.h"

void InitApp(Application& app)
{
	app.background.setSize(Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y * 2 / 3));
	app.background.setPosition(Vector2f(0, 0));
	app.background.setFillColor(Color(155, 255, 255));
	app.ground.setSize(Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y * 1 / 3));
	app.ground.setPosition(Vector2f(0, WINDOW_SIZE.y * 2 / 3));
	app.ground.setFillColor(Color(80, 70, 70));
}

void ProcessEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void DrawWindow(RenderWindow& window, Car& myCar, Application& app)
{
	window.clear(Color(220, 220, 220));
	window.draw(app.ground);
	window.draw(app.background);
	window.draw(myCar.leftWheel);
	window.draw(myCar.rightWheel);
	window.draw(myCar.carSprite);
	window.display();
}
