#include "MenuState.hpp"

#include "Config.hpp"

MenuState::MenuState(StateStack& stack, Context& context)
    : mBackground(context.textures->get(Textures::BackgroundMenu)),
      State(stack, context) {
    auto buttonPlay = std::make_shared<Button>(
        context, Textures::ButtonPlay, sf::Vector2f(584, 267)
    );
    buttonPlay->setCallback([this]() {
        mContext->mode = Config::ChooseModeState::NewGame;
        requestStackPush(States::ChooseMode);
    });
    mGUIContainer.pack(buttonPlay);

    auto buttonContinue = std::make_shared<Button>(
        context, Textures::ButtonContinue, sf::Vector2f(584, 320)
    );
    buttonContinue->setCallback([this]() {
        // problematic
        mContext->mode = Config::ChooseModeState::Continue;
        requestStackPush(States::ChooseMode);
    });
    mGUIContainer.pack(buttonContinue);

    auto buttonRanking = std::make_shared<Button>(
        context, Textures::ButtonRanking, sf::Vector2f(584, 373)
    );
    buttonRanking->setCallback([this]() { requestStackPush(States::Ranking); });
    mGUIContainer.pack(buttonRanking);

    auto buttonSettingMenu = std::make_shared<Button>(
        context, Textures::ButtonSettingMenu, sf::Vector2f(584, 426)
    );
    buttonSettingMenu->setCallback([this]() {
        // problematic
        mContext->mode = Config::SettingState::Skin;
        requestStackPush(States::Setting);
    });
    mGUIContainer.pack(buttonSettingMenu);

    auto buttonCredit = std::make_shared<Button>(
        context, Textures::ButtonCredit, sf::Vector2f(584, 479)
    );
    buttonCredit->setCallback([this]() { requestStackPush(States::Credit); });
    mGUIContainer.pack(buttonCredit);

    context.musics->play(Musics::Introduction);
}

void MenuState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackground);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt) { return false; }

bool MenuState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
