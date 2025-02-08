#include "include/intersection.hpp"

// Insert new segment index into existing intersections item
void updateIntersection(
    const std::vector<Segment>& segments,
    const std::map<RealPoint, Intersection>::iterator& inter_iter,
    int new_segm_ind) {
    inter_iter->second.intersec_segms_.insert(new_segm_ind);
    const Fraction& new_semg_k = segments[new_segm_ind].getIncline();
    int& curr_lower_seg_ind = inter_iter->second.lower_seg_ind_;
    if (curr_lower_seg_ind == -1 ||
        segments[inter_iter->second.lower_seg_ind_].getIncline() < new_semg_k) {
        curr_lower_seg_ind = new_segm_ind;
    }
}

// Create new intersection
// Since the variable QueueItem::segment_ind_ is not used in the case of
// intersection, we will use it to store the number of vertical nodes involved
// in the intersection
void createIntersection(const int& vert_segments_num,
                        const RealPoint& new_point, int lower_seg_ind,
                        const std::pair<int, int>& new_segments_pair,
                        std::priority_queue<QueueItem, std::vector<QueueItem>,
                                            QueueComparator>& min_heap,
                        std::map<RealPoint, Intersection>& intersections) {
    min_heap.emplace(vert_segments_num, OperType::INTERSECTION, new_point);
    intersections.insert(std::pair<RealPoint, Intersection>{
        new_point,
        Intersection{.lower_seg_ind_ = lower_seg_ind,
                     .intersec_segms_ = std::unordered_set<int>{
                         new_segments_pair.first, new_segments_pair.second}}});
}

// Only for non-vertical segments
void checkNeighborsIntersection(
    const std::set<const Segment**, StatusComparator>::iterator& left_iter,
    const std::set<const Segment**, StatusComparator>::iterator& right_iter,
    const std::vector<Segment>& segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections) {
    const Segment* const segm_begin_ptr = &segments[0];
    int left_iter_ind = static_cast<int>(**left_iter - segm_begin_ptr);
    int right_iter_ind = static_cast<int>(**right_iter - segm_begin_ptr);
    const auto& intersection_point =
        segments[left_iter_ind].findIntersection(segments[right_iter_ind]);
    if (intersection_point.has_value()) {
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
            const Fraction& left_iter_incl =
                segments[left_iter_ind].getIncline();
            const Fraction& right_iter_incl =
                segments[right_iter_ind].getIncline();
            int lower_ind = -1;
            if (left_iter_incl > right_iter_incl) {
                lower_ind = left_iter_ind;
            } else {
                lower_ind = right_iter_ind;
            }
            createIntersection(
                0, intersection_point.value(), lower_ind,
                std::pair<int, int>{left_iter_ind, right_iter_ind}, min_heap,
                intersections);
        }
    }
}
