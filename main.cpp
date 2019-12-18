#include <iostream>
#include "BigInteger.h"
using namespace std;

int main()
{
    BigInteger a = {PLUS, 2, "18"};
    BigInteger b = {PLUS, 2, "34"};
    cout << a + b << endl << a * b;
    return 0;
}
