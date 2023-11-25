#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category {
enum Type {
    None = 0,
    SceneOnGround = 1,
    SceneAir = 1 << 1,
    Player = 1 << 2,
    Character = 1 << 3,
    Obstacle = 1 << 4,
    TrafficLight = 1 << 5,
    Lane = 1 << 6,
};
}

#endif  // CATEGORY_HPP
