#ifndef BENTLEY_OTTMANN_SRC_SEGMENT
#define BENTLEY_OTTMANN_SRC_SEGMENT

// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment

#include <optional>
#include "../../point/include/point.hpp"

class Segment {
public:
    Segment(int x1, int y1, int x2, int y2);

    Segment(const IntPoint& point1, const IntPoint& point2);

    [[nodiscard]] std::pair<const IntPoint&, const IntPoint&> getPoints()
        const noexcept;

    // The function calculates coordinates only for non-vertical lines, since
    // only such lines are in the Status.
    [[nodiscard]] Fraction ordinateVal(const Fraction& x) const noexcept;

    [[nodiscard]] const Fraction& getIncline() const noexcept;

    [[nodiscard]] std::optional<RealPoint> findIntersection(
        const Segment& other) const noexcept;

private:
    const std::optional<Fraction> k_;
    const std::optional<Fraction> b_;
    IntPoint point1_;
    IntPoint point2_;
};

#endif  // BENTLEY_OTTMANN_SRC_SEGMENT
