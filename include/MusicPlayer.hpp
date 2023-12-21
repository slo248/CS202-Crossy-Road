#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio/Music.hpp>
#include <SFML/System/NonCopyable.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable {
   public:
    MusicPlayer();
    void play(Musics::ID theme);
    void stop();
    void setPaused(bool paused);
    void setVolume(float volume);

   private:
    sf::Music mMusic;
    std::map<Musics::ID, std::string> mFilenames;
    float mVolume;
};

#endif
