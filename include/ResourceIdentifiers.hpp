#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf {
class Texture;
class Font;
class Music;
class SoundBuffer;
}  // namespace sf

namespace Fonts {
enum ID {
    Main,
    Enchanted,
};
}

namespace Musics {
enum ID { None, Introduction, Music1, Music2, Music3, MusicCount, Win, HighScore, Lose };
}

namespace SoundEffects {
enum ID {
    ClickButton,
    BombExplode,
    JumpInRiver,
    Log,
    WalkGrass,
    WalkGraveyard,
    WalkSwamp,
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

    // <---------------Weather-------------->
    Rain,
    Snow,
    // <------------------------------------>

    //// GUI
    // Common
    BackgroundMain,
    BackgroundTextbox,
    BackgroundLabel,
    ButtonBack,
    ButtonHome,
    ButtonHome2,
    ButtonLevel,
    ButtonPlayAgain,
    ButtonSetting,
    ButtonResume,

    // Skin(serve for GUI)
    SkinArcher,
    SkinEnchantress,
    SkinKnight,
    SkinMusketeer,
    SkinSwordsman,
    SkinWizard,

    // Setting state
    BackgroundSetting,
    DialogCommon,
    DialogSuccess,
    ButtonLeftArrow,
    ButtonRightArrow,
    ButtonUpArrow,
    ButtonDownArrow,
    ButtonGeneral,
    ButtonSkin,
    LabelKeys,
    LabelMusic,
    LabelSfx,
    LabelTextConfirm,
    ButtonSave,
    ButtonMusic,
    ButtonSfx,
    ButtonConfirm,
    ButtonOK,
    BarSounds,
    ChosenMusic,
    OptionMusic,

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
    DeadArcher,
    DeadEnchantress,
    DeadKnight,
    DeadMusketeer,
    DeadSwordsman,
    DeadWizard,

    // Pause state
    BackgroundPause,
    ButtonSaveGame,
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

    // Chooosemode state
    ButtonLevelMenu,
    ButtonBackMenu,
    ButtonSurvival,

    // Game state
    CountDown,

};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffects::ID> SoundBufferHolder;

#endif  // RESOURCE_IDENTIFIERS_HPP
