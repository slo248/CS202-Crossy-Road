#include "VolumeBar.hpp"

#include <iostream>

#define VOLUME_BAR_WIDTH 210.f
#define VOLUME_BAR_HEIGHT 10.f

VolumeBar::VolumeBar(State::Context& context, float x, float y, Type type)
    : mContext(&context), mType(type), mX(x), mY(y), mIsDragging(false) {
    sf::Color color;

    if (mType == Music) {
        mVolumeLevel = mContext->volumeMusic;
    } else {
        mVolumeLevel = mContext->volumeSfx;
    }

    mVolumeBackground.setSize(sf::Vector2f(VOLUME_BAR_WIDTH, VOLUME_BAR_HEIGHT)
    );
    color = sf::Color(232, 180, 133);
    mVolumeBackground.setFillColor(color);
    mVolumeBackground.setPosition(mX, mY);

    mVolumeBar.setSize(sf::Vector2f(
        (mVolumeLevel / 100.f) * VOLUME_BAR_WIDTH, VOLUME_BAR_HEIGHT
    ));
    color = sf::Color(56, 151, 40);
    mVolumeBar.setFillColor(color);
    mVolumeBar.setPosition(mX, mY);

    mVolumeDot.setRadius(10);
    color = sf::Color(182, 182, 182);
    mVolumeDot.setFillColor(color);

    mVolumeDot.setPosition(
        mX + (mVolumeLevel / 100.f) * VOLUME_BAR_WIDTH, mY - 5
    );

    toggleMute();
}

void VolumeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mVolumeBackground, states);
    target.draw(mVolumeBar, states);
    target.draw(mVolumeDot, states);
}

void VolumeBar::handleEvent(const sf::Event& event) {
    if ((mType == Music && mContext->isMuteMusic) ||
        (mType == Sfx && mContext->isMuteSfx))
        return;

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = mContext->window->mapPixelToCoords(
                sf::Mouse::getPosition(*(mContext->window))
            );

            if (mVolumeDot.getGlobalBounds().contains(mousePos)) {
                mIsDragging = true;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            mIsDragging = false;
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        if (mIsDragging) {
            sf::Vector2f mousePos = mContext->window->mapPixelToCoords(
                sf::Mouse::getPosition(*(mContext->window))
            );

            float newX = clamp(mousePos.x, mX, mX + VOLUME_BAR_WIDTH);

            mVolumeDot.setPosition(newX, mY - 5);
            mVolumeLevel = (newX - mX) / VOLUME_BAR_WIDTH * 100.f;

            if (mType == Music) {
                mContext->volumeMusic = mVolumeLevel;
            } else {
                mContext->volumeSfx = mVolumeLevel;
            }

            mVolumeBar.setSize(sf::Vector2f(
                (mVolumeLevel / 100.f) * VOLUME_BAR_WIDTH, VOLUME_BAR_HEIGHT
            ));
        }
    }
}

void VolumeBar::toggleMute() {
    if ((mType == Music && mContext->isMuteMusic) ||
        (mType == Sfx && mContext->isMuteSfx)) {
        mVolumeBar.setFillColor(sf::Color(182, 182, 182));
    } else {
        mVolumeBar.setFillColor(sf::Color(56, 151, 40));
    }
}

void VolumeBar::update() {}

float VolumeBar::clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}
