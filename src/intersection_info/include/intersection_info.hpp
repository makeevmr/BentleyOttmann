#ifndef BENTLEY_OTTMANN_SRC_INTERSECTION_INFO
#define BENTLEY_OTTMANN_SRC_INTERSECTION_INFO

#include <unordered_set>

struct IntersectionInfo {
    int lower_seg_ind_;
    std::unordered_set<int> intersec_segms_;
};

#endif  // BENTLEY_OTTMANN_SRC_INTERSECTION_INFO
