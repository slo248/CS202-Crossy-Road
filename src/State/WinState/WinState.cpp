#include "WinState.hpp"

#include "GameState.hpp"
#include "Label.hpp"
#include "ResourceHolder.hpp"

WinState::WinState(StateStack& stack, Context& context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMain)),
      mMode(static_cast<Config::WinState::Mode>(context.mode)),
      mDialogVictory(context.textures->get(Textures::DialogVictory)) {
    mDialogVictory.setPosition(211.f, 98.f);
    Button::Ptr buttonHome;

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(810.f, 560.f)
    );
    buttonSetting->setCallback([this]() {
        mContext->mode = Config::SettingState::Skin;
        requestStackPush(States::Setting);
    });

    auto buttonPlayAgain = std::make_shared<Button>(
        context, Textures::ButtonPlayAgain, sf::Vector2f(527.f, 364.f)
    );
    buttonPlayAgain->setCallback([this]() {
        mContext->isLoadedFromFile = false;
        requestStackClear();
        requestStackPush(States::Game);
    });

    if (mMode == Config::WinState::HighScore) {
        std::string score = std::to_string(mContext->currentScore);
        mContext->musics->play(Musics::HighScore, false);

        buttonHome = std::make_shared<Button>(
            context, Textures::ButtonHome2, sf::Vector2f(339.f, 364.f)
        );

        auto labelScore = std::make_shared<Label>(
            "Your score: " + score, Fonts::Main, context, 20
        );
        labelScore->setColor("#5B1010");
        float labelScoreX = 380 - 3 * float(score.length());
        labelScore->setPosition(labelScoreX, 161);
        mGUIContainer.pack(labelScore);

        auto labelHighScore =
            std::make_shared<Label>("HIGH SCORE", Fonts::Main, context, 30);
        labelHighScore->setColor("#5B1010");
        labelHighScore->setPosition(358, 121);
        mGUIContainer.pack(labelHighScore);
    } else {
        mContext->musics->play(Musics::Win, false);
        buttonHome = std::make_shared<Button>(
            context, Textures::ButtonHome, sf::Vector2f(25.f, 560.f)
        );

        auto labelWin =
            std::make_shared<Label>("LEVEL PASSED!", Fonts::Main, context, 25);
        labelWin->setColor("#5B1010");
        labelWin->setPosition(357, 123);
        mGUIContainer.pack(labelWin);

        auto buttonLevel = std::make_shared<Button>(
            context, Textures::ButtonLevel, sf::Vector2f(339.f, 364.f)
        );
        buttonLevel->setCallback([this]() {
            mContext->mode = Config::LevelState::NewGame;
            requestStackPush(States::Level);
        });
        mGUIContainer.pack(buttonLevel);

        auto buttonResume = std::make_shared<Button>(
            context, Textures::ButtonResume, sf::Vector2f(433.f, 364.f)
        );
        buttonResume->setCallback([this]() {
            mContext->isLoadedFromFile = false;
            mContext->gameLevel =
                static_cast<Config::Game::Level>(mContext->gameLevel + 1);
            if (mContext->gameLevel > Config::Game::Level::L5) {
                requestStackClear();
                requestStackPush(States::Menu);
            } else {
                requestStackClear();
                requestStackPush(States::Game);
            }
        });
        mGUIContainer.pack(buttonResume);
    }
    buttonHome->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Menu);
    });

    mGUIContainer.pack(buttonHome);
    mGUIContainer.pack(buttonSetting);
    mGUIContainer.pack(buttonPlayAgain);

    Textures::ID skin = static_cast<Textures::ID>(
        mContext->playerSkinNumber + Textures::SkinArcher
    );
    mPlayerSkin = std::make_unique<Animation>(
        mContext->textures->get(skin), sf::Vector2i(256, 256)
    );

    mPlayerSkin->setPosition(460, 220);
    mPlayerSkin->play();
    mPlayerSkin->setRepeat(true);
}

void WinState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackgroundSprite);
    window.draw(mDialogVictory);
    window.draw(mGUIContainer);
    window.draw(*mPlayerSkin);
}

bool WinState::update(sf::Time dt) {
    mPlayerSkin->update(dt);
    return false;
}

bool WinState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
