#include "read_data/include/read_data.hpp"
#include "bentley_ottmann/begin_case/include/begin_case.hpp"
#include "bentley_ottmann/end_case/include/end_case.hpp"
#include "bentley_ottmann/intersection_case/include/intersection_case.hpp"

int main() {
    constexpr int kLimit = -1001;
    std::ifstream input_file("../tests/input/input9.txt", std::ios::binary);
    if (!input_file.is_open()) {
        std::cerr << "Couldn't open input file\n";
        return EXIT_FAILURE;
    }
    Fraction scan_line = Fraction(kLimit, 1);
    OperType curr_oper_type;
    std::vector<Segment> segments;
    std::vector<const Segment*> segment_ptrs;
    std::vector<int> reversed_segment_ptrs;
    std::map<int, std::map<Fraction, int>> vertical_segments;
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>
        min_heap{QueueComparator(segments)};
    std::map<RealPoint, Intersection> intersections;
    std::set<const Segment**, StatusComparator> status(
        {}, StatusComparator(scan_line, curr_oper_type));
    readData(input_file, segments, segment_ptrs, reversed_segment_ptrs,
             vertical_segments, min_heap);
    while (!min_heap.empty()) {
        const Fraction new_event_x = min_heap.top().point_.x_;
        scan_line = new_event_x;
        int64_t vert_segm_end_y = kLimit;
        int vert_segm_ind = -1;
        do {
            const QueueItem& new_event = min_heap.top();
            curr_oper_type = new_event.oper_type_;
            switch (new_event.oper_type_) {
                case OperType::BEGIN:
                    beginCaseHandler(new_event, vert_segm_end_y, vert_segm_ind,
                                     segments, segment_ptrs,
                                     reversed_segment_ptrs, vertical_segments,
                                     min_heap, intersections, status);
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
    }
    input_file.close();
    return EXIT_SUCCESS;
}
