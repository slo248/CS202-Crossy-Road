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
    FieldTrafficLight,
    SwampTrafficLight,
    GraveyardTrafficLight,
    // <----------------Trafic Light------------->

    //////////////////////////////////////////////

    // <----------------Lane-------------------->
    River,
    Dirt,
    Grass,
    Graveyard,
    Soil,
    Swamp,
    // <----------------Lane-------------------->

    /////////////////////////////////////////////

    // <------------------Animal---------------->
    Bee,
    Bird,
    Crocodile,
    Dog,
    Frog,
    Rabbit,
    Sheep,
    Turtle,
    // <------------------Animal----------------->

    //////////////////////////////////////////////

    // <-------------------Enemy----------------->
    BeeBoss,
    BombBat,
    Fishmen,
    Orc,
    Zombie,

    // callbees,
    // octopus,
    // slime,
    // fullscreen_blind,
    // <-------------------Enemy----------------->

    // <---------------Characters Skin-------------->
    Archer,
    Enchantress,
    Knight,
    Musketeer,
    Swordman,
    Wizard,
    // <---------------Characters Skin-------------->

    ////////////////////////////////////////////////

    // <-------------------Obstacle----------------->
    // <----------Field---------->
    campfire1,
    campfire2,
    f_fence,
    pointer1,
    pointer2,
    stone1,
    stone2,
    stone3,
    stone4,
    stone5,
    grass1,
    grass2,
    grass3,
    grass4,
    grass5,
    bush1,
    bush2,
    bush3,
    bush4,
    flower1,
    flower2,
    flower3,
    flower4,
    butterfly1,
    butterfly2,
    butterfly3,
    butterfly4,
    tent,
    tree1,
    tree2,
    log,
    lamp,
    dirt1,
    dirt2,
    dirt3,
    box1,
    box2,
    box3,
    // // <----------Field---------->

    ////////////////////////////////////

    // <-----------Graveyard----------->
    lantern,
    gy_log,
    gy_tree1,
    gy_tree2,
    gy_tree3,
    gy_tree4,
    gy_grass1,
    gy_grass2,
    gy_grass3,
    gy_grass4,
    gy_grass5,
    bone1,
    bone2,
    bone3,
    bone4,
    gy_fence,
    statue1,
    statue2,
    statue3,
    statue4,
    statue5,
    statue6,
    // <----------Graveyard----------->

    ///////////////////////////////////

    // <-----------River-------------->
    rv_grass1,
    rv_grass2,
    rv_grass3,
    rv_grass4,
    rv_grass5,
    rv_stone1,
    rv_stone2,
    rv_stone3,
    rv_stone4,
    rv_stone5,
    jump_log,
    // <-----------River-------------->

    ///////////////////////////////////

    // <----------Swamp--------------->
    torch,
    sw_tree1,
    sw_tree2,
    sw_grass1,
    sw_grass2,
    sw_grass3,
    sw_grass4,
    sw_grass5,
    sw_stone1,
    sw_stone2,
    sw_stone3,
    sw_stone4,
    sw_stone5,
    sw_pointer1,
    sw_pointer2,
    well,
    // <----------Swamp--------------->
    // <-------------------Obstacle----------------->

    // <---------------Characters Skin-------------->
    archer,
    enchantress,
    knight,
    musketeer,
    swordman,
    wizard,
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

    // Setting state
    BackgroundSetting,
    DialogGeneral,
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
