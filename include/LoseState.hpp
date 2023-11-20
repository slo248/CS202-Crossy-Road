#ifndef LOSE_STATE_HPP
#define LOSE_STATE_HPP


#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"

class LoseState : public State {
    public:
     LoseState(StateStack& stack, Context context);
    
     virtual void draw();
     virtual bool update(sf::Time dt);
     virtual bool handleEvent(const sf::Event& event);
    
    private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mDefeatDialog;
    Container mGUIContainer;

};

#endif
