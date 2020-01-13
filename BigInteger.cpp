#include "BigInteger.h"
#include <cstring>

BigInteger::BigInteger(SIGN newSign, short unsigned newNOD, const char* newDigits)
{
    sign = newSign;
    numberOfDigits = newNOD;
    for (int i = 0; i < newNOD; ++i)
    {
        digits[newNOD - i - 1] = newDigits[i] - '0';
    }
}

BigInteger::BigInteger()
{
    sign = PLUS;
    numberOfDigits = 0;
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
        short unsigned maxLength = max(numberOfDigits, BI.numberOfDigits);
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
        if (*this > BI)
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
        else if (*this < BI)
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
        else
        {
            return {PLUS, 1, "0"};
        }
        difference.numberOfDigits = a.numberOfDigits;
        char carry = 0;
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
    if ((digits[0] == 0 && numberOfDigits == 1) || (BI.digits[0] == 0 && BI.numberOfDigits == 1))
    {
        return {PLUS, 1, "0"};
    }
    BigInteger product;
    char carry = 0;
    unsigned short i = 0, j = 0;
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
    if (product.digits[product.numberOfDigits - 1] == 0)
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
    if (BI.digits[0] == 0 && BI.numberOfDigits == 1)
    {
        cerr << "Division by 0!\n";
        exit(DIV_BY_0);
    }
    if (*this < BI)
    {
        return {PLUS, 1, "0"};
    }
    if (*this == BI)
    {
        if (sign == BI.sign)
        {
            return {PLUS, 1, "1"};
        }
        else
        {
            return {MINUS, 1, "1"};
        }
    }
    BigInteger quotient;
    BigInteger remainder;
    if (sign == BI.sign)
    {
        quotient.sign = PLUS;
    }
    else
    {
        quotient.sign = MINUS;
    }
    BI.sign = PLUS;
    quotient.numberOfDigits = numberOfDigits;
    remainder.numberOfDigits = 0;
    for (short int i = numberOfDigits; i >= 0; --i)
    {
        for (short int j = numberOfDigits - 1; j >= 0; --j)
        {
            remainder.digits[j + 1] = remainder.digits[j];
        }
        ++remainder.numberOfDigits;
        remainder.digits[0] = digits[i];
        quotient.digits[i] = 0;
        while (remainder >= BI)
        {
            ++quotient.digits[i];
            remainder = remainder - BI;
        }
    }
    while (quotient.digits[quotient.numberOfDigits - 1] == 0 && quotient.numberOfDigits > 1)
    {
        --quotient.numberOfDigits;
    }
    return quotient;
}

bool BigInteger::operator==(const BigInteger& BI) const
{
    short unsigned NOD = numberOfDigits;
    // Elimina zero-urile semnificative, daca exista
    while (digits[NOD - 1] == 0 && NOD > 1)
    {
        --NOD;
    }
    //Folosim NOD-ului primului nr pentru ca se considera mai mare
    for (short int i = NOD - 1; i >= 0; --i)
    {
        if (digits[i] != BI.digits[i])
        {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator<(const BigInteger& BI) const
{
    short unsigned NODa = numberOfDigits;
    short unsigned NODb = BI.numberOfDigits;
    // Elimina zero-urile semnificative, daca exista.
    while (digits[NODa - 1] == 0 && NODa > 1)
    {
        --NODa;
    }
    while (BI.digits[NODb - 1] == 0 && NODb > 1)
    {
        --NODb;
    }
    if (NODa < NODb)
    {
        return true;
    }
    if (NODa > NODb)
    {
        return false;
    }
    for (short int i = NODb - 1; i >= 0; --i)
    {
        if (digits[i] < BI.digits[i])
        {
            return true;
        }
        if (digits[i] > BI.digits[i])
        {
            return false;
        }
    }
    return false;
}

bool BigInteger::operator>(const BigInteger& BI) const
{
    return BI < *this;
}

bool BigInteger::operator>=(const BigInteger& BI) const
{
    return !(*this < BI);
}