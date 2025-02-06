#include "include/find_intersection.hpp"

std::optional<RealPoint> findIntersection(const Segment& seg1,
                                          const Segment& seg2) noexcept {
    const auto& [point1, point2] = seg1.getPoints();
    const auto& [point3, point4] = seg2.getPoints();
    const int64_t denom = (point1.x_ - point2.x_) * (point3.y_ - point4.y_) -
                          (point1.y_ - point2.y_) * (point3.x_ - point4.x_);
    if (denom == 0) {
        return {};
    }
    const int64_t t_numer = (point1.x_ - point3.x_) * (point3.y_ - point4.y_) -
                            (point1.y_ - point3.y_) * (point3.x_ - point4.x_);
    const int64_t u_numer = (point1.x_ - point2.x_) * (point1.y_ - point3.y_) -
                            (point1.y_ - point2.y_) * (point1.x_ - point3.x_);
    if (((t_numer <= 0 && denom < 0) || (t_numer >= 0 && denom > 0)) &&
        ((u_numer <= 0 && denom > 0) || (u_numer >= 0 && denom < 0)) &&
        (std::abs(t_numer) <= std::abs(denom)) &&
        (std::abs(u_numer) < std::abs(denom))) {
        Fraction x(point1.x_ * denom + t_numer * (point2.x_ - point1.x_),
                   denom);
        Fraction y(point1.y_ * denom + t_numer * (point2.y_ - point1.y_),
                   denom);
        return RealPoint{x, y};
    }
    return {};
}
