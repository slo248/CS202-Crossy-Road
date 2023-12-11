#ifndef RANKING_STATE_HPP
#define RANKING_STATE_HPP
#include "Button.hpp"
#include "State.hpp"

class RankingState : public State {
   public:
    RankingState(StateStack& stack, Context context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
};

#endif
