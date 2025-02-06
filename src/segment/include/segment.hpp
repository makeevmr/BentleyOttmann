#ifndef BENTLEY_OTTMANN_SRC_SEGMENT
#define BENTLEY_OTTMANN_SRC_SEGMENT

#include "../../point/include/point.hpp"
#include <optional>

class Segment {
public:
    Segment(int x1, int y1, int x2, int y2);

    [[nodiscard]] std::pair<const IntPoint&, const IntPoint&> getPoints() const;

    // The function calculates coordinates only for non-vertical lines, since
    // only such lines are in the Status and Queue.
    [[nodiscard]] Fraction ordinateVal(const Fraction& x) const;

private:
    const std::optional<Fraction> k_;
    const std::optional<Fraction> b_;
    IntPoint point1_;
    IntPoint point2_;
};

#endif  // BENTLEY_OTTMANN_SRC_SEGMENT
