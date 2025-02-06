#ifndef BENTLEY_OTTMANN_SRC_COMPARATOR
#define BENTLEY_OTTMANN_SRC_COMPARATOR

#include "../../segment/include/segment.hpp"

class Comparator {
public:
    explicit Comparator(Fraction& scan_line);

    bool operator()(const Segment* left, const Segment* right) const;

private:
    Fraction& scan_line_x_;
};

#endif  // BENTLEY_OTTMANN_SRC_COMPARATOR
