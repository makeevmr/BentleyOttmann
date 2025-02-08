#include "read_data/include/read_data.hpp"
#include "bentley_ottmann/begin_case/include/begin_case.hpp"
#include "bentley_ottmann/end_case/include/end_case.hpp"
#include "bentley_ottmann/intersection_case/include/intersection_case.hpp"

int main() {
    constexpr int kLimit = -101;
    std::ifstream input_file("../tests/input/input2.txt", std::ios::binary);
    if (!input_file.is_open()) {
        return EXIT_FAILURE;
        std::cerr << "Couldn't open input file\n";
    }
    Fraction prev_event_x = Fraction(kLimit, 1);
    Fraction scan_line = prev_event_x;
    std::vector<Segment> segments;
    std::vector<const Segment*> segment_ptrs;
    std::vector<int> reversed_segment_ptrs;
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>
        min_heap{QueueComparator(segments)};
    std::map<RealPoint, Intersection> intersections;
    std::set<const Segment**, StatusComparator> status(
        {}, StatusComparator(scan_line));
    readData(input_file, segments, segment_ptrs, reversed_segment_ptrs,
             min_heap);
    while (!min_heap.empty()) {
        const Fraction new_event_x = min_heap.top().point_.x_;
        scan_line = (prev_event_x + new_event_x) / Fraction(2, 1);
        int64_t vert_line_end_y = kLimit - 1;
        int vert_line_id = -1;
        do {
            const QueueItem& new_event = min_heap.top();
            switch (new_event.oper_type_) {
                case OperType::BEGIN:
                    beginCaseHandler(new_event, vert_line_end_y, vert_line_id,
                                     segments, segment_ptrs,
                                     reversed_segment_ptrs, min_heap,
                                     intersections, status);
                    break;
                case OperType::INTERSECTION:
                    intersectionCaseHandler(new_event, segments, segment_ptrs,
                                            reversed_segment_ptrs, min_heap,
                                            intersections, status);
                    break;
                case OperType::END:
                    endCaseHandler(new_event, segments, segment_ptrs,
                                   reversed_segment_ptrs, min_heap,
                                   intersections, status);
                    break;
            }
            min_heap.pop();
        } while (!min_heap.empty() && min_heap.top().point_.x_ == new_event_x);
        prev_event_x = new_event_x;
    }
    input_file.close();
    return EXIT_SUCCESS;
}
