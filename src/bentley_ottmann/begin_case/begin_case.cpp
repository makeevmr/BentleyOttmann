#include "include/begin_case.hpp"

#define assertm(exp, msg) assert((void(msg), exp))

void beginCaseHandler(const QueueItem& new_event, int64_t& vert_line_end_y,
                      int& vert_line_id, const std::vector<Segment>& segments,
                      std::vector<const Segment*>& segment_ptrs,
                      const std::vector<int>& reversed_segment_ptrs,
                      std::priority_queue<QueueItem, std::vector<QueueItem>,
                                          QueueComparator>& min_heap,
                      std::map<RealPoint, Intersection>& intersections,
                      std::set<const Segment**, StatusComparator>& status) {
    const Segment& new_segm = segments[new_event.segment_ind_];
    const auto& [left_point, right_point] = new_segm.getPoints();
    RealPoint real_left_point = static_cast<RealPoint>(left_point);
    // New segment is vertical line
    if (left_point.x_ == right_point.x_) {
        assertm(vert_line_end_y <= right_point.y_,
                "New vert segment lower than previous");
        // Vertical lines have a common point
        if (vert_line_end_y == left_point.y_) {
            createIntersection(
                2, real_left_point, -1,
                std::pair<int, int>{vert_line_id, new_event.segment_ind_},
                min_heap, intersections);
        }
        vert_line_end_y = right_point.y_;
        vert_line_id = new_event.segment_ind_;
    } else {
        // Insert non-vertical segment
        const auto& [ins_iter, is_inserted] = status.insert(
            &segment_ptrs[reversed_segment_ptrs[new_event.segment_ind_]]);
        assertm(is_inserted, "NO INSERTSION");
        // Check neighbor above and below
        if (status.begin() != ins_iter) {
            checkNeighborsIntersection(std::prev(ins_iter), ins_iter, segments,
                                       min_heap, intersections);
        }
        if (std::next(ins_iter) != status.end()) {
            checkNeighborsIntersection(std::next(ins_iter), ins_iter, segments,
                                       min_heap, intersections);
        }
        // Check if we are in vert segment and if so, find
        // intersection point with non-vertical segment
        if (left_point.y_ <= vert_line_end_y) {
            const auto& f_iter = intersections.find(real_left_point);
            if (f_iter != intersections.end()) {
                std::unordered_set<int>& unord_set =
                    f_iter->second.intersec_segms_;
                if (!unord_set.contains(new_event.segment_ind_)) {
                    updateIntersection(segments, f_iter,
                                       new_event.segment_ind_);
                }
                if (!unord_set.contains(vert_line_id)) {
                    unord_set.insert(vert_line_id);
                }
            } else {
                createIntersection(
                    1, real_left_point, new_event.segment_ind_,
                    std::pair<int, int>{vert_line_id, new_event.segment_ind_},
                    min_heap, intersections);
            }
        }
    }
}
