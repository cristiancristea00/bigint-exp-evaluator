#include <iostream>
#include <vector>
#include <cstring>

#define DIM_MAX 3
#define DIV_BY_0 1

using namespace std;

enum SEMN
{
    MINUS,
    PLUS
};

class BigInteger
{
 private:

    SEMN sign;
    short unsigned numberOfDigits;
    char digits[DIM_MAX];

 public:

    BigInteger(SEMN newSign, unsigned newNOD, const char* newDigits);
    BigInteger();
    friend ostream& operator<<(ostream&, BigInteger);
    BigInteger operator+(BigInteger);
    BigInteger operator-(BigInteger);
    BigInteger operator*(BigInteger);
    BigInteger operator/(BigInteger);
    bool operator<(const BigInteger&) const;
    bool operator>(const BigInteger&) const;
};