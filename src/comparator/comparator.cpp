#include "include/comparator.hpp"

Comparator::Comparator(Fraction& scan_line)
    : scan_line_x_(scan_line) {}

bool Comparator::operator()(const Segment* left, const Segment* right) const {
    return left->ordinateVal(scan_line_x_) > right->ordinateVal(scan_line_x_);
}
