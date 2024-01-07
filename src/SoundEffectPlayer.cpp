#include "SoundEffectPlayer.hpp"

#include <SFML/Audio/Listener.hpp>
#include <cmath>

namespace {
// Sound coordinate system, point of view of a player in front of the screen:
// X = left; Y = up; Z = back (out of the screen)
const float ListenerZ = 300.f;
const float Attenuation = 8.f;
const float MinDistance2D = 200.f;
const float MinDistance3D =
    std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}  // namespace

SoundEffectPlayer::SoundEffectPlayer() : mSoundBuffers(), mSounds() {
    mSoundBuffers.loadSoundBufferFromFile();
}

void SoundEffectPlayer::play(SoundEffects::ID effect) {
    play(effect, getListenerPosition());
}

void SoundEffectPlayer::play(SoundEffects::ID effect, sf::Vector2f position) {
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffers.get(effect));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.setVolume(mVolume);
    sound.play();
}

void SoundEffectPlayer::setVolume(float volume) { mVolume = volume; }

void SoundEffectPlayer::removeStoppedSounds() {
    mSounds.remove_if([](const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundEffectPlayer::setListenerPosition(sf::Vector2f position) {
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundEffectPlayer::getListenerPosition() const {
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}
