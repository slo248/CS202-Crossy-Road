#ifndef SOUND_EFFECT_PLAYER_HPP
#define SOUND_EFFECT_PLAYER_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class SoundEffectPlayer : private sf::NonCopyable {
   public:
    SoundEffectPlayer();

    void play(SoundEffects::ID effect);
    void play(SoundEffects::ID effect, sf::Vector2f position);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector2f position);
    sf::Vector2f getListenerPosition() const;

   private:
    SoundBufferHolder mSoundBuffers;
    std::list<sf::Sound> mSounds;
};

#endif  // SOUND_EFFECT_PLAYER_HPP
