#pragma once
#include <SFML/Graphics.hpp>

const sf::Vector2i WINDOW_SIZE = {850, 640};

const int CELL_SIDE = 200;
const int SPACE_BETWEEN_CELL = 10;
const int CELL_SIZE_PLUS_SPACE = 210;
const int SECOND_CELL_POSITION_START = 220;
const int SECOND_CELL_POSITION_END = 420;
const int THIRD_CELL_POSITION_START = 430;
const int THIRD_CELL_POSITION_END = 630;

const sf::Vector2i XWIN_SPRITE_POSITION = { 40, 240 };
const sf::Vector2i OWIN_SPRITE_POSITION = XWIN_SPRITE_POSITION;
const sf::Vector2i DRAW_SPRITE_POSITION = { 110, 240 };

const sf::Vector2i CURRENTSPRITE_POSITION_IF_ONE_PLAYER = { 40, 270 };
const sf::Vector2i CURRENTSPRITE_POSITION_IF_TWO_PLAYERS = { 40, 380 };

const sf::Vector2i ONE_PLAYER_SPRITE_POSITION_X = { 100,  486 };
const sf::Vector2i ONE_PLAYER_SPRITE_POSITION_Y = { 260, 361 };
const sf::Vector2i TWO_PLAYERS_SPRITE_POSITION_X = { 100,  559 };
const sf::Vector2i TWO_PLAYERS_SPRITE_POSITION_Y = { 370, 471 };

const int FIELD_CELLS = 3;
const int SPACE_BETWEEN_MARK_AND_CELL = 46;

const int SPRITE_SIDE = 128;

const sf::Vector2i MENU_CELL_SIZE = { 200, 620 };
const sf::Vector2i MENU_CELL_POSITION = { 640, 10 };
const sf::Vector2i REFRESH_SPRITE_POSITION = { 676, 150 };
const sf::Vector2i EXIT_POSITION = { 676, 360 };

const sf::Vector2i RECTANGLESTART_SIZE = { 830, 620 };

const int MAX_TURNS = 9;

const int FIRST_LINE = 0;
const int FIRST_COLOMN = 0;
const int SECOND_LINE = 1;
const int SECOND_COLOMN = 1;
const int THIRD_LINE = 2;
const int THIRD_COLOMN = 2;
