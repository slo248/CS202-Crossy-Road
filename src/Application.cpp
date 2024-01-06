#include "Application.hpp"

#include <fstream>
#include <iostream>

#include "ChooseModeState.hpp"
#include "CreditState.hpp"
#include "GameState.hpp"
#include "LevelState.hpp"
#include "LoseState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "RankingState.hpp"
#include "SettingState.hpp"
#include "WinState.hpp"

Application::Application()
    : mWindow(
          sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT),
          "Crossing Road", sf::Style::Default
      ),
      mTextures(),
      mFonts(),
      mMusics(),
      mSoundEffects(),
      mPlayer(),
      mHighScores(DEFAULT_RANKING_SLOTS, {0, "anonymous"}),
      mStateStack(initContext()) {
    mWindow.setFramerateLimit(60);
    mTextures.loadTextureFromFile();
    mFonts.loadFontFromFile();

    registerStates();
    mStateStack.pushState(States::Menu);

    mMusics.setVolume(25.f);
    mSoundEffects.setVolume(50.f);
}

Application::~Application() {
    // saveSettings();
    saveRanking();
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before
            // update() call
            if (mStateStack.isEmpty()) mWindow.close();
        }

        render();
    }
}

void Application::processInput() {
    sf::Event event;

    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }
}

void Application::update(sf::Time dt) { mStateStack.update(dt); }

void Application::render() {
    mWindow.clear(sf::Color::White);
    mStateStack.draw();
    mWindow.display();
}

void Application::registerStates() {
    mStateStack.registerState<SettingState>(States::Setting);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<CreditState>(States::Credit);
    mStateStack.registerState<LoseState>(States::Lose);
    mStateStack.registerState<WinState>(States::Win);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<RankingState>(States::Ranking);
    mStateStack.registerState<LevelState>(States::Level);
    mStateStack.registerState<ChooseModeState>(States::ChooseMode);
}

State::Context Application::initContext() {
    // loadSettings();
    loadRanking();

    return State::Context(
        mWindow, mTextures, mFonts, mMusics, mSoundEffects, mPlayer, mHighScores
    );
}

void Application::saveRanking() {
    std::ofstream out;
    out.open(RANKING_PATH);
    if (!out.good()) {
        std::cout << "Cannot save ranking\n";
        out.close();
        return;
    }

    for (int i = 0; i < DEFAULT_RANKING_SLOTS; ++i) {
        out << mHighScores[i].score << "\n" << mHighScores[i].date << "\n";
    }
    out.close();
}

void Application::loadRanking() {
    std::ifstream in(RANKING_PATH);
    if (!in.good()) {
        std::cout << "No ranking file";
    }

    HighScore score;
    in >> score.score;
    in.ignore();
    std::getline(in, score.date);

    for (int i = 0; i < DEFAULT_RANKING_SLOTS && !in.eof(); ++i) {
        mHighScores[i] = score;
        in >> score.score;
        in.ignore();
        std::getline(in, score.date);
    }

    in.close();
}
