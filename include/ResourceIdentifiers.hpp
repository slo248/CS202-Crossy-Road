#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf {
class Texture;
}

namespace Textures {
enum ID {
    // traffic lights
    red1,
    red2,
    red3,
    yellow1,
    yellow2,
    yellow3,
    green1,
    green2,
    green3,
    // roads
    river,
    road1,
    road2,
    road3,
    road4,
    road5,

    // animals
    bee,
    bird1,
    bird2,
    bird3,
    bird4,
    crocodile,
    dog,
    frog,
    rabbit,
    sheep,
    turtle,

    // bombs
    explode,
    blind,

    // characters
    archer,
    enchantress,
    knight,
    musketeer,
    swordman,
    wizard,

    // vehicles
    bee_boss,
    bom_bats,
    fishmen,
    orcs,
    zombie,

    ////others
    // Field
    fence,
    campfire1,
    campfire2,
    pointer,
    stone1,
    stone2,
    stone3,
    stone4,
    stone5,
    stone6,
    stone7,
    stone8,
    stone9,
    stone10,
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
    box1,
    box2,
    box3,
    log1,
    log2,
    log3,

    // Graveyard
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
    lantern1,
    lantern2,
    gy_fence,
    statue1,
    statue2,
    statue3,
    statue4,
    statue5,
    statue6,
    statue7,
    statue8,
    statue9,
    statue10,

    // river
    rv_stone1,
    rv_stone2,
    rv_stone3,
    rv_stone4,
    rv_stone5,
    rv_stone6,
    rv_stone7,
    rv_stone8,
    rv_stone9,
    rv_stone10,

    // swamp
    sw_tree1,
    sw_tre2,
    sw_tre3,
    sw_tre4,
    torch,
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
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif  // RESOURCE_IDENTIFIERS_HPP
