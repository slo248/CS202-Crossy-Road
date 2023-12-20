#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <sstream>

#include "Config.hpp"

namespace sf {
class Sprite;
class Text;
}  // namespace sf

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
template <typename T>
void centerOrigin(T& t);

int random(int left, int right);

float slotToPosition(int slot);

int positionToSlot(float x);

int getCurrentRow(int y);

float getLevelFactor(Config::GameLevel::Type gameType);

std::string savedGamePath(Config::GameLevel::Type type);

std::string gameModeToString(Config::GameLevel::Type type);

int gameLevelToBlocks(Config::GameLevel::Type gameLevel);

#include "Utility.inl"
#endif
