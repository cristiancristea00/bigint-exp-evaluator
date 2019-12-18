#include "BigInteger.h"

BigInteger::BigInteger(SEMN newSign, unsigned newNOD, char newDigits[1000])
{
    sign = newSign;
    numberOfDigits = newNOD;
    for (int i = 0; i < newNOD; ++i)
    {
        digits[newNOD - i - 1] = newDigits[i] - '0';
    }
    memset(digits + numberOfDigits, 0, DIM_MAX - numberOfDigits);
}

BigInteger::BigInteger()
{
    memset(digits, 0, DIM_MAX);
}

ostream& operator<<(ostream& os, BigInteger BI)
{
    if (BI.sign == MINUS)
    {
        os << '-';
    }
    for (int i = BI.numberOfDigits - 1; i >= 0; --i)
    {
        os << +BI.digits[i];
    }
    return os;
}

BigInteger BigInteger::operator+(BigInteger BI)
{
    if (sign == BI.sign)
    {
        BigInteger sum;
        char carry = 0;
        unsigned maxLenght = max(numberOfDigits, BI.numberOfDigits);
        for (int i = 0; i < maxLenght; ++i)
        {
            sum.digits[i] = digits[i] + BI.digits[i] + carry;
            carry = sum.digits[i] / 10;
            sum.digits[i] %= 10;
        }
        if (carry != 0)
        {
            sum.digits[maxLenght++] = carry;
        }
        sum.numberOfDigits = maxLenght;
        sum.sign = sign;
        return sum;
    }
    else
    {
        //TODO
    }
}
BigInteger BigInteger::operator-(BigInteger BI)
{
    //TODO
}
BigInteger BigInteger::operator*(BigInteger BI)
{
    BigInteger product;
    char carry = 0;
    int i, j;
    for (i = 0; i < numberOfDigits; ++i)
    {
        carry = 0;
        for (j = 0; j < BI.numberOfDigits; ++j)
        {
            product.digits[i + j] += digits[i] * BI.digits[j] + carry;
            carry = product.digits[i + j] / 10;
            product.digits[i + j] %= 10;
        }
        if (carry != 0)
        {
            product.digits[i + j] = carry;
        }
    }
    product.numberOfDigits = numberOfDigits + BI.numberOfDigits;
    if (product.digits[product.numberOfDigits] == 0)
    {
        --product.numberOfDigits;
    }
    if (sign == BI.sign)
    {
        product.sign = PLUS;
    }
    else
    {
        product.sign = MINUS;
    }
    return product;
}
BigInteger BigInteger::operator/(BigInteger BI)
{
    //TODO
}
