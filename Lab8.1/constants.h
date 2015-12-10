#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace sf;

static const Vector2i WINDOW_SIZE = { 800, 600 };

static const Time FPS_LIMIT = seconds(1.f / 60.f);

static const float ACCELERATION = 0.1f;
static const float MAX_SPEED = 4;

static const float WHEEL_RADIUS = 19.5f;

static const Vector2f LEFT_WHEEL_POS = {70, 13};
static const Vector2f RIGHT_WHEEL_POS = {80, 13};
