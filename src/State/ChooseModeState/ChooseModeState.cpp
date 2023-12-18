#include "ChooseModeState.hpp"

#include "ResourceHolder.hpp"

ChooseModeState::ChooseModeState(StateStack& stack, Context& context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMenu)),
      mMode(static_cast<ChooseModeState::Mode>(context.mode)) {
    auto buttonLevelMenu = std::make_shared<Button>(
        context, Textures::ButtonLevelMenu, sf::Vector2f(584, 320)
    );
    buttonLevelMenu->setCallback([this]() { requestStackPush(States::Level); });
    mGUIContainer.pack(buttonLevelMenu);

    auto buttonSurvivalMenu = std::make_shared<Button>(
        context, Textures::ButtonSurvivalMenu, sf::Vector2f(584, 373)
    );
    // buttonSurvivalMenu->setCallback([this]() {
    //     requestStackPush(States::ChooseMode);
    // });
    mGUIContainer.pack(buttonSurvivalMenu);

    auto buttonBackMenu = std::make_shared<Button>(
        context, Textures::ButtonBackMenu, sf::Vector2f(584, 426)
    );
    buttonBackMenu->setCallback(
        std::bind(&ChooseModeState::requestStackPop, this)
    );
    mGUIContainer.pack(buttonBackMenu);

    // Continue:
    // std::ifstream in(saveGamePath(choice), std::ios::in);
    // context.isLoadFromFile = true;
    // if (!in.good()) {
    //     context.isLoadFromFile = false;
    //     requestStackPush(States::GameState);
    // }
    //
    // in >> context.isLoadFromFile;
    // requestStackPush(States::GameState);
    // in.close();
}

void ChooseModeState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}
bool ChooseModeState::update(sf::Time dt) { return true; }

bool ChooseModeState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
