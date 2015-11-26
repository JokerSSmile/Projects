#include <SFML/Graphics.hpp>
#include "Clock.h"
#include <windows.h>
#include <ctime>

using namespace sf;
using namespace std;

void ProcessEvents(RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void UpdateClock(AnalogClock& myClock, SYSTEMTIME& currentTime)
{
	myClock.hourHand->setRotation(float((currentTime.wHour + 3) * 30));
	myClock.minuteHand->setRotation(float(currentTime.wMinute * 6));
	myClock.secondHand->setRotation(float(currentTime.wSecond * 6));
}

void RenderClock(AnalogClock& myClock, RenderWindow& window)
{
	window.clear(Color::White);
	window.draw(*myClock.dial);
	window.draw(*myClock.hourHand);
	window.draw(*myClock.minuteHand);
	window.draw(*myClock.secondHand);
	window.draw(*myClock.clockCenter);
	DrawLabels(myClock);
	window.display();
}

int main()
{
	AnalogClock *myClock = new AnalogClock;
	InitializeClock(*myClock);
	RenderWindow& window = *myClock->window;
	while (window.isOpen())
	{
		SYSTEMTIME currentTime;
		GetSystemTime(&currentTime);

		ProcessEvents(window);
		UpdateClock(*myClock, currentTime);
		RenderClock(*myClock, window);

	}
	DeleteClock(*myClock);
	return 0;
}
