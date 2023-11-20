#include "DialogGeneral.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

DialogGeneral::DialogGeneral(const sf::Texture& texture) : Dialog(texture) {
    this->setPosition(21.f, 146.f);
}
