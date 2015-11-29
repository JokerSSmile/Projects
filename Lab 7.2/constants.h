#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const Vector2i WINDOW_SIZE = { 600,400 };

const Time FPS_LIMIT = seconds(1.f/90.f);

const int BLOCKS_COUNT = 5;
const int SPACE_BETWEEN_BLOCKS = 40;

const float BLOCK_SPEED = 2;
const float BLOCK_COLOR_CHANGE_SPEED = 3;

const int FIRST_STEP_SHIFT = 300;

const Vector2i BLOCK_START_SIZE = { 30, 30 };
const Vector2f START_POSITION = { 50, 100 };
