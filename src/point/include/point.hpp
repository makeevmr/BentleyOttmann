#ifndef BENTLEY_OTTMANN_SRC_POINT
#define BENTLEY_OTTMANN_SRC_POINT

#include <cstdint>
#include "../../fraction/include/fraction.hpp"

class IntPoint {
public:
    IntPoint(int64_t x, int64_t y);

    int64_t x_;
    int64_t y_;
};

class RealPoint {
public:
    RealPoint(const Fraction& x, const Fraction& y);

    Fraction x_;
    Fraction y_;
};

#endif  // BENTLEY_OTTMANN_SRC_POINT
