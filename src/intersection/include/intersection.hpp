#ifndef BENTLEY_OTTMANN_SRC_INTERSECTION
#define BENTLEY_OTTMANN_SRC_INTERSECTION

#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
#include <map>

#include "../../segment/include/segment.hpp"
#include "../../comparator/include/comparator.hpp"

struct Intersection {
    int lower_seg_ind_;
    std::unordered_set<int> intersec_segms_;
};

void updateIntersection(
    const std::vector<Segment>& segments,
    const std::map<RealPoint, Intersection>::iterator& inter_iter,
    int new_segm_ind);

void createIntersection(const int& vert_segments_num,
                        const RealPoint& new_point, int lower_seg_ind,
                        const std::pair<int, int>& new_segments_pair,
                        std::priority_queue<QueueItem, std::vector<QueueItem>,
                                            QueueComparator>& min_heap,
                        std::map<RealPoint, Intersection>& intersections);

// Only for non-vertical segments
void checkNeighborsIntersection(
    const Fraction& scan_line_value,
    const std::set<const Segment**, StatusComparator>::iterator& left_iter,
    const std::set<const Segment**, StatusComparator>::iterator& right_iter,
    const std::vector<Segment>& segments,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>&
        min_heap,
    std::map<RealPoint, Intersection>& intersections);

#endif  // BENTLEY_OTTMANN_SRC_INTERSECTION
