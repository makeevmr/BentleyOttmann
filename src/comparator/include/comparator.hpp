#ifndef BENTLEY_OTTMANN_SRC_COMPARATOR
#define BENTLEY_OTTMANN_SRC_COMPARATOR

#include "../../segment/include/segment.hpp"
#include "../../queue_item/include/queue_item.hpp"

#include <vector>

class StatusComparator {
public:
    StatusComparator(Fraction& scan_line, OperType& curr_oper_type);

    bool operator()(const Segment** const& left,
                    const Segment** const& right) const;

private:
    Fraction& scan_line_x_;
    OperType& curr_oper_type_;
};

class QueueComparator {
public:
    explicit QueueComparator(const std::vector<Segment>& segments) noexcept;

    bool operator()(const QueueItem& left, const QueueItem& right) const;

private:
    const std::vector<Segment>& segments_;
};

#endif  // BENTLEY_OTTMANN_SRC_COMPARATOR
