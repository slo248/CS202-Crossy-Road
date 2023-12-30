#include "LoseState.hpp"

#include "Config.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

LoseState::LoseState(StateStack& stack, Context& context)
    : State(stack, context),
      mMode(static_cast<Config::LoseState::Mode>(context.mode)),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMain)),
      mDialogDefeat(context.textures->get(Textures::DialogDefeat)) {
    mDialogDefeat.setPosition(200.f, 80.f);
    Button::Ptr buttonHome;

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(810.f, 560.f)
    );
    buttonSetting->setCallback([this]() {
        mContext->mode = Config::SettingState::Skin;
        requestStackPush(States::Setting);
    });

    auto buttonPlayAgain = std::make_shared<Button>(
        context, Textures::ButtonPlayAgain, sf::Vector2f(485.f, 362.f)
    );
    buttonPlayAgain->setCallback([this]() {
        mContext->isLoadedFromFile = false;
        requestStackClear();
        requestStackPush(States::Game);
    });

    if (mMode == Config::LoseState::Survival) {
        buttonHome = std::make_shared<Button>(
            context, Textures::ButtonHome2, sf::Vector2f(345.f, 362.f)
        );
    } else {
        buttonHome = std::make_shared<Button>(
            context, Textures::ButtonHome, sf::Vector2f(25.f, 560.f)
        );

        auto buttonLevel = std::make_shared<Button>(
            context, Textures::ButtonLevel, sf::Vector2f(345.f, 362.f)
        );
        buttonLevel->setCallback([this]() {
            mContext->mode = Config::LevelState::NewGame;
            requestStackPush(States::Level);
        });
        mGUIContainer.pack(buttonLevel);
    }

    buttonHome->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Menu);
    });

    mGUIContainer.pack(buttonSetting);
    mGUIContainer.pack(buttonPlayAgain);
    mGUIContainer.pack(buttonHome);

    Textures::ID skin = static_cast<Textures::ID>(
        mContext->playerSkinNumber + Textures::DeadArcher
    );
    mPlayerSkin = std::make_unique<Animation>(
        mContext->textures->get(skin), sf::Vector2i(256, 256)
    );

    mPlayerSkin->setPosition(460, 220);
    mPlayerSkin->play();
    mPlayerSkin->setRepeat(false);

    mContext->musics->play(Musics::Lose, false);
}

void LoseState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackgroundSprite);
    window.draw(mDialogDefeat);
    window.draw(mGUIContainer);
    window.draw(*mPlayerSkin);
}

bool LoseState::update(sf::Time dt) {
    mPlayerSkin->update(dt);
    return false;
}

bool LoseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
