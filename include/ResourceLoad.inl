#include "ResourceIdentifiers.hpp"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadTextureFromFile() {
    /***************************Load Animal Textures***************************/
    // load(
    //     Textures::BeeToLeft,
    //     "asset/game_textures/Animal/Bee/S_Walk_ToLeft.png"
    // );
    // load(
    //     Textures::BeeToRight,
    //     "asset/game_textures/Animal/Bee/S_Walk_ToRight.png"
    // );
    // load(
    //     Textures::BeeIdle, "asset/game_textures/Animal/Bee/D_Walk.png"
    // );

    // load(
    //     Textures::BirdToLeft,
    //     "asset/game_textures/Animal/Bird1/S_Fly_ToLeft.png"
    // );
    // load(
    //     Textures::BirdToRight,
    //     "asset/game_textures/Animal/Bird1/S_Fly_ToRight.png"
    // );
    // load(
    //     Textures::BirdIdle, "asset/game_textures/Animal/Bird1/S_Idle.png"
    // );

    // load(
    //     Textures::FrogToLeft,
    //     "asset/game_textures/Animal/Frog/S_Walk_ToLeft.png"
    // );
    // load(
    //     Textures::FrogToRight,
    //     "asset/game_textures/Animal/Frog/S_Walk_ToRight.png"
    // );
    // load(
    //     Textures::FrogIdle, "asset/game_textures/Animal/Frog/S_Idle.png"
    // );

    // load(
    //     Textures::RabbitToLeft,
    //     "asset/game_textures/Animal/Rabbit/S_Walk_ToLeft.png"
    // );
    // load(
    //     Textures::RabbitToRight,
    //     "asset/game_textures/Animal/Rabbit/S_Walk_ToRight.png"
    // );
    // load(
    //     Textures::RabbitIdle, "asset/game_textures/Animal/Rabbit/S_Idle.png"
    // );

    // load(
    //     Textures::SheepToLeft,
    //     "asset/game_textures/Animal/Sheep/S_Walk_ToLeft.png"
    // );
    // load(
    //     Textures::SheepToRight,
    //     "asset/game_textures/Animal/Sheep/S_Walk_ToRight.png"
    // );
    // load(
    //     Textures::SheepIdle, "asset/game_textures/Animal/Sheep/S_Idle.png"
    // );

    // load(
    //     Textures::TurtleToLeft,
    //     "asset/game_textures/Animal/Turtle/S_Walk_ToLeft.png"
    // );
    // load(
    //     Textures::TurtleToRight,
    //     "asset/game_textures/Animal/Turtle/S_Walk_ToRight.png"
    // );
    // load(
    //     Textures::TurtleIdle,
    //     "asset/game_textures/Animal/Turtle/S_Attack.png"
    // );

    /*************************************************************************/

    /***********************Load TrafficLight Textures***********************/
    load(
        Textures::Field_TrafficLight,
        "asset/game_textures/TrafficLight/Field_TrafficLight.png"
    );
    load(
        Textures::Graveyard_TrafficLight,
        "asset/game_textures/TrafficLight/Graveyard_TrafficLight.png"
    );
    load(
        Textures::Swamp_TrafficLight,
        "asset/game_textures/TrafficLight/Swamp_TrafficLight.png"
    );
    /*************************************************************************/

    /***********************Load Enemy Textures****************************/
    load(
        Textures::BeeBossToLeft,
        "asset/game_textures/Enemy/BeeBoss/S_Fly_ToLeft.png"
    );
    load(
        Textures::BeeBossToRight,
        "asset/game_textures/Enemy/BeeBoss/S_Fly_ToRight.png"
    );
    load(
        Textures::BeeBossIdle,
        "asset/game_textures/Enemy/BeeBoss/Special_Idle.png"
    );

    load(
        Textures::BombBatToLeft,
        "asset/game_textures/Enemy/BombBat/S_Fly_ToLeft.png"
    );
    load(
        Textures::BombBatToRight,
        "asset/game_textures/Enemy/BombBat/S_Fly_ToRight.png"
    );
    load(Textures::BombBatIdle, "asset/game_textures/Enemy/BombBat/D_Fly.png");

    load(
        Textures::CrocodileToLeft,
        "asset/game_textures/Enemy/Crocodile/S_Walk_ToLeft.png"
    );
    load(
        Textures::CrocodileToRight,
        "asset/game_textures/Enemy/Crocodile/S_Walk_ToRight.png"
    );
    load(
        Textures::CrocodileIdle,
        "asset/game_textures/Enemy/Crocodile/S_Attack.png"
    );

    load(
        Textures::DogToLeft, "asset/game_textures/Enemy/Dog/S_Walk_ToLeft.png"
    );
    load(
        Textures::DogToRight, "asset/game_textures/Enemy/Dog/S_Walk_ToRight.png"
    );
    load(Textures::DogIdle, "asset/game_textures/Enemy/Dog/S_Attack.png");

    load(
        Textures::FishmenToLeft,
        "asset/game_textures/Enemy/Fishmen/S_Walk_ToLeft.png"
    );
    load(
        Textures::FishmenToRight,
        "asset/game_textures/Enemy/Fishmen/S_Walk_ToRight.png"
    );
    load(Textures::FishmenIdle, "asset/game_textures/Enemy/Fishmen/S_Swim.png");

    load(
        Textures::OrcToLeft, "asset/game_textures/Enemy/Orc/S_Walk_ToLeft.png"
    );
    load(
        Textures::OrcToRight, "asset/game_textures/Enemy/Orc/S_Walk_ToRight.png"
    );
    load(Textures::OrcIdle, "asset/game_textures/Enemy/Orc/D_Special.png");

    load(
        Textures::WraithToLeft,
        "asset/game_textures/Enemy/Wraith/S_Walk_ToLeft.png"
    );
    load(
        Textures::WraithToRight,
        "asset/game_textures/Enemy/Wraith/S_Walk_ToRight.png"
    );
    load(Textures::WraithIdle, "asset/game_textures/Enemy/Wraith/S_Idle.png");

    load(
        Textures::WraithProToLeft,
        "asset/game_textures/Enemy/WraithPro/S_Walk_ToLeft.png"
    );
    load(
        Textures::WraithProToRight,
        "asset/game_textures/Enemy/WraithPro/S_Walk_ToRight.png"
    );
    load(
        Textures::WraithProIdle,
        "asset/game_textures/Enemy/WraithPro/S_Idle.png"
    );

    load(
        Textures::WraithSwampToLeft,
        "asset/game_textures/Enemy/WraithSwamp/S_Walk_ToLeft.png"
    );
    load(
        Textures::WraithSwampToRight,
        "asset/game_textures/Enemy/WraithSwamp/S_Walk_ToRight.png"
    );
    load(
        Textures::WraithSwampIdle,
        "asset/game_textures/Enemy/WraithSwamp/S_Idle.png"
    );

    load(
        Textures::GolemGyToLeft,
        "asset/game_textures/Enemy/GolemGy/S_Walk_ToLeft.png"
    );
    load(
        Textures::GolemGyToRight,
        "asset/game_textures/Enemy/GolemGy/S_Walk_ToRight.png"
    );
    load(Textures::GolemGyIdle, "asset/game_textures/Enemy/GolemGy/S_Idle.png");

    load(
        Textures::GolemToLeft,
        "asset/game_textures/Enemy/Golem/S_Walk_ToLeft.png"
    );
    load(
        Textures::GolemToRight,
        "asset/game_textures/Enemy/Golem/S_Walk_ToRight.png"
    );
    load(Textures::GolemIdle, "asset/game_textures/Enemy/Golem/S_Idle.png");

    load(
        Textures::GolemSwampToLeft,
        "asset/game_textures/Enemy/GolemSwamp/S_Walk_ToLeft.png"
    );
    load(
        Textures::GolemSwampToRight,
        "asset/game_textures/Enemy/GolemSwamp/S_Walk_ToRight.png"
    );
    load(
        Textures::GolemSwampIdle,
        "asset/game_textures/Enemy/GolemSwamp/S_Idle.png"
    );

    load(
        Textures::SatyrGyToLeft,
        "asset/game_textures/Enemy/SatyrGy/S_Walk_ToLeft.png"
    );
    load(
        Textures::SatyrGyToRight,
        "asset/game_textures/Enemy/SatyrGy/S_Walk_ToRight.png"
    );
    load(Textures::SatyrGyIdle, "asset/game_textures/Enemy/SatyrGy/S_Idle.png");

    load(
        Textures::SatyrToLeft,
        "asset/game_textures/Enemy/Satyr/S_Walk_ToLeft.png"
    );
    load(
        Textures::SatyrToRight,
        "asset/game_textures/Enemy/Satyr/S_Walk_ToRight.png"
    );
    load(Textures::SatyrIdle, "asset/game_textures/Enemy/Satyr/S_Idle.png");

    load(
        Textures::SatyrSwampToLeft,
        "asset/game_textures/Enemy/SatyrSwamp/S_Walk_ToLeft.png"
    );
    load(
        Textures::SatyrSwampToRight,
        "asset/game_textures/Enemy/SatyrSwamp/S_Walk_ToRight.png"
    );
    load(
        Textures::SatyrSwampIdle,
        "asset/game_textures/Enemy/SatyrSwamp/S_Idle.png"
    );

    load(
        Textures::MinoGyToLeft,
        "asset/game_textures/Enemy/MinoGy/S_Walk_ToLeft.png"
    );
    load(
        Textures::MinoGyToRight,
        "asset/game_textures/Enemy/MinoGy/S_Walk_ToRight.png"
    );
    load(Textures::MinoGyIdle, "asset/game_textures/Enemy/MinoGy/S_Idle.png");

    load(
        Textures::MinoToLeft, "asset/game_textures/Enemy/Mino/S_Walk_ToLeft.png"
    );
    load(
        Textures::MinoToRight,
        "asset/game_textures/Enemy/Mino/S_Walk_ToRight.png"
    );
    load(Textures::MinoIdle, "asset/game_textures/Enemy/Mino/S_Idle.png");

    load(
        Textures::MinoSwampToLeft,
        "asset/game_textures/Enemy/MinoSwamp/S_Walk_ToLeft.png"
    );
    load(
        Textures::MinoSwampToRight,
        "asset/game_textures/Enemy/MinoSwamp/S_Walk_ToRight.png"
    );
    load(
        Textures::MinoSwampIdle,
        "asset/game_textures/Enemy/MinoSwamp/S_Idle.png"
    );

    /*************************************************************************/

    /**************************Load Lane Textures******************************/
    load(Textures::Dirt, "asset/game_textures/Lane/Dirt.png");
    load(Textures::Grass, "asset/game_textures/Lane/Grass.png");
    load(Textures::Graveyard, "asset/game_textures/Lane/Graveyard.png");
    load(Textures::Soil, "asset/game_textures/Lane/Soil.png");
    load(Textures::Swamp, "asset/game_textures/Lane/Swamp.png");
    load(Textures::River, "asset/game_textures/Lane/River.png");
    /*************************************************************************/

    /**************************Load Skin Textures************************/
    load(
        Textures::ArcherToLeft,
        "asset/game_textures/Skin/Archer/Walk_ToLeft.png"
    );
    load(
        Textures::ArcherToRight,
        "asset/game_textures/Skin/Archer/Walk_ToRight.png"
    );
    load(Textures::ArcherIdle, "asset/game_textures/Skin/Archer/Idle.png");
    load(Textures::ArcherDead, "asset/game_textures/Skin/Archer/Dead.png");

    load(
        Textures::EnchantressToLeft,
        "asset/game_textures/Skin/Enchantress/Walk_ToLeft.png"
    );
    load(
        Textures::EnchantressToRight,
        "asset/game_textures/Skin/Enchantress/Walk_ToRight.png"
    );
    load(
        Textures::EnchantressIdle,
        "asset/game_textures/Skin/Enchantress/Idle.png"
    );
    load(
        Textures::EnchantressDead,
        "asset/game_textures/Skin/Enchantress/Dead.png"
    );

    load(
        Textures::KnightToLeft,
        "asset/game_textures/Skin/Knight/Walk_ToLeft.png"
    );
    load(
        Textures::KnightToRight,
        "asset/game_textures/Skin/Knight/Walk_ToRight.png"
    );
    load(Textures::KnightIdle, "asset/game_textures/Skin/Knight/Idle.png");
    load(Textures::KnightDead, "asset/game_textures/Skin/Knight/Dead.png");

    load(
        Textures::MusketeerToLeft,
        "asset/game_textures/Skin/Musketeer/Walk_ToLeft.png"
    );
    load(
        Textures::MusketeerToRight,
        "asset/game_textures/Skin/Musketeer/Walk_ToRight.png"
    );
    load(
        Textures::MusketeerIdle, "asset/game_textures/Skin/Musketeer/Idle.png"
    );
    load(
        Textures::MusketeerDead, "asset/game_textures/Skin/Musketeer/Dead.png"
    );

    load(
        Textures::SwordsmanToLeft,
        "asset/game_textures/Skin/Swordsman/Walk_ToLeft.png"
    );
    load(
        Textures::SwordsmanToRight,
        "asset/game_textures/Skin/Swordsman/Walk_ToRight.png"
    );
    load(
        Textures::SwordsmanIdle, "asset/game_textures/Skin/Swordsman/Idle.png"
    );
    load(
        Textures::SwordsmanDead, "asset/game_textures/Skin/Swordsman/Dead.png"
    );

    load(
        Textures::WizardToLeft,
        "asset/game_textures/Skin/Wizard/Walk_ToLeft.png"
    );
    load(
        Textures::WizardToRight,
        "asset/game_textures/Skin/Wizard/Walk_ToRight.png"
    );
    load(Textures::WizardIdle, "asset/game_textures/Skin/Wizard/Idle.png");
    load(Textures::WizardDead, "asset/game_textures/Skin/Wizard/Dead.png");
    /***********************************************************************/

    /**************************Load Other Textures**************************/

    /*<------------------------Field Textures--------------------------->*/
    load(
        Textures::Field_Bush2,
        "asset/game_textures/Obstacle/Field/Bush/Bush2.png"
    );
    load(
        Textures::Field_Lamp1,
        "asset/game_textures/Obstacle/Field/Lamp/Lamp1.png"
    );
    load(
        Textures::Field_Stone6,
        "asset/game_textures/Obstacle/Field/Stone/Stone6.png"
    );
    load(
        Textures::Field_Tent3,
        "asset/game_textures/Obstacle/Field/Tent/Tent3.png"
    );
    load(
        Textures::Field_Tree1,
        "asset/game_textures/Obstacle/Field/Tree/Tree1.png"
    );
    /*<------------------------Field Textures--------------------------->*/

    /*<------------------------Graveyard Textures--------------------------->*/
    load(
        Textures::Graveyard_House1,
        "asset/game_textures/Obstacle/Graveyard/House/House1.png"
    );
    load(
        Textures::Graveyard_Statue8,
        "asset/game_textures/Obstacle/Graveyard/Statue/Statue8.png"
    );
    load(
        Textures::Graveyard_Tree2,
        "asset/game_textures/Obstacle/Graveyard/Tree/Tree2.png"
    );
    /*<------------------------Graveyard Textures--------------------------->*/

    /*<------------------------Swamp Textures--------------------------->*/
    load(
        Textures::Swamp_House1,
        "asset/game_textures/Obstacle/Swamp/House/House1.png"
    );
    load(
        Textures::Swamp_Tree2,
        "asset/game_textures/Obstacle/Swamp/Tree/Tree2.png"
    );
    load(
        Textures::Swamp_Well1,
        "asset/game_textures/Obstacle/Swamp/Well/Well1.png"
    );
    /*<------------------------Swamp Textures--------------------------->*/

    /*<------------------------River Textures--------------------------->*/
    load(
        Textures::River_Log1, "asset/game_textures/Obstacle/River/Log/Log2.png"
    );
    /*<------------------------River Textures--------------------------->*/
    // Common
    load(Textures::BackgroundMain, "asset/textures/BackgroundMain.png");
    load(Textures::ButtonBack, "asset/textures/ButtonBack.png");
    load(Textures::ButtonHome, "asset/textures/ButtonHome.png");
    load(Textures::ButtonLevel, "asset/textures/ButtonLevel.png");
    load(Textures::ButtonPlayAgain, "asset/textures/ButtonPlayAgain.png");
    load(Textures::ButtonSetting, "asset/textures/ButtonSetting.png");
    load(Textures::ButtonResume, "asset/textures/ButtonResume.png");

    // Skin (serve for GUI)
    load(Textures::SkinArcher, "asset/textures/SkinArcher.png");
    load(Textures::SkinEnchantress, "asset/textures/SkinEnchantress.png");
    load(Textures::SkinKnight, "asset/textures/SkinKnight.png");
    load(Textures::SkinMusketeer, "asset/textures/SkinMusketeer.png");
    load(Textures::SkinSwordsman, "asset/textures/SkinSwordsman.png");
    load(Textures::SkinWizard, "asset/textures/SkinWizard.png");

    // Setting state
    load(Textures::BackgroundSetting, "asset/textures/BackgroundSetting.png");
    load(Textures::DialogCommon, "asset/textures/DialogCommon.png");
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
    load(Textures::ButtonAdd, "asset/textures/daucong.png");
    load(Textures::ButtonSub, "asset/textures/dautru.png");
    load(Textures::ButtonConfirm, "asset/textures/ButtonConfirm.png");
    load(Textures::ChosenMusic, "asset/textures/mOpMain.png");
    load(Textures::OptionMusic, "asset/textures/mOpSub.png");

    // Credit state
    load(Textures::BackgroundCredit, "asset/textures/BackgroundCredit.png");

    // Win state
    load(Textures::DialogVictory, "asset/textures/DialogVictory.png");

    // Lose state
    load(Textures::ButtonHomeLose, "asset/textures/ButtonHomeLose.png");
    load(Textures::DialogDefeat, "asset/textures/DialogDefeat.png");

    // Pause state
    load(Textures::BackgroundPause, "asset/textures/BackgroundPause.png");
    load(Textures::ButtonSaveGame, "asset/textures/ButtonSaveGame.png");
    load(Textures::ButtonResumePause, "asset/textures/ButtonResumePause.png");
    load(
        Textures::ButtonPlayAgainPause,
        "asset/textures/ButtonPlayAgainPause.png"
    );

    // Menu State
    load(Textures::BackgroundMenu, "asset/textures/BackgroundMenu.png");
    load(Textures::ButtonPlay, "asset/textures/ButtonPlay.png");
    load(Textures::ButtonContinue, "asset/textures/ButtonContinue.png");
    load(Textures::ButtonRanking, "asset/textures/ButtonRanking.png");
    load(Textures::ButtonSettingMenu, "asset/textures/ButtonSettingMenu.png");
    load(Textures::ButtonCredit, "asset/textures/ButtonCredit.png");

    // Ranking State
    load(Textures::BackgroundRanking, "asset/textures/BackgroundRanking.png");

    // Level State
    load(Textures::BackgroundLevel, "asset/textures/BackgroundLevel.png");
    load(Textures::BarLevel, "asset/textures/BarLevel.png");

    // Saved State
    load(Textures::BackgroundSaved, "asset/textures/BackgroundSaved.png");
    load(Textures::BarSaved, "asset/textures/BarSaved.png");

    // Chose Mode State
    load(Textures::ButtonLevelMenu, "asset/textures/ButtonLevelMenu.png");
    load(Textures::ButtonSurvivalMenu, "asset/textures/ButtonSurvivalMenu.png");
    load(Textures::ButtonBackMenu, "asset/textures/ButtonBackMenu.png");
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadFontFromFile() {
    load(Fonts::Main, "asset/font/Inter-Bold.ttf");
}
