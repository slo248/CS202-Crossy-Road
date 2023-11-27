#include "ResourceIdentifiers.hpp"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadTextureFromFile() {
    // Common
    load(Textures::BackgroundMain, "asset/textures/BackgroundMain.png");
    load(Textures::ButtonBack, "asset/textures/ButtonBack.png");
    load(Textures::ButtonHome, "asset/textures/ButtonHome.png");
    load(Textures::ButtonLevel, "asset/textures/ButtonLevel.png");
    load(Textures::ButtonPlayAgain, "asset/textures/ButtonPlayAgain.png");
    load(Textures::ButtonSetting, "asset/textures/ButtonSetting.png");
    load(Textures::ButtonResume, "asset/textures/ButtonResume.png");

    // Setting state
    load(Textures::BackgroundSetting, "asset/textures/BackgroundSetting.png");
    load(Textures::DialogGeneral, "asset/textures/DialogGeneral.png");
    load(Textures::ButtonLeftArrow, "asset/textures/ButtonLeftArrow.png");
    load(Textures::ButtonRightArrow, "asset/textures/ButtonRightArrow.png");
    load(Textures::ButtonUpArrow, "asset/textures/ButtonUpArrow.png");
    load(Textures::ButtonDownArrow, "asset/textures/ButtonDownArrow.png");
    load(Textures::ButtonGeneral, "asset/textures/ButtonGeneral.png");
    load(Textures::ButtonSkin, "asset/textures/ButtonSkin.png");
    load(Textures::LabelTextKeys, "asset/textures/LabelTextKeys.png");
    load(Textures::LabelTextSounds, "asset/textures/LabelTextSounds.png");
    load(Textures::ButtonSave, "asset/textures/ButtonSave.png");
    load(Textures::ButtonSound, "asset/textures/ButtonSound.png");
    load(Textures::ButtonMusic, "asset/textures/ButtonMusic.png");

    // Credit state
    load(Textures::BackgroundCredit, "asset/textures/BackgroundCredit.png");

    // Win state
    load(Textures::DialogVictory, "asset/textures/DialogVictory.png");

    // Lose state
    load(Textures::DialogDefeat, "asset/textures/DialogDefeat.png");
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadFontFromFile() {
    load(Fonts::Main, "asset/Sansation.ttf");
}
