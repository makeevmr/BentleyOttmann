#include "include/read_data.hpp"

void readData(std::ifstream& input_file, std::vector<Segment>& segments,
              std::vector<const Segment*>& segment_ptrs,
              std::priority_queue<QueueItem, std::vector<QueueItem>,
                                  QueueComparator>& min_heap) {
    int x1, y1, x2, y2;
    while (input_file.peek() != EOF) {
        input_file >> x1 >> y1 >> x2 >> y2;
        bool is_begin_vertex_one = (x1 < x2) || (x1 == x2 && y1 < y2);
        if (!is_begin_vertex_one) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        segments.emplace_back(x1, y1, x2, y2);
        segment_ptrs.push_back(&segments.back());
        int last_ind = static_cast<int>(segments.size()) - 1;
        min_heap.push(
            QueueItem{.segment_ind_ = last_ind,
                      .oper_type_ = OperType::BEGIN,
                      .point_ = RealPoint(Fraction(x1, 1), Fraction(y1, 1))});
        min_heap.push(
            QueueItem{.segment_ind_ = last_ind,
                      .oper_type_ = OperType::END,
                      .point_ = RealPoint(Fraction(x2, 1), Fraction(y2, 1))});
    }
}
