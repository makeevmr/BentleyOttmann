#include "include/begin_case.hpp"

#define assertm(exp, msg) assert((void(msg), exp))

void beginCaseHandler(const QueueItem& new_event,
                      std::vector<Segment>& segments,
                      std::vector<const Segment*>& segment_ptrs,
                      const std::vector<int>& reversed_segment_ptrs,
                      std::priority_queue<QueueItem, std::vector<QueueItem>,
                                          QueueComparator>& min_heap,
                      std::map<RealPoint, Intersection>& intersections,
                      std::set<const Segment**, StatusComparator>& status) {
    int new_segm_ind = new_event.segment_ind_;
    const auto& [ins_iter, is_inserted] =
        status.insert(&segment_ptrs[reversed_segment_ptrs[new_segm_ind]]);
    assertm(is_inserted, "New segment not inserted in status");
    if (status.begin() != ins_iter) {
        checkNeighborsIntersection(new_event.point_.x_, std::prev(ins_iter),
                                   ins_iter, segments, min_heap, intersections);
    }
    if (std::next(ins_iter) != status.end()) {
        checkNeighborsIntersection(new_event.point_.x_, ins_iter,
                                   std::next(ins_iter), segments, min_heap,
                                   intersections);
    }
}
