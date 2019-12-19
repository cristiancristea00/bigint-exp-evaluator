#include <iostream>
#include <vector>
#include <cstring>

#define DIM_MAX 300
#define DIV_BY_0 1

using namespace std;

enum SIGN
{
    MINUS,
    PLUS
};

class BigInteger
{
 private:

    SIGN sign;
    short unsigned numberOfDigits;
    char digits[DIM_MAX];

    bool operator==(const BigInteger&) const;
    bool operator<(const BigInteger&) const;
    bool operator>(const BigInteger&) const;
    bool operator>=(const BigInteger&) const;

 public:

    BigInteger(SIGN newSign, unsigned newNOD, const char* newDigits);
    BigInteger();

    friend ostream& operator<<(ostream&, BigInteger);

    BigInteger operator+(BigInteger);
    BigInteger operator-(BigInteger);
    BigInteger operator*(BigInteger);
    BigInteger operator/(BigInteger);
};