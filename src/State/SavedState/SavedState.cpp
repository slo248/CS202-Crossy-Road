#include "SavedState.hpp"

#include "ResourceHolder.hpp"

SavedState::SavedState(StateStack& stack, Context context)
    : State(stack, context),
      mBackground(context.textures->get(Textures::BackgroundSaved)) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    buttonBack->setCallback(std::bind(&SavedState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);

    int numSaved = 7;
    for (int i = 0; i < numSaved; ++i) {
        auto barSaved = std::make_shared<Button>(
            context, Textures::BarSaved, sf::Vector2f(35, 165 + 53 * i)
        );
        mGUIContainer.pack(barSaved);
    }
}

void SavedState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool SavedState::update(sf::Time dt) { return true; }

bool SavedState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
