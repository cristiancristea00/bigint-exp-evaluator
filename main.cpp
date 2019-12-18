#include <iostream>
#include "BigInteger.h"
using namespace std;

int main()
{
    BigInteger a = {MINUS, 2, "34"};
    BigInteger b = {PLUS, 2, "18"};
    cout << a + b << endl << a << endl << b;
    return 0;
}
