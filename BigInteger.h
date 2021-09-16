#include <iostream>
#include <cstring>
#include <array>

class BigInteger
{
 public:
    enum class Sign
    {
        MINUS,
        PLUS
    };

 private:
    static constexpr size_t DIM_MAX = 1000;
    static constexpr int8_t BASE_TEN = 10;

    Sign sign {Sign::PLUS};
    uint16_t number_of_digits {0};
    std::array<int8_t, DIM_MAX> digits {};

    auto operator==(BigInteger const & big_integer) const noexcept -> bool;
    auto operator<(BigInteger const & big_integer) const noexcept -> bool;
    auto operator>(BigInteger const & big_integer) const noexcept -> bool;
    auto operator>=(BigInteger const & big_integer) const noexcept -> bool;

 public:

    BigInteger(Sign const & new_sign, uint16_t new_nod, std::string_view new_digits) noexcept;
    BigInteger() noexcept;

    friend auto operator<<(std::ostream & stream, BigInteger const & big_integer) noexcept -> std::ostream &;

    auto operator+(BigInteger) noexcept -> BigInteger;
    auto operator-(BigInteger) noexcept -> BigInteger;
    auto operator*(BigInteger) noexcept -> BigInteger;
    auto operator/(BigInteger) -> BigInteger;
};
