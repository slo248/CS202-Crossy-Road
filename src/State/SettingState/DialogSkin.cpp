#include "DialogSkin.hpp"

#include "ResourceHolder.hpp"

DialogSkin::DialogSkin(const sf::Texture& texture, State::Context& context)
    : Dialog(texture, context) {
    mSprite.setPosition(13.f, 112.f);

    mButtonLeft = std::make_shared<Button>(
        context, Textures::ButtonLeftArrow, sf::Vector2f(288, 288), true
    );
    mButtonLeft->setCallback([this]() { changeSkin(--mCurrentSkin); });
    mGUIContainer.pack(mButtonLeft);

    mButtonRight = std::make_shared<Button>(
        context, Textures::ButtonRightArrow, sf::Vector2f(531, 288), true
    );
    mButtonRight->setCallback([this]() { changeSkin(++mCurrentSkin); });
    mGUIContainer.pack(mButtonRight);

    auto mButtonConfirm = std::make_shared<Button>(
        context, Textures::ButtonConfirm, sf::Vector2f(382, 499)
    );
    mButtonConfirm->setCallback([this]() {
        mContext->playerSkinNumber = mCurrentSkin;
    });
    mGUIContainer.pack(mButtonConfirm);

    int skin = Textures::ArcherIdle;
    for (int i = 0; i < mNumSkins; ++i) {
        addSkins(
            i, sf::Vector2f(212 + i * 92, 406), sf::Vector2i(42, 38),
            static_cast<Textures::ID>(skin + 4 * i)
        );
    }

    int chosenSkin = Textures::SkinArcher;
    for (int i = 0; i < mNumSkins; ++i) {
        addChosenSkins(
            i, sf::Vector2f(445, 230), sf::Vector2i(256, 258),
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
    if (mButtonLeft->isSelected() || mButtonRight->isSelected()) {
        mButtonLeft->deselect();
        mButtonRight->deselect();
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
    int i, sf::Vector2f position, sf::Vector2i frameSize, Textures::ID skin
) {
    mSkins[i] =
        std::make_unique<Animation>(mContext->textures->get(skin), frameSize);

    mSkins[i]->setPosition(position.x, position.y);
    mSkins[i]->play();
    mSkins[i]->setRepeat(true);
}

void DialogSkin::addChosenSkins(
    int i, sf::Vector2f position, sf::Vector2i frameSize, Textures::ID skin
) {
    mChosenSkins[i] =
        std::make_unique<Animation>(mContext->textures->get(skin), frameSize);

    mChosenSkins[i]->setPosition(position.x, position.y);
    mChosenSkins[i]->play();
    mChosenSkins[i]->setRepeat(true);
}

void DialogSkin::changeSkin(int i) {
    mCurrentSkin = i % mNumSkins;

    if (mCurrentSkin < 0) {
        mCurrentSkin += mNumSkins;
    }
}
