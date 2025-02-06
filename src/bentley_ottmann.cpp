#include "find_intersection/include/find_intersection.hpp"
#include "comparator/include/comparator.hpp"

#include <set>
#include <unordered_set>

int main() {
    Fraction scan_line(10, 1);
    std::set<Segment*, Comparator> status({}, Comparator(scan_line));
    Fraction a(4, 8);
    Fraction b(3, 9);
    std::cout << a + b << '\n';
    std::cout << a * b << '\n';
    std::cout << a - b << '\n';
    // std::unordered_set<Segment*> set;
    // std::unordered_set<std::pair<int, int>> set;
    // std::set<Segment*> set;
    // std::pair<int, int> p{1, 2};
    // auto& [a, b] = p;

    Segment seg1(2, 4, 2, -5);
    Segment seg2(5, 0, -5, 0);
    // Segment seg1(0, 0, 2, 2);
    // Segment seg2(1, 1, 3, 3);
    std::optional<RealPoint> inter_point = findIntersection(seg1, seg2);
    if (inter_point) {
        std::cout << inter_point->x_ << ' ' << inter_point->y_ << '\n';
    } else {
        std::cout << "NO INTERSECTION\n";
    }
    return 0;
}
