#include "include/point.hpp"

IntPoint::IntPoint(int64_t x, int64_t y) noexcept
    : x_(x),
      y_(y) {}

IntPoint::operator RealPoint() const noexcept {
    return RealPoint(Fraction(x_, 1), Fraction(y_, 1));
}

std::ostream& operator<<(std::ostream& out, const IntPoint& point) noexcept {
    out << '(' << point.x_ << ", " << point.y_ << ')';
    return out;
}

RealPoint::RealPoint(const Fraction& x, const Fraction& y) noexcept
    : x_(x),
      y_(y) {}

[[nodiscard]] bool operator<(const RealPoint& left,
                             const RealPoint& right) noexcept {
    return (left.x_ < right.x_) || (left.x_ == right.x_ && left.y_ < right.y_);
}

std::ostream& operator<<(std::ostream& out, const RealPoint& point) noexcept {
    out << '(' << point.x_ << ", " << point.y_ << ')';
    return out;
}
