#include <iostream>

#define DIM_MAX 1000
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
	char digits[DIM_MAX] = {};

	bool operator==(const BigInteger&) const;
	bool operator<(const BigInteger&) const;
	bool operator>(const BigInteger&) const;
	bool operator>=(const BigInteger&) const;

 public:

	BigInteger(const SIGN&, const short unsigned&, const char*);
	BigInteger();

	friend ostream& operator<<(ostream&, const BigInteger&);

	BigInteger operator+(BigInteger);
	BigInteger operator-(BigInteger);
	BigInteger operator*(BigInteger);
	BigInteger operator/(BigInteger);
};