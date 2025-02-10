#include "include/comparator.hpp"

StatusComparator::StatusComparator(Fraction& scan_line,
                                   OperType& curr_oper_type)
    : scan_line_x_(scan_line),
      curr_oper_type_(curr_oper_type) {}

bool StatusComparator::operator()(const Segment** const& left,
                                  const Segment** const& right) const {
    const Segment& left_seg = **left;
    const Segment& right_seg = **right;
    const Fraction& left_ordinate = left_seg.ordinateVal(scan_line_x_);
    const Fraction& right_ordiante = right_seg.ordinateVal(scan_line_x_);
    const auto& [left_point1, left_point2] = left_seg.getPoints();
    const auto& [right_point1, right_point2] = right_seg.getPoints();
    bool is_left_vert = left_point1.x_ == left_point2.x_;
    bool is_right_vert = right_point1.x_ == right_point2.x_;
    if (curr_oper_type_ == OperType::BEGIN ||
        curr_oper_type_ == OperType::INTERSECTION) {
        if (is_left_vert && is_right_vert) {
            if (left_point2.y_ == right_point1.y_ ||
                right_point2.y_ == left_point1.y_) {
                return left_point2.y_ < right_point2.y_;
            }
            return left_ordinate > right_ordiante;
        }
        return (left_ordinate > right_ordiante) ||
               ((left_ordinate == right_ordiante) &&
                ((!is_left_vert && is_right_vert) ||
                 ((!is_left_vert && !is_right_vert) &&
                  ((left_seg.getIncline() < right_seg.getIncline()) ||
                   ((left_seg.getIncline() == right_seg.getIncline()) &&
                    (left_point2 == right_point1))))));
    } else {
        return (left_ordinate > right_ordiante) ||
               ((left_ordinate == right_ordiante) &&
                ((is_left_vert && !is_right_vert) ||
                 ((!is_left_vert && !is_right_vert) &&
                  ((left_seg.getIncline() > right_seg.getIncline()) ||
                   ((left_seg.getIncline() == right_seg.getIncline()) &&
                    (left_point1 == right_point2)))) ||
                 ((is_left_vert && is_right_vert) &&
                  (left_point2.y_ > right_point2.y_))));
    }
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
    bool is_left_vert_segm = false;
    if (left_op == OperType::BEGIN || left_op == OperType::END) {
        is_left_vert_segm = segments_[left.segment_ind_].isVertical();
    }
    const bool oper_order =
        (((left_op == OperType::INTERSECTION || left_op == OperType::END) &&
          right_op == OperType::BEGIN) ||
         (left_op == OperType::END && right_op == OperType::INTERSECTION));
    return (x1 > x2) ||
           ((x1 == x2) &&
            ((y1 > y2) || (y1 == y2 && (oper_order || (left_op == right_op &&
                                                       is_left_vert_segm)))));
}
