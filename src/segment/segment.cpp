#include "include/segment.hpp"

Segment::Segment(int x1, int y1, int x2, int y2)
    : k_(x2 == x1 ? std::optional<Fraction>()
                  : std::optional<Fraction>(Fraction(y2 - y1, x2 - x1))),
      b_(x2 == x1 ? std::optional<Fraction>()
                  : Fraction(y1, 1) - k_.value() * Fraction(x1, 1)),
      point1_(x1, y1),
      point2_(x2, y2) {}

[[nodiscard]] std::pair<const IntPoint&, const IntPoint&> Segment::getPoints()
    const {
    return std::pair<const IntPoint&, const IntPoint&>{point1_, point2_};
}

[[nodiscard]] Fraction Segment::ordinateVal(const Fraction& x) const {
    return k_.value() * x + b_.value();
}
