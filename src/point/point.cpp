#include "include/point.hpp"

IntPoint::IntPoint(int64_t x, int64_t y)
    : x_(x),
      y_(y) {}

RealPoint::RealPoint(const Fraction& x, const Fraction& y)
    : x_(x),
      y_(y) {}
