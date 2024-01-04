#include "VolumeBar.hpp"

#include <iostream>

#define VOLUME_BAR_WIDTH 210.f
#define VOLUME_BAR_HEIGHT 10.f
#define VOLUME_BAR_X 586.f
#define VOLUME_BAR_Y 248.f

VolumeBar::VolumeBar(State::Context& context)
    : isDragging(false), mVolumeLevel(context.volumeLevel), mContext(&context) {
    sf::Color color;

    mVolumeBackground.setSize(sf::Vector2f(VOLUME_BAR_WIDTH, VOLUME_BAR_HEIGHT)
    );
    color = sf::Color(232, 180, 133);
    mVolumeBackground.setFillColor(color);
    mVolumeBackground.setPosition(VOLUME_BAR_X, VOLUME_BAR_Y);

    mVolumeBar.setSize(sf::Vector2f(
        (mVolumeLevel / 100.f) * VOLUME_BAR_WIDTH, VOLUME_BAR_HEIGHT
    ));
    color = sf::Color(56, 151, 40);
    mVolumeBar.setFillColor(color);
    mVolumeBar.setPosition(VOLUME_BAR_X, VOLUME_BAR_Y);

    mVolumeDot.setRadius(10);
    color = sf::Color(182, 182, 182);
    mVolumeDot.setFillColor(color);

    mVolumeDot.setPosition(
        VOLUME_BAR_X + (mVolumeLevel / 100.f) * VOLUME_BAR_WIDTH,
        VOLUME_BAR_Y - 5
    );
}

void VolumeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mVolumeBackground, states);
    target.draw(mVolumeBar, states);
    target.draw(mVolumeDot, states);
}

void VolumeBar::handleEvent(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos =
                window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (mVolumeDot.getGlobalBounds().contains(mousePos)) {
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
            sf::Vector2f mousePos =
                window.mapPixelToCoords(sf::Mouse::getPosition(window));
            float newX = clamp(
                mousePos.x, VOLUME_BAR_X, VOLUME_BAR_X + VOLUME_BAR_WIDTH
            );
            mVolumeDot.setPosition(newX, VOLUME_BAR_Y - 5);
            mVolumeLevel = (newX - VOLUME_BAR_X) / VOLUME_BAR_WIDTH * 100.f;
            mContext->volumeLevel = mVolumeLevel;
            mVolumeBar.setSize(sf::Vector2f(
                (mVolumeLevel / 100.f) * VOLUME_BAR_WIDTH, VOLUME_BAR_HEIGHT
            ));
        }
    }
}

void VolumeBar::update() {}

float VolumeBar::clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}
