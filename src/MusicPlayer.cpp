#include "MusicPlayer.hpp"

#include "State.hpp"

MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(100.f) {
    mFilenames[Musics::Introduction] = "asset/music/Introduction.mp3";
    mFilenames[Musics::Music1] = "asset/music/music1.mp3";
    mFilenames[Musics::Music2] = "asset/music/music2.mp3";
    mFilenames[Musics::Music3] = "asset/music/music3.mp3";
    mFilenames[Musics::Win] = "asset/music/Win.mp3";
    mFilenames[Musics::HighScore] = "asset/music/HighScore.mp3";
    mFilenames[Musics::Lose] = "asset/music/Lose.mp3";
}

void MusicPlayer::play(Musics::ID theme, bool loop) {
    if (theme == Musics::None) {
        mMusic.stop();
        return;
    }

    std::string filename = mFilenames[theme];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(loop);
    mMusic.play();
}

void MusicPlayer::stop() { mMusic.stop(); }

void MusicPlayer::setVolume(float volume) { mVolume = volume; }

void MusicPlayer::setPaused(bool paused) {
    if (paused)
        mMusic.pause();
    else {
        mMusic.setVolume(mVolume);
        mMusic.play();
    }
}
