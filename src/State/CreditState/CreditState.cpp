#include "CreditState.hpp"

#include "ResourceHolder.hpp"

CreditState::CreditState(StateStack& stack, Context context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundCredit)) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(1065.f, 6.f)
    );
    buttonBack->setCallback(std::bind(&CreditState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);
}

void CreditState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}
bool CreditState::update(sf::Time dt) { return true; }

bool CreditState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
