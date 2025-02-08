#include "include/segment.hpp"

#include <cassert>

Segment::Segment(int x1, int y1, int x2, int y2)
    : k_(x2 == x1 ? std::optional<Fraction>()
                  : std::optional<Fraction>(Fraction(y2 - y1, x2 - x1))),
      b_(x2 == x1 ? std::optional<Fraction>()
                  : Fraction(y1, 1) - k_.value() * Fraction(x1, 1)),
      point1_(x1, y1),
      point2_(x2, y2) {}

[[nodiscard]] std::pair<const IntPoint&, const IntPoint&> Segment::getPoints()
    const noexcept {
    return std::pair<const IntPoint&, const IntPoint&>{point1_, point2_};
}

// The function calculates coordinates only for non-vertical lines, since
// only such lines are in the Status.
[[nodiscard]] Fraction Segment::ordinateVal(const Fraction& x) const noexcept {
    return k_.value() * x + b_.value();
}

// applies only to non - vertical segments
[[nodiscard]] const Fraction& Segment::getIncline() const noexcept {
    assert(k_.has_value());
    return k_.value();
}

[[nodiscard]] std::optional<RealPoint> Segment::findIntersection(
    const Segment& other) const noexcept {
    const auto& [other_point1, other_point2] = other.getPoints();
    const int64_t denom =
        (point1_.x_ - point2_.x_) * (other_point1.y_ - other_point2.y_) -
        (point1_.y_ - point2_.y_) * (other_point1.x_ - other_point2.x_);
    if (denom == 0) {
        return {};
    }
    const int64_t t_numer =
        (point1_.x_ - other_point1.x_) * (other_point1.y_ - other_point2.y_) -
        (point1_.y_ - other_point1.y_) * (other_point1.x_ - other_point2.x_);
    const int64_t u_numer =
        (point1_.x_ - point2_.x_) * (point1_.y_ - other_point1.y_) -
        (point1_.y_ - point2_.y_) * (point1_.x_ - other_point1.x_);
    if (((t_numer <= 0 && denom < 0) || (t_numer >= 0 && denom > 0)) &&
        ((u_numer <= 0 && denom > 0) || (u_numer >= 0 && denom < 0)) &&
        (std::abs(t_numer) <= std::abs(denom)) &&
        (std::abs(u_numer) < std::abs(denom))) {
        Fraction x(point1_.x_ * denom + t_numer * (point2_.x_ - point1_.x_),
                   denom);
        Fraction y(point1_.y_ * denom + t_numer * (point2_.y_ - point1_.y_),
                   denom);
        return RealPoint{x, y};
    }
    return {};
}
