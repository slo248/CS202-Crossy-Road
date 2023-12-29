#include "VolumeBar.hpp"
#include <iostream>

VolumeBar::VolumeBar(float width, float height) : isDragging(false), volumeLevel(50.0f) {
    volumeBar.setSize(sf::Vector2f(width, height));
    volumeBar.setFillColor(sf::Color::Green);

    volumeDot.setRadius(10);
    volumeDot.setFillColor(sf::Color::Blue);
    volumeDot.setPosition(50, 100);
}

void VolumeBar::setPosition(float x, float y) {
    volumeBar.setPosition(x, y);
}

void VolumeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(volumeBar, states);
    target.draw(volumeDot, states);
}

void VolumeBar::handleEvent(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (volumeDot.getGlobalBounds().contains(mousePos)) {
                isDragging = true;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isDragging = false;
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        if (isDragging) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            float newX = clamp(mousePos.x, 50.0f, 350.0f);
            volumeDot.setPosition(newX, 100);
            volumeBar.setSize(sf::Vector2f(newX - 50, 20));
            volumeLevel = (newX - 50) / 3;
            std::cout << "Volume set to: " << volumeLevel << std::endl;
        }
    }
}

void VolumeBar::update() {
    // Any updates to the volume bar can be handled here (if needed)
}

float VolumeBar::clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}
