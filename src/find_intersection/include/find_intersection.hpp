#ifndef BENTLEY_OTTMANN_SRC_FIND_INTERSECTION
#define BENTLEY_OTTMANN_SRC_FIND_INTERSECTION

// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment

#include "../../segment/include/segment.hpp"

std::optional<RealPoint> findIntersection(const Segment& seg1,
                                          const Segment& seg2) noexcept;

#endif  // BENTLEY_OTTMANN_SRC_FIND_INTERSECTION
