#include <iostream>
#include <vector>
#include <cstring>

#define DIM_MAX 4

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
    short unsigned numberOfDigits;
    char digits[DIM_MAX];
    COMP compare(BigInteger);

 public:
    BigInteger(SEMN newSign, unsigned newNOD, const char* newDigits);
    BigInteger();
    friend ostream& operator<<(ostream&, BigInteger);
    BigInteger operator+(BigInteger);
    BigInteger operator-(BigInteger);
    BigInteger operator*(BigInteger);
    BigInteger operator/(BigInteger);
};