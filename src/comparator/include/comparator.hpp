#ifndef BENTLEY_OTTMANN_SRC_COMPARATOR
#define BENTLEY_OTTMANN_SRC_COMPARATOR

#include "../../segment/include/segment.hpp"
#include "../../queue_item/include/queue_item.hpp"

#include <vector>

class StatusComparator {
public:
    explicit StatusComparator(Fraction& scan_line);

    bool operator()(const Segment** const& left,
                    const Segment** const& right) const;

private:
    Fraction& scan_line_x_;
};

class QueueComparator {
public:
    explicit QueueComparator(const std::vector<Segment>& segments) noexcept;

    bool operator()(const QueueItem& left, const QueueItem& right) const;

private:
    const std::vector<Segment>& segments_;
};

#endif  // BENTLEY_OTTMANN_SRC_COMPARATOR
