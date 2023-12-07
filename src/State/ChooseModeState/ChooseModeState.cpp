#include "ChooseModeState.hpp"

#include "ResourceHolder.hpp"

ChooseModeState::ChooseModeState(StateStack& stack, Context context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMenu)) {
    auto buttonBackMenu = std::make_shared<Button>(
        context, Textures::ButtonBackMenu, sf::Vector2f(874, 640)
    );
    buttonBackMenu->setCallback(std::bind(&ChooseModeState::requestStackPop, this));
    mGUIContainer.pack(buttonBackMenu);

    auto buttonLevelMenu = std::make_shared<Button>(
        context, Textures::ButtonLevelMenu, sf::Vector2f(874, 480)
    );
    buttonLevelMenu->setCallback([this]() { requestStackPush(States::Level); });
    mGUIContainer.pack(buttonLevelMenu);

    auto buttonSurvivalMenu = std::make_shared<Button>(
        context, Textures::ButtonSurvivalMenu, sf::Vector2f(874, 560)
    );
    buttonSurvivalMenu->setCallback([this]() { requestStackPush(States::ChooseMode); });
    mGUIContainer.pack(buttonSurvivalMenu);
}

void ChooseModeState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer); 
}
bool ChooseModeState::update(sf::Time dt) { return true; }

bool ChooseModeState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
