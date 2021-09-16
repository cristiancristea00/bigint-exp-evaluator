#include "BigInteger.h"

BigInteger::BigInteger(Sign const & new_sign, uint16_t new_nod, std::string_view new_digits) noexcept
        : sign(new_sign), number_of_digits(new_nod)
{
    for (size_t i = 0; i < new_nod; ++i)
    {
        digits.at(new_nod - i - 1) = static_cast<int8_t>(new_digits.at(i) - '0');
    }
}

BigInteger::BigInteger() noexcept
{
    memset(digits.data(), 0, DIM_MAX);
}

auto operator<<(std::ostream & stream, BigInteger const & big_integer) noexcept -> std::ostream &
{
    if (big_integer.sign == BigInteger::Sign::MINUS)
    {
        stream << '-';
    }
    for (int i = big_integer.number_of_digits - 1; i >= 0; --i)
    {
        stream << +big_integer.digits.at(static_cast<size_t>(i));
    }
    return stream;
}

auto BigInteger::operator+(BigInteger big_integer) noexcept -> BigInteger
{
    if (sign == big_integer.sign)
    {
        BigInteger sum {};
        int8_t carry {0};
        uint16_t max_length = std::max(number_of_digits, big_integer.number_of_digits);
        for (size_t i = 0; i < max_length; ++i)
        {
            sum.digits.at(i) = static_cast<int8_t>(digits.at(i) + big_integer.digits.at(i) + carry);
            carry = static_cast<int8_t>(sum.digits.at(i) / BASE_TEN);
            sum.digits.at(i) %= BASE_TEN;
        }
        if (carry != 0)
        {
            sum.digits.at(max_length++) = carry;
        }
        sum.number_of_digits = max_length;
        sum.sign = sign;
        return sum;
    }
    if (sign == BigInteger::Sign::PLUS && big_integer.sign == BigInteger::Sign::MINUS)
    {
        big_integer.sign = BigInteger::Sign::PLUS;
        return *this - big_integer;
    }
    BigInteger aux = *this;
    aux.sign = BigInteger::Sign::PLUS;
    return big_integer - aux;
}

auto BigInteger::operator-(BigInteger big_integer) noexcept -> BigInteger
{
    if (sign == BigInteger::Sign::MINUS && big_integer.sign == BigInteger::Sign::PLUS)
    {
        big_integer.sign = BigInteger::Sign::MINUS;
        return *this + big_integer;
    }
    if (sign == BigInteger::Sign::PLUS && big_integer.sign == BigInteger::Sign::MINUS)
    {
        big_integer.sign = BigInteger::Sign::PLUS;
        return *this + big_integer;
    }

    BigInteger difference;
    BigInteger first;
    BigInteger second;
    if (*this > big_integer)
    {
        first = *this;
        second = big_integer;
        if (first.sign == BigInteger::Sign::MINUS && second.sign == BigInteger::Sign::MINUS)
        {
            difference.sign = BigInteger::Sign::MINUS;
        }
        else
        {
            difference.sign = BigInteger::Sign::PLUS;
        }
    }
    else if (*this < big_integer)
    {
        first = big_integer;
        second = *this;
        if (first.sign == BigInteger::Sign::MINUS && second.sign == BigInteger::Sign::MINUS)
        {
            difference.sign = BigInteger::Sign::PLUS;
        }
        else
        {
            difference.sign = BigInteger::Sign::MINUS;
        }
    }
    else
    {
        return {BigInteger::Sign::PLUS, 1, "0"};
    }
    difference.number_of_digits = first.number_of_digits;
    int8_t carry {0};
    size_t idx {0};
    for (idx = 0; idx < difference.number_of_digits; ++idx)
    {
        difference.digits.at(idx) = static_cast<int8_t>(first.digits.at(idx) - second.digits.at(idx) + carry);
        if (difference.digits.at(idx) < 0)
        {
            difference.digits.at(idx) += BASE_TEN;
            carry = -1;
        }
        else
        {
            carry = 0;
        }
    }
    idx = difference.number_of_digits - 1;
    while (difference.digits.at(idx) == 0)
    {
        --idx;
    }
    difference.number_of_digits = static_cast<uint16_t>(idx + 1);
    return difference;
}

auto BigInteger::operator*(BigInteger big_integer) noexcept -> BigInteger
{
    if ((digits[0] == 0 && number_of_digits == 1) || (big_integer.digits[0] == 0 && big_integer.number_of_digits == 1))
    {
        return {BigInteger::Sign::PLUS, 1, "0"};
    }
    BigInteger product;
    int8_t carry = 0;
    size_t idx1 {0};
    size_t idx2 {0};
    for (idx1 = 0; idx1 < number_of_digits; ++idx1)
    {
        carry = 0;
        for (idx2 = 0; idx2 < big_integer.number_of_digits; ++idx2)
        {
            product.digits.at(idx1 + idx2) += digits.at(idx1) * big_integer.digits.at(idx2) + carry;
            carry = static_cast<int8_t>(product.digits.at(idx1 + idx2) / BASE_TEN);
            product.digits.at(idx1 + idx2) %= BASE_TEN;
        }
        if (carry != 0)
        {
            product.digits.at(idx1 + idx2) = carry;
        }
    }
    product.number_of_digits = number_of_digits + big_integer.number_of_digits;
    if (product.digits.at(product.number_of_digits - 1) == 0)
    {
        --product.number_of_digits;
    }
    if (sign == big_integer.sign)
    {
        product.sign = BigInteger::Sign::PLUS;
    }
    else
    {
        product.sign = BigInteger::Sign::MINUS;
    }
    return product;
}

auto BigInteger::operator/(BigInteger big_integer) -> BigInteger
{
    if (big_integer.digits[0] == 0 && big_integer.number_of_digits == 1)
    {
        throw std::invalid_argument("Division by 0!\n");
    }
    if (*this < big_integer)
    {
        return {BigInteger::Sign::PLUS, 1, "0"};
    }
    if (*this == big_integer)
    {
        if (sign == big_integer.sign)
        {
            return {BigInteger::Sign::PLUS, 1, "1"};
        }
        return {BigInteger::Sign::MINUS, 1, "1"};
    }

    BigInteger quotient;
    BigInteger remainder;
    if (sign == big_integer.sign)
    {
        quotient.sign = BigInteger::Sign::PLUS;
    }
    else
    {
        quotient.sign = BigInteger::Sign::MINUS;
    }
    big_integer.sign = BigInteger::Sign::PLUS;
    quotient.number_of_digits = number_of_digits;
    remainder.number_of_digits = 0;
    for (int i = number_of_digits; i >= 0; --i)
    {
        for (int j = number_of_digits - 1; j >= 0; --j)
        {
            remainder.digits.at(static_cast<size_t>(j + 1)) = remainder.digits.at(static_cast<size_t>(j));
        }
        ++remainder.number_of_digits;
        remainder.digits.at(0) = digits.at(static_cast<size_t>(i));
        quotient.digits.at(static_cast<size_t>(i)) = 0;
        while (remainder >= big_integer)
        {
            ++quotient.digits.at(static_cast<size_t>(i));
            remainder = remainder - big_integer;
        }
    }
    while (quotient.digits.at(quotient.number_of_digits - 1) == 0 && quotient.number_of_digits > 1)
    {
        --quotient.number_of_digits;
    }
    return quotient;
}

auto BigInteger::operator==(BigInteger const & big_integer) const noexcept -> bool
{
    uint16_t nod = number_of_digits;
    // Remove leading zeroes if necessary
    while (digits.at(nod - 1) == 0 && nod > 1)
    {
        --nod;
    }
    for (int i = nod - 1; i >= 0; --i)
    {
        if (digits.at(static_cast<size_t>(i)) != big_integer.digits.at(static_cast<size_t>(i)))
        {
            return false;
        }
    }
    return true;
}

auto BigInteger::operator<(BigInteger const & big_integer) const noexcept -> bool
{
    uint16_t nod_a = number_of_digits;
    uint16_t nod_b = big_integer.number_of_digits;
    // Remove leading zeroes if necessary
    while (digits.at(nod_a - 1) == 0 && nod_a > 1)
    {
        --nod_a;
    }
    while (big_integer.digits.at(nod_b - 1) == 0 && nod_b > 1)
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
    for (int i = nod_b - 1; i >= 0; --i)
    {
        if (digits.at(static_cast<size_t>(i)) < big_integer.digits.at(static_cast<size_t>(i)))
        {
            return true;
        }
        if (digits.at(static_cast<size_t>(i)) > big_integer.digits.at(static_cast<size_t>(i)))
        {
            return false;
        }
    }
    return false;
}

auto BigInteger::operator>(BigInteger const & big_integer) const noexcept -> bool
{
    return big_integer < *this;
}

auto BigInteger::operator>=(BigInteger const & big_integer) const noexcept -> bool
{
    return !(*this < big_integer);
}
