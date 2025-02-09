#ifndef BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_BEGIN_CASE
#define BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_BEGIN_CASE

#include <cassert>

#include "../../../intersection/include/intersection.hpp"

void beginCaseHandler(
    const QueueItem& new_event, int64_t& vert_segm_end_y, int& vert_segm_ind,
    const std::vector<Segment>& segments,
    std::vector<const Segment*>& segment_ptrs,
    const std::vector<int>& reversed_segment_ptrs,
    const std::map<int, std::map<Fraction, int>>& vertical_segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections,
    std::set<const Segment**, StatusComparator>& status);

#endif  // BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_BEGIN_CASE
