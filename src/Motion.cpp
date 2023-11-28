#include "Motion.hpp"

#include <cassert>
#include <cmath>

using namespace Motion;

float Linear::operator()(float x) {
    assert(0 <= x && x <= 1);
    return x;
}

float Quad::operator()(float x) {
    assert(0 <= x && x <= 1);
    return x * x;
}

float Bezier::operator()(float x) {
    assert(0 <= x && x <= 1);
    return x * x * (3.f - 2.f * x);
}

float Sigmoid::operator()(float x) {
    assert(0 <= x && x <= 1);
    return 1.f / (1.f + exp(-12.f * (x - 0.5f)));
}
