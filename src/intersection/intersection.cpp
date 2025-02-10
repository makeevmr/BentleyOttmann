#include "include/intersection.hpp"

// Insert new segment index into existing intersections item
void updateIntersection(
    const std::vector<Segment>& segments,
    const std::map<RealPoint, Intersection>::iterator& inter_iter,
    int new_segm_ind) {
    inter_iter->second.intersec_segms_.insert(new_segm_ind);
    const Segment& new_segm = segments[new_segm_ind];
    int& curr_low_segm_ind = inter_iter->second.lower_seg_ind_;
    const Segment& low_segm = segments[curr_low_segm_ind];
    if (new_segm.isVertical()) {
        if (!low_segm.isVertical()) {
            curr_low_segm_ind = new_segm_ind;
        } else {
            const IntPoint& new_segm_point2 = new_segm.getPoints().second;
            const IntPoint& low_segm_point2 = low_segm.getPoints().second;
            if (new_segm_point2.y_ > low_segm_point2.y_) {
                curr_low_segm_ind = new_segm_ind;
            }
        }
    } else if (!low_segm.isVertical() &&
               low_segm.getIncline() < new_segm.getIncline()) {
        curr_low_segm_ind = new_segm_ind;
    }
}

void createIntersection(const RealPoint& new_point, int lower_seg_ind,
                        const std::pair<int, int>& new_segments_pair,
                        std::priority_queue<QueueItem, std::vector<QueueItem>,
                                            QueueComparator>& min_heap,
                        std::map<RealPoint, Intersection>& intersections) {
    min_heap.emplace(0, OperType::INTERSECTION, new_point);
    intersections.insert(std::pair<RealPoint, Intersection>{
        new_point,
        Intersection{.lower_seg_ind_ = lower_seg_ind,
                     .intersec_segms_ = std::unordered_set<int>{
                         new_segments_pair.first, new_segments_pair.second}}});
}

void checkNeighborsIntersection(
    const Fraction& scan_line_value,
    const std::set<const Segment**, StatusComparator>::iterator& left_iter,
    const std::set<const Segment**, StatusComparator>::iterator& right_iter,
    std::vector<Segment>& segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections) {
    const Segment* const segm_begin_ptr = &segments[0];
    int left_iter_ind = static_cast<int>(**left_iter - segm_begin_ptr);
    int right_iter_ind = static_cast<int>(**right_iter - segm_begin_ptr);
    const Segment& left_segm = segments[left_iter_ind];
    Segment& right_segm = segments[right_iter_ind];
    const auto& intersection_point =
        segments[left_iter_ind].findIntersection(segments[right_iter_ind]);
    if (intersection_point.has_value() &&
        intersection_point.value().x_ >= scan_line_value) {
        const auto& f_iter = intersections.find(intersection_point.value());
        // The point is already in intersections
        if (f_iter != intersections.end()) {
            std::unordered_set<int>& unord_set = f_iter->second.intersec_segms_;
            if (!unord_set.contains(left_iter_ind)) {
                updateIntersection(segments, f_iter, left_iter_ind);
            }
            if (!unord_set.contains(right_iter_ind)) {
                updateIntersection(segments, f_iter, right_iter_ind);
            }
        } else {
            // No such point in intersections
            int lower_ind = -1;
            if (!left_segm.isVertical() && !right_segm.isVertical()) {
                const Fraction& left_iter_incl = left_segm.getIncline();
                const Fraction& right_iter_incl = right_segm.getIncline();
                if (left_iter_incl > right_iter_incl) {
                    lower_ind = left_iter_ind;
                } else {
                    lower_ind = right_iter_ind;
                }
            } else if (left_segm.isVertical() && right_segm.isVertical()) {
                const IntPoint& left_point2 = left_segm.getPoints().second;
                const IntPoint& right_point2 = right_segm.getPoints().second;
                lower_ind = left_point2.y_ > right_point2.y_ ? left_iter_ind
                                                             : right_iter_ind;
            } else if (left_segm.isVertical()) {
                lower_ind = left_iter_ind;
            } else {
                lower_ind = right_iter_ind;
            }
            createIntersection(
                intersection_point.value(), lower_ind,
                std::pair<int, int>{left_iter_ind, right_iter_ind}, min_heap,
                intersections);
        }
        if (!left_segm.isVertical() && right_segm.isVertical()) {
            right_segm.getVertSegmParameter() = intersection_point->y_;
        }
    }
}
