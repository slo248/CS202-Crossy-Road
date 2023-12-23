#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio/Music.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <map>
#include <string>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class MusicPlayer : private sf::NonCopyable {
   public:
    MusicPlayer();
    void play(Musics::ID theme, bool loop = true);
    void stop();
    void setPaused(bool paused);
    void setVolume(float volume);

   private:
    sf::Music mMusic;
    std::map<Musics::ID, std::string> mFilenames;
    float mVolume;
};

#endif
