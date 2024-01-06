#include "MenuState.hpp"

#include "Config.hpp"

#define ORIGIN_X 584.f
#define ORIGIN_Y 267.f

MenuState::MenuState(StateStack& stack, Context& context)
    : mBackground(context.textures->get(Textures::BackgroundMenu)),
      State(stack, context) {
    auto buttonPlay = std::make_shared<Button>(
        context, Textures::ButtonPlay, sf::Vector2f(ORIGIN_X, ORIGIN_Y)
    );
    buttonPlay->setCallback([this]() {
        mContext->mode = Config::ChooseModeState::NewGame;
        requestStackPush(States::ChooseMode);
    });
    mGUIContainer.pack(buttonPlay);

    auto buttonContinue = std::make_shared<Button>(
        context, Textures::ButtonContinue, sf::Vector2f(ORIGIN_X, ORIGIN_Y + 53.f)
    );
    buttonContinue->setCallback([this]() {
        mContext->mode = Config::ChooseModeState::Continue;
        requestStackPush(States::ChooseMode);
    });
    mGUIContainer.pack(buttonContinue);

    auto buttonRanking = std::make_shared<Button>(
        context, Textures::ButtonRanking, sf::Vector2f(ORIGIN_X, ORIGIN_Y + 106.f)
    );
    buttonRanking->setCallback([this]() { requestStackPush(States::Ranking); });
    mGUIContainer.pack(buttonRanking);

    auto buttonSettingMenu = std::make_shared<Button>(
        context, Textures::ButtonSettingMenu, sf::Vector2f(ORIGIN_X, ORIGIN_Y + 159.f)
    );
    buttonSettingMenu->setCallback([this]() {
        mContext->musics->setPaused();
        mContext->mode = Config::SettingState::Skin;
        requestStackPush(States::Setting);
    });
    mGUIContainer.pack(buttonSettingMenu);

    auto buttonCredit = std::make_shared<Button>(
        context, Textures::ButtonCredit, sf::Vector2f(ORIGIN_X, ORIGIN_Y + 212.f)
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
