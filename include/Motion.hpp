#ifndef MOTION_HPP
#define MOTION_HPP

namespace Motion {
struct Linear {
    float operator()(float x);
};
struct Quad {
    float operator()(float x);
};
struct Bezier {
    float operator()(float x);
};
struct Sigmoid {
    float operator()(float x);
};
}  // namespace Motion

#endif  // MOTION_HPP
