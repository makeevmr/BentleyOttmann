#include "include/intersection_case.hpp"

#define assertm(exp, msg) assert((void(msg), exp))

static void printIntersections(
    const RealPoint& intersection_point,
    const std::unordered_set<int>& intersecting_segments) {
    std::cout << intersection_point << ": [";
    std::unordered_set<int>::const_iterator hash_set_b_iter =
        intersecting_segments.begin();
    std::unordered_set<int>::const_iterator hash_set_e_iter =
        intersecting_segments.end();
    std::cout << *(hash_set_b_iter) + 1;
    ++hash_set_b_iter;
    for (; hash_set_b_iter != hash_set_e_iter; ++hash_set_b_iter) {
        std::cout << ", " << *(hash_set_b_iter) + 1;
    }
    std::cout << "]\n";
}

// output_file << intersection_point << ": [";
// std::unordered_set<int>::const_iterator hash_set_b_iter =
//     intersecting_segments.begin();
// std::unordered_set<int>::const_iterator hash_set_e_iter =
//     intersecting_segments.end();
// output_file << *(hash_set_b_iter) + 1;
// ++hash_set_b_iter;
// for (; hash_set_b_iter != hash_set_e_iter; ++hash_set_b_iter) {
//     output_file << ", " << *(hash_set_b_iter) + 1;
// }
// output_file << "]\n";

void intersectionCaseHandler(
    const QueueItem& new_event, std::vector<Segment>& segments,
    std::vector<const Segment*>& segment_ptrs,
    std::vector<int>& reversed_segment_ptrs,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections,
    std::set<const Segment**, StatusComparator>& status) {
    const RealPoint& intersection_point = new_event.point_;
    const std::map<RealPoint, Intersection>::iterator& inter_f_iter =
        intersections.find(intersection_point);
    assertm(
        inter_f_iter != intersections.end(),
        "Couldn't find intersection point from min_heap in intersections map");
    printIntersections(intersection_point,
                       inter_f_iter->second.intersec_segms_);
    const Intersection& intersection_item = inter_f_iter->second;
    std::set<const Segment**, StatusComparator>::iterator right_swap_iter =
        status.find(&segment_ptrs[reversed_segment_ptrs[intersection_item
                                                            .lower_seg_ind_]]);
    int segments_to_swap =
        static_cast<int>(intersection_item.intersec_segms_.size());
    int steps = segments_to_swap - 1;
    std::set<const Segment**, StatusComparator>::iterator left_swap_iter =
        right_swap_iter;
    while (steps > 0) {
        --steps;
        left_swap_iter = std::prev(left_swap_iter);
    }
    const std::set<const Segment**, StatusComparator>::iterator
        left_swap_iter_copy = left_swap_iter;
    const std::set<const Segment**, StatusComparator>::iterator
        right_swap_iter_copy = right_swap_iter;
    // Swap segments
    while (segments_to_swap > 1) {
        int left_segment_ptrs_ind =
            static_cast<int>(*left_swap_iter - &(segment_ptrs[0]));
        int right_segment_ptrs_ind =
            static_cast<int>(*right_swap_iter - &(segment_ptrs[0]));
        int left_reversed_segment_ptrs_ind = static_cast<int>(
            segment_ptrs[left_segment_ptrs_ind] - &segments[0]);
        int right_reversed_segment_ptrs_ind = static_cast<int>(
            segment_ptrs[right_segment_ptrs_ind] - &segments[0]);
        segment_ptrs[left_segment_ptrs_ind] =
            &segments[right_reversed_segment_ptrs_ind];
        segment_ptrs[right_segment_ptrs_ind] =
            &segments[left_reversed_segment_ptrs_ind];
        std::swap(reversed_segment_ptrs[left_reversed_segment_ptrs_ind],
                  reversed_segment_ptrs[right_reversed_segment_ptrs_ind]);
        segments_to_swap -= 2;
        right_swap_iter = std::prev(right_swap_iter);
        left_swap_iter = std::next(left_swap_iter);
    }
    if (left_swap_iter_copy != status.begin()) {
        checkNeighborsIntersection(
            new_event.point_.x_, std::prev(left_swap_iter_copy),
            left_swap_iter_copy, segments, min_heap, intersections);
    }
    if (std::next(right_swap_iter_copy) != status.end()) {
        checkNeighborsIntersection(new_event.point_.x_, right_swap_iter_copy,
                                   std::next(right_swap_iter_copy), segments,
                                   min_heap, intersections);
    }
}
