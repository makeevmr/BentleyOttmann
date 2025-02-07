#include "include/comparator.hpp"

StatusComparator::StatusComparator(Fraction& scan_line)
    : scan_line_x_(scan_line) {}

bool StatusComparator::operator()(const Segment** const& left,
                                  const Segment** const& right) const {
    return (*left)->ordinateVal(scan_line_x_) >
           (*right)->ordinateVal(scan_line_x_);
}

bool QueueComparator::operator()(const QueueItem& left,
                                 const QueueItem& right) const {
    const Fraction& x1 = left.point_.x_;
    const Fraction& y1 = left.point_.y_;
    const Fraction& x2 = right.point_.x_;
    const Fraction& y2 = right.point_.y_;
    const OperType& left_op = left.oper_type_;
    const OperType& right_op = right.oper_type_;
    const bool oper_order =
        (((left_op == OperType::INTERSECTION || left_op == OperType::END) &&
          right_op == OperType::BEGIN) ||
         (left_op == OperType::END && right_op == OperType::INTERSECTION));
    return (x1 > x2) || ((x1 == x2) && ((y1 > y2) || (y1 == y2 && oper_order)));
}
