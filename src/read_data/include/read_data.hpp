#ifndef BENTLEY_OTTMANN_SRC_READ_DATA
#define BENTLEY_OTTMANN_SRC_READ_DATA

#include "../../segment/include/segment.hpp"
#include "../../comparator/include/comparator.hpp"

#include <fstream>
#include <vector>
#include <queue>
#include <map>

void readData(std::ifstream& input_file, std::vector<Segment>& segments,
              std::vector<const Segment*>& segment_ptrs,
              std::vector<int>& reversed_segment_ptrs,
              std::map<int, std::map<Fraction, int>>& vertical_segments,
              std::priority_queue<QueueItem, std::vector<QueueItem>,
                                  QueueComparator>& min_heap);

#endif  // BENTLEY_OTTMANN_SRC_READ_DATA
