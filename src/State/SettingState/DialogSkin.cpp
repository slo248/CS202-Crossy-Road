#include "DialogSkin.hpp"

#include "ResourceHolder.hpp"

DialogSkin::DialogSkin(const sf::Texture& texture, State::Context& context)
    : Dialog(texture, context) {
    mSprite.setPosition(13.f, 112.f);

    mButtonLeft = std::make_shared<Button>(
        context, Textures::ButtonLeftArrow, sf::Vector2f(241, 288), true
    );
    mGUIContainer.pack(mButtonLeft);

    mButtonRight = std::make_shared<Button>(
        context, Textures::ButtonRightArrow, sf::Vector2f(600, 288), true
    );
    mGUIContainer.pack(mButtonRight);

    auto mButtonConfirm = std::make_shared<Button>(
        context, Textures::ButtonConfirm, sf::Vector2f(382, 499)
    );
    mGUIContainer.pack(mButtonConfirm);

    int skin = Textures::ArcherIdle;
    for (int i = 0; i < mNumSkins; ++i) {
        addSkins(
            i, 212 + i * 92, static_cast<Textures::ID>(skin + 4 * i), context
        );
    }

    mChosenSkin = std::make_unique<Animation>(
        context.textures->get(Textures::SkinArcher), sf::Vector2i(97, 129), 6
    );
    mChosenSkin->setPosition(405, 236);
    mChosenSkin->play();
    mChosenSkin->setRepeat(true);
}

void DialogSkin::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    Dialog::draw(target, states);

    for (int i = 0; i < mNumSkins; ++i) {
        target.draw(*mSkins[i], states);
    }

    target.draw(*mChosenSkin, states);
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
    }
}

void DialogSkin::addSkins(
    int i, float x, Textures::ID skin, State::Context& context
) {
    mSkins[i] = std::make_unique<Animation>(
        context.textures->get(skin), sf::Vector2i(42, 38), 6
    );

    mSkins[i]->setPosition(x, 406.f);
    mSkins[i]->play();
    mSkins[i]->setRepeat(true);
}
