#pragma once
#include <SFML/Graphics.hpp>

void PcTurn(sf::RenderWindow& window, int& turnCounter, int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn);
