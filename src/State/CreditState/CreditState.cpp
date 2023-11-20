#include "CreditState.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

CreditState::CreditState(StateStack& stack, Context context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::CreditBackground)) {
    backButton =
        std::make_shared<Button>(context, Textures::BackButton, sf::Vector2f(1065.f, 6.f));
    backButton->setCallback(std::bind(&CreditState::requestStackPop, this));
    mGUIContainer.pack(backButton);
}

void CreditState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}
bool CreditState::update(sf::Time dt) { return true; }

bool CreditState::handleEvent(const sf::Event& event) {
    if (backButton->isMouseOver(*getContext().window) && event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        backButton->select();
    }
    
    mGUIContainer.handleEvent(event);
    return false;
}
