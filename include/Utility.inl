#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

template <typename T>
std::string toString(const T& value) {
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template <typename T>
void centerOrigin(T& t) {
    sf::FloatRect bounds = t.getLocalBounds();
    t.setOrigin(
        std::floor(bounds.left + bounds.width / 2.f),
        std::floor(bounds.top + bounds.height / 2.f)
    );
}
