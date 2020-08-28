#include "BigInteger.h"
#include <cstring>

BigInteger::BigInteger(Sign const& new_sign, short unsigned const& new_nod, char const* new_digits) noexcept
{
    sign = new_sign;
    number_of_digits = new_nod;
    for (int i = 0; i < new_nod; ++i)
    {
        digits[new_nod - i - 1] = new_digits[i] - '0';
    }
}

BigInteger::BigInteger() noexcept
{
    sign = PLUS;
    number_of_digits = 0;
    memset(digits, 0, DIM_MAX);
}

ostream& operator<<(ostream& os, BigInteger const& big_integer) noexcept
{
    if (big_integer.sign == MINUS)
    {
        os << '-';
    }
    for (int i = big_integer.number_of_digits - 1; i >= 0; --i)
    {
        os << +big_integer.digits[i];
    }
    return os;
}

BigInteger BigInteger::operator+(BigInteger big_integer) noexcept
{
    if (sign == big_integer.sign)
    {
        BigInteger sum;
        char carry = 0;
        short unsigned max_length = max(number_of_digits, big_integer.number_of_digits);
        for (short int i = 0; i < max_length; ++i)
        {
            sum.digits[i] = digits[i] + big_integer.digits[i] + carry;
            carry = sum.digits[i] / 10;
            sum.digits[i] %= 10;
        }
        if (carry != 0)
        {
            sum.digits[max_length++] = carry;
        }
        sum.number_of_digits = max_length;
        sum.sign = sign;
        return sum;
    }
    else if (sign == PLUS && big_integer.sign == MINUS)
    {
        big_integer.sign = PLUS;
        return *this - big_integer;
    }
    else
    {
        BigInteger aux = *this;
        aux.sign = PLUS;
        return big_integer - aux;
    }
}

BigInteger BigInteger::operator-(BigInteger big_integer) noexcept
{
    if (sign == MINUS && big_integer.sign == PLUS)
    {
        big_integer.sign = MINUS;
        return *this + big_integer;
    }
    else if (sign == PLUS && big_integer.sign == MINUS)
    {
        big_integer.sign = PLUS;
        return *this + big_integer;
    }
    else
    {
        BigInteger difference;
        BigInteger a;
        BigInteger b;
        if (*this > big_integer)
        {
            a = *this;
            b = big_integer;
            if (a.sign == MINUS && b.sign == MINUS)
            {
                difference.sign = MINUS;
            }
            else
            {
                difference.sign = PLUS;
            }
        }
        else if (*this < big_integer)
        {
            a = big_integer;
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
        difference.number_of_digits = a.number_of_digits;
        char carry = 0;
        unsigned int i = 0;
        for (i = 0; i < difference.number_of_digits; ++i)
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
        i = difference.number_of_digits - 1;
        while (difference.digits[i] == 0)
        {
            --i;
        }
        difference.number_of_digits = i + 1;
        return difference;
    }
}

BigInteger BigInteger::operator*(BigInteger big_integer) noexcept
{
    if ((digits[0] == 0 && number_of_digits == 1) || (big_integer.digits[0] == 0 && big_integer.number_of_digits == 1))
    {
        return {PLUS, 1, "0"};
    }
    BigInteger product;
    char carry = 0;
    unsigned short i = 0, j = 0;
    for (i = 0; i < number_of_digits; ++i)
    {
        carry = 0;
        for (j = 0; j < big_integer.number_of_digits; ++j)
        {
            product.digits[i + j] += digits[i] * big_integer.digits[j] + carry;
            carry = product.digits[i + j] / 10;
            product.digits[i + j] %= 10;
        }
        if (carry != 0)
        {
            product.digits[i + j] = carry;
        }
    }
    product.number_of_digits = number_of_digits + big_integer.number_of_digits;
    if (product.digits[product.number_of_digits - 1] == 0)
    {
        --product.number_of_digits;
    }
    if (sign == big_integer.sign)
    {
        product.sign = PLUS;
    }
    else
    {
        product.sign = MINUS;
    }
    return product;
}

BigInteger BigInteger::operator/(BigInteger big_integer) noexcept
{
    if (big_integer.digits[0] == 0 && big_integer.number_of_digits == 1)
    {
        cerr << "Division by 0!\n";
        exit(DIV_BY_0);
    }
    if (*this < big_integer)
    {
        return {PLUS, 1, "0"};
    }
    if (*this == big_integer)
    {
        if (sign == big_integer.sign)
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
    if (sign == big_integer.sign)
    {
        quotient.sign = PLUS;
    }
    else
    {
        quotient.sign = MINUS;
    }
    big_integer.sign = PLUS;
    quotient.number_of_digits = number_of_digits;
    remainder.number_of_digits = 0;
    for (short int i = number_of_digits; i >= 0; --i)
    {
        for (short int j = number_of_digits - 1; j >= 0; --j)
        {
            remainder.digits[j + 1] = remainder.digits[j];
        }
        ++remainder.number_of_digits;
        remainder.digits[0] = digits[i];
        quotient.digits[i] = 0;
        while (remainder >= big_integer)
        {
            ++quotient.digits[i];
            remainder = remainder - big_integer;
        }
    }
    while (quotient.digits[quotient.number_of_digits - 1] == 0 && quotient.number_of_digits > 1)
    {
        --quotient.number_of_digits;
    }
    return quotient;
}

bool BigInteger::operator==(BigInteger const& big_integer) const noexcept
{
    short unsigned nod = number_of_digits;
    // Remove leading zeroes if necessary
    while (digits[nod - 1] == 0 && nod > 1)
    {
        --nod;
    }
    for (short int i = nod - 1; i >= 0; --i)
    {
        if (digits[i] != big_integer.digits[i])
        {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator<(BigInteger const& big_integer) const noexcept
{
    short unsigned nod_a = number_of_digits;
    short unsigned nod_b = big_integer.number_of_digits;
    // Remove leading zeroes if necessary
    while (digits[nod_a - 1] == 0 && nod_a > 1)
    {
        --nod_a;
    }
    while (big_integer.digits[nod_b - 1] == 0 && nod_b > 1)
    {
        --nod_b;
    }
    if (nod_a < nod_b)
    {
        return true;
    }
    if (nod_a > nod_b)
    {
        return false;
    }
    for (short int i = nod_b - 1; i >= 0; --i)
    {
        if (digits[i] < big_integer.digits[i])
        {
            return true;
        }
        if (digits[i] > big_integer.digits[i])
        {
            return false;
        }
    }
    return false;
}

bool BigInteger::operator>(BigInteger const& big_integer) const noexcept
{
    return big_integer < *this;
}

bool BigInteger::operator>=(BigInteger const& big_integer) const noexcept
{
    return !(*this < big_integer);
}