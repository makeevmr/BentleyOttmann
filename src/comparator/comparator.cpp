#include "include/comparator.hpp"

StatusComparator::StatusComparator(Fraction& scan_line)
    : scan_line_x_(scan_line) {}

bool StatusComparator::operator()(const Segment** const& left,
                                  const Segment** const& right) const {
    return (*left)->ordinateVal(scan_line_x_) >
           (*right)->ordinateVal(scan_line_x_);
}

QueueComparator::QueueComparator(const std::vector<Segment>& segments) noexcept
    : segments_(segments) {}

bool QueueComparator::operator()(const QueueItem& left,
                                 const QueueItem& right) const {
    const Fraction& x1 = left.point_.x_;
    const Fraction& y1 = left.point_.y_;
    const Fraction& x2 = right.point_.x_;
    const Fraction& y2 = right.point_.y_;
    const OperType& left_op = left.oper_type_;
    const OperType& right_op = right.oper_type_;
    bool is_right_vert_segm = false;
    if (right_op == OperType::BEGIN || right_op == OperType::END) {
        const auto& [right_point1, right_point2] =
            segments_[right.segment_ind_].getPoints();
        is_right_vert_segm = (right_point1.y_ == right_point2.y_);
    }
    const bool oper_order =
        (((left_op == OperType::INTERSECTION || left_op == OperType::END) &&
          right_op == OperType::BEGIN) ||
         (left_op == OperType::END && right_op == OperType::INTERSECTION));
    return (x1 > x2) ||
           ((x1 == x2) &&
            ((y1 > y2) || (y1 == y2 && (oper_order || (left_op == right_op &&
                                                       is_right_vert_segm)))));
}
