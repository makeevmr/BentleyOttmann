#include "include/begin_case.hpp"

#define assertm(exp, msg) assert((void(msg), exp))

static void checkDiffTypesSegmentIntersection(
    const int& vert_segm_ind, const int& non_vert_segm_ind,
    const RealPoint& intersection_point, const std::vector<Segment>& segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections) {
    const auto& f_iter = intersections.find(intersection_point);
    if (f_iter != intersections.end()) {
        std::unordered_set<int>& unord_set = f_iter->second.intersec_segms_;
        if (!unord_set.contains(non_vert_segm_ind)) {
            updateIntersection(segments, f_iter, non_vert_segm_ind);
        }
        if (!unord_set.contains(vert_segm_ind)) {
            unord_set.insert(vert_segm_ind);
        }
    } else {
        createIntersection(
            1, intersection_point, non_vert_segm_ind,
            std::pair<int, int>{vert_segm_ind, non_vert_segm_ind}, min_heap,
            intersections);
    }
}

static void checkPassThroughVertSegment(
    const int vert_segm_ind, const int& non_vert_segm_ind,
    const int& x_intersection_val, const Fraction& y_intersection_val,
    const std::vector<Segment>& segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections) {
    const Segment& vert_segment = segments[vert_segm_ind];
    const auto& [left_vert_point, right_vert_point] = vert_segment.getPoints();
    RealPoint intersection_point =
        RealPoint(Fraction(x_intersection_val, 1), y_intersection_val);
    if ((Fraction(left_vert_point.y_, 1) <= y_intersection_val) &&
        (y_intersection_val <= Fraction(right_vert_point.y_, 1))) {
        checkDiffTypesSegmentIntersection(vert_segm_ind, non_vert_segm_ind,
                                          intersection_point, segments,
                                          min_heap, intersections);
    }
}

void beginCaseHandler(
    const QueueItem& new_event, int64_t& vert_segm_end_y, int& vert_segm_ind,
    const std::vector<Segment>& segments,
    std::vector<const Segment*>& segment_ptrs,
    const std::vector<int>& reversed_segment_ptrs,
    const std::map<int, std::map<Fraction, int>>& vertical_segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections,
    std::set<const Segment**, StatusComparator>& status) {
    int new_segm_ind = new_event.segment_ind_;
    const Segment& new_segm = segments[new_segm_ind];
    const auto& [left_point, right_point] = new_segm.getPoints();
    RealPoint real_left_point = static_cast<RealPoint>(left_point);
    // New segment is vertical line
    if (left_point.x_ == right_point.x_) {
        assertm(vert_segm_end_y <= right_point.y_,
                "New vert segment lower than previous");
        // Vertical lines have a common point
        if (vert_segm_end_y == left_point.y_ &&
            !intersections.contains(real_left_point)) {
            createIntersection(2, real_left_point, -1,
                               std::pair<int, int>{vert_segm_ind, new_segm_ind},
                               min_heap, intersections);
        }
        vert_segm_end_y = right_point.y_;
        vert_segm_ind = new_segm_ind;
    } else {
        // Insert non-vertical segment
        const auto& [ins_iter, is_inserted] =
            status.insert(&segment_ptrs[reversed_segment_ptrs[new_segm_ind]]);
        assertm(is_inserted, "NO INSERTSION");
        // Check neighbor above and below
        if (status.begin() != ins_iter) {
            checkNeighborsIntersection(new_event.point_.x_, std::prev(ins_iter),
                                       ins_iter, segments, min_heap,
                                       intersections);
        }
        if (std::next(ins_iter) != status.end()) {
            checkNeighborsIntersection(new_event.point_.x_, std::next(ins_iter),
                                       ins_iter, segments, min_heap,
                                       intersections);
        }
        // Check if we are in vert segment and if so, find
        // intersection point with non-vertical segment
        if (left_point.y_ <= vert_segm_end_y) {
            checkDiffTypesSegmentIntersection(vert_segm_ind, new_segm_ind,
                                              real_left_point, segments,
                                              min_heap, intersections);
        }
        std::map<int, std::map<Fraction, int>>::const_iterator
            vert_segm_e_iter = vertical_segments.end();
        std::map<int, std::map<Fraction, int>>::const_iterator
            vert_segm_f_iter =
                vertical_segments.upper_bound(static_cast<int>(left_point.x_));
        while (vert_segm_f_iter != vert_segm_e_iter &&
               vert_segm_f_iter->first < right_point.x_) {
            const Fraction& y_intersection_val =
                new_segm.ordinateVal(Fraction(vert_segm_f_iter->first, 1));
            const std::map<Fraction, int>& vert_segms_on_line_map =
                vert_segm_f_iter->second;
            const auto& vert_segms_on_line_f_iter =
                vert_segms_on_line_map.lower_bound(y_intersection_val);
            if (vert_segms_on_line_f_iter != vert_segms_on_line_map.end()) {
                checkPassThroughVertSegment(
                    vert_segms_on_line_f_iter->second, new_segm_ind,
                    vert_segm_f_iter->first, y_intersection_val, segments,
                    min_heap, intersections);
            }
            if (vert_segms_on_line_f_iter != vert_segms_on_line_map.begin()) {
                checkPassThroughVertSegment(
                    std::prev(vert_segms_on_line_f_iter)->second, new_segm_ind,
                    vert_segm_f_iter->first, y_intersection_val, segments,
                    min_heap, intersections);
            }
            ++vert_segm_f_iter;
        }
    }
}
