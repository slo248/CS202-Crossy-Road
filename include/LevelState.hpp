#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include "Button.hpp"
#include "Label.hpp"
#include "State.hpp"

class LevelState : public State {
   public:
    LevelState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
    Config::LevelState::Mode mMode;
    void addButtonLevel(int numLevel);
};

#endif
