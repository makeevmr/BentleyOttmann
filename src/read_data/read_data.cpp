#include "include/read_data.hpp"

void readData(std::ifstream& input_file, std::vector<Segment>& segments,
              std::vector<const Segment*>& segment_ptrs,
              std::vector<int>& reversed_segment_ptrs,
              std::map<int, std::map<Fraction, int>>& vertical_segments,
              std::priority_queue<QueueItem, std::vector<QueueItem>,
                                  QueueComparator>& min_heap) {
    int x1, y1, x2, y2;
    int last_ind = -1;
    while (input_file.peek() != EOF) {
        input_file >> x1 >> y1 >> x2 >> y2;
        bool is_begin_vertex_one = (x1 < x2) || (x1 == x2 && y1 < y2);
        if (!is_begin_vertex_one) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        segments.emplace_back(x1, y1, x2, y2);
        ++last_ind;
        min_heap.emplace(last_ind, OperType::BEGIN,
                         RealPoint(Fraction(x1, 1), Fraction(y1, 1)));
        min_heap.emplace(last_ind, OperType::END,
                         RealPoint(Fraction(x2, 1), Fraction(y2, 1)));
        if (x1 == x2) {
            vertical_segments[x1].insert(
                std::pair<Fraction, int>{Fraction(y1, 1), last_ind});
        }
    }
    for (std::size_t i = 0, segments_size = segments.size(); i < segments_size;
         ++i) {
        reversed_segment_ptrs.push_back(static_cast<int>(i));
        segment_ptrs.push_back(&segments[i]);
    }
}
