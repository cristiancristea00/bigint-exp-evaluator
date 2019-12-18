#include "BigInteger.h"

BigInteger::BigInteger(SEMN newSign, unsigned newNOD, const char* newDigits)
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
        short int carry = 0;
        unsigned maxLength = max(numberOfDigits, BI.numberOfDigits);
        for (short int i = 0; i < maxLength; ++i)
        {
            sum.digits[i] = digits[i] + BI.digits[i] + carry;
            carry = sum.digits[i] / 10;
            sum.digits[i] %= 10;
        }
        if (carry != 0)
        {
            sum.digits[maxLength++] = carry;
        }
        sum.numberOfDigits = maxLength;
        sum.sign = sign;
        return sum;
    }
    else if (sign == PLUS && BI.sign == MINUS)
    {
        BI.sign = PLUS;
        return *this - BI;
    }
    else
    {
        BigInteger aux = *this;
        aux.sign = PLUS;
        return BI - aux;
    }
}
BigInteger BigInteger::operator-(BigInteger BI)
{
    if (sign == MINUS && BI.sign == PLUS)
    {
        BI.sign = MINUS;
        return *this + BI;
    }
    else if (sign == PLUS && BI.sign == MINUS)
    {
        BI.sign = PLUS;
        return *this + BI;
    }
    else
    {
        BigInteger difference;
        BigInteger a;
        BigInteger b;
        if (this->compare(BI) == BIGGER)
        {
            a = *this;
            b = BI;
            if (a.sign == MINUS && b.sign == MINUS)
            {
                difference.sign = MINUS;
            }
            else
            {
                difference.sign = PLUS;
            }
        }
        else if (this->compare(BI) == LESS)
        {
            a = BI;
            b = *this;
            if (a.sign == MINUS && b.sign == MINUS)
            {
                difference.sign = PLUS;
            }
            else
            {
                difference.sign = MINUS;
            }
        }
        difference.numberOfDigits = a.numberOfDigits;
        short int carry = 0;
        unsigned int i = 0;
        for (i = 0; i < difference.numberOfDigits; ++i)
        {
            difference.digits[i] = a.digits[i] - b.digits[i] + carry;
            if (difference.digits[i] < 0)
            {
                difference.digits[i] += 10;
                carry = -1;
            }
            else
            {
                carry = 0;
            }
        }
        i = difference.numberOfDigits - 1;
        while (difference.digits[i] == 0)
        {
            --i;
        }
        difference.numberOfDigits = i + 1;
        return difference;
    }
}
BigInteger BigInteger::operator*(BigInteger BI)
{
    BigInteger product;
    short int carry = 0;
    short int i, j;
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

    BigInteger quotient;
    BigInteger remainder;
    //TODO
}

COMP BigInteger::compare(BigInteger BI)
{
    if (numberOfDigits < BI.numberOfDigits)
    {
        return LESS;
    }
    if (numberOfDigits > BI.numberOfDigits)
    {
        return BIGGER;
    }
    for (short int i = numberOfDigits - 1; i >= 0; --i)
    {
        if (digits[i] < BI.digits[i])
        {
            return LESS;
        }
        if (digits[i] > BI.digits[i])
        {
            return BIGGER;
        }
    }
    return EQUAL;
}
