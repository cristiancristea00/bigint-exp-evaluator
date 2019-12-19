#include <iostream>
#include "BigInteger.h"
using namespace std;

int main()
{
    BigInteger a = {PLUS, 1, "9"};
    BigInteger b = {PLUS, 1, "3"};
    cout << a / b << endl << a << endl << b;
    return 0;
}
