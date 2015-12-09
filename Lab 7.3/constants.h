#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

const Vector2i WINDOW_SIZE = { 800, 600 };
const Time FPS_LIMIT = seconds(1.f / 60.f);

const int LEFT_BORDER = 20;
const int RIGHT_BORDER = 340;
const int CIRCLE_ANGLE = 360;

const float ACCELERATION = 0.01f;
const float WHEEL_SPEED = 0.8f;

const Vector2i RIGHT_WHEEL_START_POSITION = { 500, 400 };
const Vector2i LEFT_WHEEL_START_POSITION = { 560, 400 };
