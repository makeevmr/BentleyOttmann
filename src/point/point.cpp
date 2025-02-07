#include "include/point.hpp"

IntPoint::IntPoint(int64_t x, int64_t y) noexcept
    : x_(x),
      y_(y) {}

IntPoint::operator RealPoint() const noexcept {
    return RealPoint(Fraction(x_, 1), Fraction(y_, 1));
}

RealPoint::RealPoint(const Fraction& x, const Fraction& y) noexcept
    : x_(x),
      y_(y) {}

[[nodiscard]] bool operator<(const RealPoint& left,
                             const RealPoint& right) noexcept {
    return (left.x_ < right.x_) || (left.x_ == right.x_ && left.y_ < right.y_);
}
