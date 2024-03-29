#include "DialogSkin.hpp"

#include "DialogSuccess.hpp"
#include "ResourceHolder.hpp"

#define something 4

DialogSkin::DialogSkin(const sf::Texture& texture, State::Context& context)
    : Dialog(texture, context), mCurrentSkin(context.playerSkinNumber) {
    mSprite.setPosition(13.f, 112.f);

    auto mButtonLeft = std::make_shared<Button>(
        context, Textures::ButtonLeftArrow, sf::Vector2f(288, 288), true
    );
    mButtonLeft->setCallback([this, mButtonLeft]() {
        if (mButtonLeft->isSelected()) {
            mButtonLeft->deselect();
        }

        changeSkin(--mCurrentSkin);
    });
    mGUIContainer.pack(mButtonLeft);

    auto mButtonRight = std::make_shared<Button>(
        context, Textures::ButtonRightArrow, sf::Vector2f(531, 288), true
    );
    mButtonRight->setCallback([this, mButtonRight]() {
        if (mButtonRight->isSelected()) {
            mButtonRight->deselect();
        }

        changeSkin(++mCurrentSkin);
    });
    mGUIContainer.pack(mButtonRight);

    auto mButtonConfirm = std::make_shared<Button>(
        context, Textures::ButtonConfirm, sf::Vector2f(382, 499)
    );
    mButtonConfirm->setCallback([this]() {
        mContext->playerSkinNumber = mCurrentSkin;
        mDialogSuccess->activate();
    });
    mGUIContainer.pack(mButtonConfirm);

    mDialogSuccess = std::make_shared<DialogSuccess>(
        mContext->textures->get(Textures::DialogSuccess), *mContext
    );
    mGUIContainer.pack(mDialogSuccess);

    int skin = Textures::ArcherIdle;
    for (int i = 0; i < mNumSkins; ++i) {
        addSkins(
            mSkins, i, sf::Vector2f(212 + i * 92, 406), sf::Vector2i(42, 38),
            static_cast<Textures::ID>(skin + 4 * i)
        );
    }

    int chosenSkin = Textures::SkinArcher;
    for (int i = 0; i < mNumSkins; ++i) {
        addSkins(
            mChosenSkins, i, sf::Vector2f(445, 230), sf::Vector2i(256, 258),
            static_cast<Textures::ID>(chosenSkin + i)
        );
    }
}

void DialogSkin::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    Dialog::draw(target, states);

    for (int i = 0; i < mNumSkins; ++i) {
        target.draw(*mSkins[i], states);
    }

    target.draw(*mChosenSkins[mCurrentSkin], states);
    target.draw(mGUIContainer, states);
}

void DialogSkin::handleEvent(const sf::Event& event) {
    if (mDialogSuccess && mDialogSuccess->isActive()) {
        mDialogSuccess->handleEvent(event);
        return;
    }

    mGUIContainer.handleEvent(event);
}

void DialogSkin::update(sf::Time dt) {
    for (int i = 0; i < mNumSkins; ++i) {
        mSkins[i]->update(dt);
        mChosenSkins[i]->update(dt);
    }
}

void DialogSkin::addSkins(
    std::array<Animation::Ptr, NUMBER_OF_SKINS>& mSkins, int skinNumber,
    sf::Vector2f position, sf::Vector2i frameSize, Textures::ID skin
) {
    mSkins[skinNumber] =
        std::make_unique<Animation>(mContext->textures->get(skin), frameSize);

    mSkins[skinNumber]->setPosition(position.x, position.y);
    mSkins[skinNumber]->play();
    mSkins[skinNumber]->setRepeat(true);
}

void DialogSkin::changeSkin(int skinNumber) {
    mCurrentSkin = skinNumber % mNumSkins;

    if (mCurrentSkin < 0) {
        mCurrentSkin += mNumSkins;
    }
}
