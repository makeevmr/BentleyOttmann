#include "include/point.hpp"

IntPoint::IntPoint(int64_t x, int64_t y) noexcept
    : x_(x),
      y_(y) {}

IntPoint::IntPoint(const IntPoint& other) noexcept
    : x_(other.x_),
      y_(other.y_) {}

IntPoint& IntPoint::operator=(const IntPoint& other) noexcept {
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

IntPoint::IntPoint(IntPoint&& other) noexcept
    : x_(std::move(other.x_)),
      y_(std::move(other.y_)) {}

IntPoint& IntPoint::operator=(IntPoint&& other) noexcept {
    if (this != &other) {
        x_ = std::move(other.x_);
        y_ = std::move(other.y_);
    }
    return *this;
}

IntPoint::operator RealPoint() const noexcept {
    return RealPoint(Fraction(x_, 1), Fraction(y_, 1));
}

std::ostream& operator<<(std::ostream& out, const IntPoint& point) noexcept {
    out << '(' << point.x_ << ", " << point.y_ << ')';
    return out;
}

[[nodiscard]] bool operator==(const IntPoint& left,
                              const IntPoint& right) noexcept {
    return left.x_ == right.x_ && left.y_ == right.y_;
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
