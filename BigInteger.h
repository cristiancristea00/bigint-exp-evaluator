#include <iostream>

#define DIM_MAX 1000
#define DIV_BY_0 1

using namespace std;

enum Sign
{
    MINUS,
    PLUS
};

class BigInteger
{
 private:

    Sign sign;
    short unsigned number_of_digits;
    char digits[DIM_MAX] = {};

    bool operator==(BigInteger const&) const noexcept;
    bool operator<(BigInteger const&) const noexcept;
    bool operator>(BigInteger const&) const noexcept;
    bool operator>=(BigInteger const&) const noexcept;

 public:

    BigInteger(Sign const&, short unsigned const&, char const*) noexcept;
    BigInteger() noexcept;

    friend ostream& operator<<(ostream&, BigInteger const&) noexcept;

    BigInteger operator+(BigInteger) noexcept;
    BigInteger operator-(BigInteger) noexcept;
    BigInteger operator*(BigInteger) noexcept;
    BigInteger operator/(BigInteger) noexcept;
};