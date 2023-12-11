#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf {
class Texture;
class Font;
}  // namespace sf

namespace Fonts {
enum ID {
    Main,
    Enchanted,
};
}

namespace Textures {
enum ID {
    // <----------------Trafic Light------------>
    Field_TrafficLight,
    Graveyard_TrafficLight,
    Swamp_TrafficLight,
    // <----------------Trafic Light------------->

    //////////////////////////////////////////////

    // <----------------Lane-------------------->
    Dirt,
    Grass,
    Graveyard,
    Soil,
    Swamp,
    River,
    // <----------------Lane-------------------->

    /////////////////////////////////////////////

    // // <------------------Animal---------------->
    // BeeToLeft,
    // BeeToRight,
    // BeeIdle,

    // BirdToLeft,
    // BirdToRight,
    // BirdIdle,

    // FrogToLeft,
    // FrogToRight,
    // FrogIdle,

    // RabbitToLeft,
    // RabbitToRight,
    // RabbitIdle,

    // SheepToLeft,
    // SheepToRight,
    // SheepIdle,

    // TurtleToLeft,
    // TurtleToRight,
    // TurtleIdle,
    // // <------------------Animal----------------->

    //////////////////////////////////////////////

    // <-------------------Enemy----------------->
    BeeBossToLeft,
    BeeBossToRight,
    BeeBossIdle,

    BombBatToLeft,
    BombBatToRight,
    BombBatIdle,

    FishmenToLeft,
    FishmenToRight,
    FishmenIdle,

    OrcToLeft,
    OrcToRight,
    OrcIdle,

    CrocodileToLeft,
    CrocodileToRight,
    CrocodileIdle,

    DogToLeft,
    DogToRight,
    DogIdle,

    WraithToLeft,
    WraithToRight,
    WraithIdle,

    WraithProToLeft,
    WraithProToRight,
    WraithProIdle,

    WraithSwampToLeft,
    WraithSwampToRight,
    WraithSwampIdle,

    GolemGyToLeft,
    GolemGyToRight,
    GolemGyIdle,

    GolemToLeft,
    GolemToRight,
    GolemIdle,

    GolemSwampToLeft,
    GolemSwampToRight,
    GolemSwampIdle,

    SatyrGyToLeft,
    SatyrGyToRight,
    SatyrGyIdle,

    SatyrToLeft,
    SatyrToRight,
    SatyrIdle,

    SatyrSwampToLeft,
    SatyrSwampToRight,
    SatyrSwampIdle,

    MinoGyToLeft,
    MinoGyToRight,
    MinoGyIdle,

    MinoToLeft,
    MinoToRight,
    MinoIdle,

    MinoSwampToLeft,
    MinoSwampToRight,
    MinoSwampIdle,

    // callbees,
    // octopus,
    // slime,
    // fullscreen_blind,
    // <-------------------Enemy----------------->

    // <---------------Characters Skin-------------->
    ArcherToLeft,
    ArcherToRight,
    ArcherIdle,
    ArcherDead,

    EnchantressToLeft,
    EnchantressToRight,
    EnchantressIdle,
    EnchantressDead,

    KnightToLeft,
    KnightToRight,
    KnightIdle,
    KnightDead,

    MusketeerToLeft,
    MusketeerToRight,
    MusketeerIdle,
    MusketeerDead,

    SwordsmanToLeft,
    SwordsmanToRight,
    SwordsmanIdle,
    SwordsmanDead,

    WizardToLeft,
    WizardToRight,
    WizardIdle,
    WizardDead,
    // <---------------Characters Skin-------------->

    ////////////////////////////////////////////////

    // <-------------------Obstacle----------------->
    // <----------Field---------->
    Field_Bush2,
    Field_Lamp1,
    Field_Stone6,
    Field_Tent3,
    Field_Tree1,
    // // <----------Field---------->

    ////////////////////////////////////

    // <-----------Graveyard----------->
    Graveyard_House1,
    Graveyard_Statue8,
    Graveyard_Tree2,
    // <----------Graveyard----------->

    ///////////////////////////////////

    // <-----------River-------------->
    River_Log1,
    // <-----------River-------------->

    ///////////////////////////////////

    // <----------Swamp--------------->
    Swamp_Tree2,
    Swamp_House1,
    Swamp_Well1,
    // <----------Swamp--------------->
    // <-------------------Obstacle----------------->

    // <---------------Characters Skin-------------->

    //// GUI
    // Common
    BackgroundMain,
    BackgroundTextbox,
    BackgroundLabel,
    ButtonBack,
    ButtonHome,
    ButtonLevel,
    ButtonPlayAgain,
    ButtonSetting,
    ButtonResume,

    // Skin(serve for GUI)
    SkinArcher,

    // Setting state
    BackgroundSetting,
    DialogCommon,
    ButtonLeftArrow,
    ButtonRightArrow,
    ButtonUpArrow,
    ButtonDownArrow,
    ButtonGeneral,
    ButtonSkin,
    LabelTextConfirm,
    LabelTextKeys,
    LabelTextSounds,
    ButtonSave,
    ButtonSound,
    ButtonMusic,
    ButtonConfirm,
    BarSounds,

    // Credit state
    BackgroundCredit,

    // Menu state
    BackgroundMenu,
    ButtonPlay,
    ButtonContinue,
    ButtonRanking,
    ButtonSettingMenu,
    ButtonCredit,

    // Win state
    DialogVictory,

    // Lose state
    DialogDefeat,

    // Pause state
    BackgroundPause,
    ButtonStar,
    ButtonResumePause,
    ButtonPlayAgainPause,

    // Ranking state
    BackgroundRanking,

    // Level state
    BackgroundLevel,
    BarLevel,

    // Saved state
    BackgroundSaved,
    BarSaved,

    // Chose Mode State
    ButtonLevelMenu,
    ButtonBackMenu,
    ButtonSurvivalMenu,
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif  // RESOURCE_IDENTIFIERS_HPP
