#ifndef BENTLEY_OTTMANN_SRC_FRACTION
#define BENTLEY_OTTMANN_SRC_FRACTION

#include <cstdint>
#include <iostream>

class Fraction {
public:
    Fraction() noexcept;

    Fraction(int64_t numerator, int64_t denomintaor) noexcept;

    Fraction(const Fraction& other);

    Fraction& operator=(const Fraction& other) noexcept;

    Fraction& operator+=(const Fraction& other) noexcept;

    Fraction& operator-=(const Fraction& other) noexcept;

    Fraction& operator*=(const Fraction& other) noexcept;

    Fraction& operator/=(const Fraction& other) noexcept;

private:
    int64_t numerator_;
    int64_t denominator_;

    friend std::ostream& operator<<(std::ostream& out,
                                    const Fraction& frac) noexcept;

    friend bool operator>(const Fraction& left, const Fraction& right) noexcept;

    friend bool operator==(const Fraction& left,
                           const Fraction& right) noexcept;
};

std::ostream& operator<<(std::ostream& out, const Fraction& frac) noexcept;

[[nodiscard]] Fraction operator+(const Fraction& left,
                                 const Fraction& right) noexcept;

[[nodiscard]] Fraction operator-(const Fraction& left,
                                 const Fraction& right) noexcept;

[[nodiscard]] Fraction operator*(const Fraction& left,
                                 const Fraction& right) noexcept;

[[nodiscard]] Fraction operator/(const Fraction& left,
                                 const Fraction& right) noexcept;

[[nodiscard]] bool operator>(const Fraction& left,
                             const Fraction& right) noexcept;

[[nodiscard]]
bool operator<(const Fraction& left, const Fraction& right) noexcept;

// All fractions are irreducible
[[nodiscard]] bool operator==(const Fraction& left,
                              const Fraction& right) noexcept;

[[nodiscard]] bool operator!=(const Fraction& left,
                              const Fraction& right) noexcept;

#endif  // BENTLEY_OTTMANN_SRC_FRACTION
