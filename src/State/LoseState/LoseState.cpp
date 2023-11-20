#include "LoseState.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

LoseState::LoseState(StateStack& stack, Context context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMain)),
      mDefeatDialog(context.textures->get(Textures::DialogDefeat)) {
    mDefeatDialog.setPosition(225.f, 103.f);
}

void LoseState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mDefeatDialog);
    window.draw(mGUIContainer);
}
bool LoseState::update(sf::Time dt) { return true; }
bool LoseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
