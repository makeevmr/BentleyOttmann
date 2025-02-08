#ifndef BENTLEY_OTTMANN_SRC_POINT
#define BENTLEY_OTTMANN_SRC_POINT

#include <cstdint>
#include "../../fraction/include/fraction.hpp"

struct RealPoint;

struct IntPoint {
public:
    IntPoint(int64_t x, int64_t y) noexcept;

    explicit operator RealPoint() const noexcept;

    int64_t x_;
    int64_t y_;
};

std::ostream& operator<<(std::ostream& out, const IntPoint& point) noexcept;

struct RealPoint {
public:
    RealPoint(const Fraction& x, const Fraction& y) noexcept;

    Fraction x_;
    Fraction y_;
};

[[nodiscard]] bool operator<(const RealPoint& left,
                             const RealPoint& right) noexcept;

std::ostream& operator<<(std::ostream& out, const RealPoint& point) noexcept;

#endif  // BENTLEY_OTTMANN_SRC_POINT
