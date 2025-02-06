#ifndef BENTLEY_OTTMANN_SRC_FRACTION
#define BENTLEY_OTTMANN_SRC_FRACTION

#include <cstdint>
#include <iostream>

class Fraction {
public:
    Fraction(int64_t numerator, int64_t denomintaor);

    Fraction(const Fraction& other);

    Fraction& operator*=(const Fraction& other);

private:
    int64_t numerator_;
    int64_t denominator_;

    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);

    friend Fraction operator*(const Fraction& left, const Fraction& right);

    friend Fraction operator+(const Fraction& left, const Fraction& right);

    friend Fraction operator-(const Fraction& left, const Fraction& right);

    friend bool operator>(const Fraction& left, const Fraction& right);
};

std::ostream& operator<<(std::ostream& out, const Fraction& frac);

Fraction operator*(const Fraction& left, const Fraction& right);

Fraction operator+(const Fraction& left, const Fraction& right);

Fraction operator-(const Fraction& left, const Fraction& right);

bool operator>(const Fraction& left, const Fraction& right);

#endif  // BENTLEY_OTTMANN_SRC_FRACTION
