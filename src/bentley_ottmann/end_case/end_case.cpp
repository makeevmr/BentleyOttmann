#include "include/end_case.hpp"

#define assertm(exp, msg) assert((void(msg), exp))

void endCaseHandler(const QueueItem& new_event, std::vector<Segment>& segments,
                    std::vector<const Segment*>& segment_ptrs,
                    const std::vector<int>& reversed_segment_ptrs,
                    std::priority_queue<QueueItem, std::vector<QueueItem>,
                                        QueueComparator>& min_heap,
                    std::map<RealPoint, Intersection>& intersections,
                    std::set<const Segment**, StatusComparator>& status) {
    const std::set<const Segment**, StatusComparator>::iterator status_f_iter =
        status.find(
            &(segment_ptrs[reversed_segment_ptrs[new_event.segment_ind_]]));
    assertm(status_f_iter != status.end(),
            "There is no current segment in the status during the END event");
    if (status_f_iter != status.begin() &&
        std::next(status_f_iter) != status.end()) {
        const auto& left_neighbor = std::prev(status_f_iter);
        const auto& right_neighbor = std::next(status_f_iter);
        checkNeighborsIntersection(new_event.point_.x_, left_neighbor,
                                   right_neighbor, segments, min_heap,
                                   intersections);
    }
    status.erase(status_f_iter);
}
