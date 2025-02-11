#include "read_data/include/read_data.hpp"
#include "bentley_ottmann/begin_case/include/begin_case.hpp"
#include "bentley_ottmann/end_case/include/end_case.hpp"
#include "bentley_ottmann/intersection_case/include/intersection_case.hpp"

#include <stack>

int main(int argc, char* argv[]) {
    constexpr int kLimit = -1001;
    if (argc != 2) {
        std::cerr << "USAGE: <INPUT FILE NAME>\n";
        return EXIT_FAILURE;
    }
    std::ifstream input_file(argv[1], std::ios::binary);
    std::ofstream output_file(argv[2], std::ios::binary);
    if (!input_file.is_open()) {
        std::cerr << "Couldn't open input file\n";
        return EXIT_FAILURE;
    }
    Fraction scan_line = Fraction(kLimit, 1);
    OperType curr_oper_type;
    std::vector<Segment> segments;
    std::vector<const Segment*> segment_ptrs;
    std::vector<int> reversed_segment_ptrs;
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>
        min_heap{QueueComparator(segments)};
    std::map<RealPoint, Intersection> intersections;
    std::set<const Segment**, StatusComparator> status(
        {}, StatusComparator(scan_line, curr_oper_type));
    readData(input_file, segments, segment_ptrs, reversed_segment_ptrs,
             min_heap);
    while (!min_heap.empty()) {
        scan_line = min_heap.top().point_.x_;
        do {
            const QueueItem& new_event = min_heap.top();
            curr_oper_type = new_event.oper_type_;
            switch (new_event.oper_type_) {
                case OperType::BEGIN:
                    beginCaseHandler(new_event, segments, segment_ptrs,
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
        } while (!min_heap.empty() && min_heap.top().point_.x_ == scan_line);
        while (!intersections.empty() &&
               intersections.begin()->first.x_ == scan_line) {
            intersections.erase(intersections.begin());
        }
    }
    input_file.close();
    return EXIT_SUCCESS;
}
