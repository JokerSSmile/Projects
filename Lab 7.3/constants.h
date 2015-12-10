#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

static const Vector2i WINDOW_SIZE = { 800, 600 };
static const Time FPS_LIMIT = seconds(1.f / 60.f);

static const int LEFT_BORDER = 20;
static const int RIGHT_BORDER = 340;
static const int CIRCLE_ANGLE = 360;

static const float ACCELERATION = 0.01f;
static const float WHEEL_SPEED = 0.8f;

static const Vector2i RIGHT_WHEEL_START_POSITION = { 500, 400 };
static const Vector2i LEFT_WHEEL_START_POSITION = { 560, 400 };
