#include "include/fraction.hpp"
#include "../gcd/include/gcd.hpp"

Fraction::Fraction() noexcept
    : numerator_(0),
      denominator_(1) {}

Fraction::Fraction(int64_t numerator, int64_t denomintaor) noexcept
    : numerator_(numerator),
      denominator_(denomintaor) {
    int64_t gcd_value = gcd(numerator_, denominator_);
    numerator_ /= gcd_value;
    denominator_ /= gcd_value;
    if (numerator_ >= 0 && denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    } else if (numerator_ <= 0 && denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    }
}

Fraction::Fraction(const Fraction& other)
    : numerator_(other.numerator_),
      denominator_(other.denominator_) {}

Fraction& Fraction::operator=(const Fraction& other) noexcept {
    if (this != &other) {
        this->numerator_ = other.numerator_;
        this->denominator_ = other.denominator_;
    }
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& other) noexcept {
    int64_t new_numerator =
        numerator_ * other.denominator_ + other.numerator_ * denominator_;
    int64_t new_denominator = denominator_ * other.denominator_;
    int64_t gcd_val = gcd(new_numerator, new_denominator);
    new_numerator /= gcd_val;
    new_denominator /= gcd_val;
    numerator_ = new_numerator;
    denominator_ = new_denominator;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) noexcept {
    Fraction other_copy = Fraction(-1, 1) * other;
    *this += other_copy;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) noexcept {
    numerator_ *= other.numerator_;
    denominator_ *= other.denominator_;
    int64_t gcd_val = gcd(numerator_, denominator_);
    numerator_ /= gcd_val;
    denominator_ /= gcd_val;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) noexcept {
    Fraction other_reverse(other.denominator_, other.numerator_);
    *this *= other_reverse;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Fraction& frac) noexcept {
    out << frac.numerator_ << '/' << frac.denominator_;
    return out;
}

[[nodiscard]] Fraction operator+(const Fraction& left,
                                 const Fraction& right) noexcept {
    Fraction left_copy = left;
    left_copy += right;
    return left_copy;
}

[[nodiscard]] Fraction operator-(const Fraction& left,
                                 const Fraction& right) noexcept {
    Fraction left_copy = left;
    left_copy -= right;
    return left_copy;
}

[[nodiscard]] Fraction operator*(const Fraction& left,
                                 const Fraction& right) noexcept {
    Fraction left_copy = left;
    left_copy *= right;
    return left_copy;
}

[[nodiscard]] Fraction operator/(const Fraction& left,
                                 const Fraction& right) noexcept {
    Fraction left_copy = left;
    left_copy /= right;
    return left_copy;
}

[[nodiscard]] bool operator>(const Fraction& left,
                             const Fraction& right) noexcept {
    // To avoid the possibility of overflow of int64_t
    int64_t left_int_div = left.numerator_ / left.denominator_;
    int64_t right_int_div = right.numerator_ / right.denominator_;
    double left_remainder =
        static_cast<double>(left.numerator_ % left.denominator_) /
        static_cast<double>(left.denominator_);
    double right_remainder =
        static_cast<double>(right.numerator_ % right.denominator_) /
        static_cast<double>(right.denominator_);
    return left_int_div > right_int_div ||
           (left_int_div == right_int_div && left_remainder > right_remainder);
}

[[nodiscard]] bool operator<(const Fraction& left,
                             const Fraction& right) noexcept {
    return !(left > right) && left != right;
}

// All fractions are irreducible
[[nodiscard]] bool operator==(const Fraction& left,
                              const Fraction& right) noexcept {
    return (left.numerator_ == right.numerator_) &&
           (left.denominator_ == right.denominator_);
}

[[nodiscard]] bool operator!=(const Fraction& left,
                              const Fraction& right) noexcept {
    return !(left == right);
}
