#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include "Button.hpp"
#include "Label.hpp"
#include "State.hpp"

class LevelState : public State {
   public:
    enum Mode { Play, Continue };
    LevelState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
    Mode mMode;
    void addButtonLevel(int numLevel);
};

#endif
