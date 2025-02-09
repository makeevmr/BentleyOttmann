#ifndef BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_INTERSECTION_CASE
#define BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_INTERSECTION_CASE

#include <cassert>

#include "../../../intersection/include/intersection.hpp"

// TODO delete later
#include <fstream>
void intersectionCaseHandler(
    std::ofstream& output_file, const QueueItem& new_event,
    const std::vector<Segment>& segments,
    std::vector<const Segment*>& segment_ptrs,
    std::vector<int>& reversed_segment_ptrs,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections,
    std::set<const Segment**, StatusComparator>& status);

#endif  // BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_INTERSECTION_CASE
