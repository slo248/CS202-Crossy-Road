#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <sstream>

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

#include "Utility.inl"
#endif
