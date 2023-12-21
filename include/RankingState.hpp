#ifndef RANKING_STATE_HPP
#define RANKING_STATE_HPP

#include "Button.hpp"
#include "Label.hpp"
#include "State.hpp"

class RankingState : public State {
   public:
    RankingState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
};

#endif
