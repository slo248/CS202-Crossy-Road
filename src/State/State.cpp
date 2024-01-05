#include "State.hpp"

#include <iostream>

#include "GameState.hpp"
#include "StateStack.hpp"

State::Context::Context(
    sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
    MusicPlayer& musics, SoundEffectPlayer& soundEffects, Player& player,
    std::vector<Highscore>& highScores
)
    : window(&window),
      textures(&textures),
      fonts(&fonts),
      musics(&musics),
      soundEffects(&soundEffects),
      player(&player),
      highScores(&highScores) {}

State::State(StateStack& stack, Context& context)
    : mGUIContainer(), mStack(&stack), mContext(&context) {}



State::~State() {}

void State::requestStackPush(States::ID stateID) { mStack->pushState(stateID); }

void State::requestStackPop() { mStack->popState(); }

void State::requestStackClear() { mStack->clearStates(); }
