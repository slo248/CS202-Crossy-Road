#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category {
enum Type {
    None = 0,
    SceneOnGround = 1,
    SceneAir = 1 << 1,
    Player = 1 << 2,
    Enemy = 1 << 3,
    Obstacle = 1 << 4,
    Decoration = 1 << 5,
    TrafficLight = 1 << 6,
    Lane = 1 << 7,
};
}

#endif  // CATEGORY_HPP
