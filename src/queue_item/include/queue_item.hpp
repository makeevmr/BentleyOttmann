#ifndef BENTLEY_OTTMANN_SRC_QUEUE_ITEM
#define BENTLEY_OTTMANN_SRC_QUEUE_ITEM

#include "../../point/include/point.hpp"

enum class OperType : int { BEGIN, INTERSECTION, END };

struct QueueItem {
public:
    int segment_ind_;
    OperType oper_type_;
    RealPoint point_;
};

#endif  // BENTLEY_OTTMANN_SRC_QUEUE_ITEM
