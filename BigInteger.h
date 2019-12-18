#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <vector>
#include <iostream>
#include <cstring>

#define DIM_MAX 1000

using namespace std;

enum SEMN
{
    MINUS,
    PLUS
};

enum COMP
{
    LESS = -1,
    EQUAL = 0,
    BIGGER = 1
};

class BigInteger
{
 private:
    SEMN sign;
    unsigned numberOfDigits;
    char digits[DIM_MAX];
    COMP compare(BigInteger);

 public:
    BigInteger(SEMN newSign, unsigned newNOD, char newDigits[1000]);
    BigInteger();
    friend ostream& operator<<(ostream&, BigInteger);
    BigInteger operator+(BigInteger);
    BigInteger operator-(BigInteger);
    BigInteger operator*(BigInteger);
    BigInteger operator/(BigInteger);
};

#endif
