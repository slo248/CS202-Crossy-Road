#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Player.hpp"
#include "State.hpp"
#include "World.hpp"

class GameState : public State {
   public:
    GameState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);
    void save();
    Config::GameLevel::Type getGameType() const;

   private:
    World mWorld;
    Player& mPlayer;
    std::vector<int>* mHighScores;
};

#endif  // GAME_STATE_HPP
