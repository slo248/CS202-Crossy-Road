#include "LoseState.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

LoseState::LoseState(StateStack& stack, Context context, bool isSurvivalMode)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMain)),
      mDialogDefeat(context.textures->get(Textures::DialogDefeat)) {
    mDialogDefeat.setPosition(200.f, 80.f);
    std::shared_ptr<Button> buttonHome;

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(810.f, 560.f)
    );
    buttonSetting->setCallback([this]() { requestStackPush(States::Setting); });

    auto buttonPlayAgain = std::make_shared<Button>(
        context, Textures::ButtonPlayAgain, sf::Vector2f(485.f, 362.f)
    );
    buttonPlayAgain->setCallback([this]() {
        // requestStackPop();
        // requestStackPush(States::Game);
    });

    if (isSurvivalMode) {
        buttonHome = std::make_shared<Button>(
            context, Textures::ButtonHome, sf::Vector2f(345.f, 362.f)
        );
        buttonHome->setCallback([this]() {
            requestStackClear();
            requestStackPush(States::Menu);
        });
    } else {
        buttonHome = std::make_shared<Button>(
            context, Textures::ButtonHome, sf::Vector2f(25.f, 560.f)
        );
        buttonHome->setCallback([this]() {
            requestStackClear();
            requestStackPush(States::Menu);
        });

        auto buttonLevel = std::make_shared<Button>(
            context, Textures::ButtonLevel, sf::Vector2f(345.f, 362.f)
        );
        buttonLevel->setCallback([this]() { requestStackPush(States::Level); });
        mGUIContainer.pack(buttonLevel);
    }

    mGUIContainer.pack(buttonSetting);
    mGUIContainer.pack(buttonPlayAgain);
    mGUIContainer.pack(buttonHome);
}

void LoseState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mDialogDefeat);
    window.draw(mGUIContainer);
}

bool LoseState::update(sf::Time dt) { return true; }

bool LoseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
