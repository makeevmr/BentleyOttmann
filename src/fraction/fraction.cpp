#include "include/fraction.hpp"
#include "../gcd/include/gcd.hpp"

Fraction::Fraction(int64_t numerator, int64_t denomintaor)
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

Fraction& Fraction::operator*=(const Fraction& other) {
    numerator_ *= other.numerator_;
    denominator_ *= other.denominator_;
    int64_t gcd_val = gcd(numerator_, denominator_);
    numerator_ /= gcd_val;
    denominator_ /= gcd_val;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    out << frac.numerator_ << '/' << frac.denominator_;
    return out;
}

Fraction operator*(const Fraction& left, const Fraction& right) {
    return Fraction(left.numerator_ * right.numerator_,
                    left.denominator_ * right.denominator_);
}

Fraction operator+(const Fraction& left, const Fraction& right) {
    int64_t new_numerator = left.numerator_ * right.denominator_ +
                            right.numerator_ * left.denominator_;
    int64_t new_denominator = left.denominator_ * right.denominator_;
    return Fraction(new_numerator, new_denominator);
}

Fraction operator-(const Fraction& left, const Fraction& right) {
    return left + Fraction(-1, 1) * right;
}

bool operator>(const Fraction& left, const Fraction& right) {
    return left.numerator_ * right.denominator_ >
           left.denominator_ * right.numerator_;
}
