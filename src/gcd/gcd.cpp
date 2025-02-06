#include "include/gcd.hpp"
#include <utility>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return std::abs(a);
}
