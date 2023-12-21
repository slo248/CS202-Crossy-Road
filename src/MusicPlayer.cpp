#include "MusicPlayer.hpp"
#include "State.hpp"

MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(100.f) {
    mFilenames[Musics::DuringPlay]    = "asset/music/DuringPlay.mp3";
	mFilenames[Musics::Introduction] = "asset/music/Introduction.mp3";
}

void MusicPlayer::play(Musics::ID theme) {
    std::string filename = mFilenames[theme];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop() { mMusic.stop(); }

void MusicPlayer::setVolume(float volume) { mVolume = volume; }

void MusicPlayer::setPaused(bool paused) {
    if (paused)
        mMusic.pause();
    else
        mMusic.play();
}
