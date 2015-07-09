#include <iostream>
#include <limits>
#include "utils.h"
using namespace std;
using namespace deye81::utils;

int main()
{
    auto number =  numeric_limits<int>::max();
    auto nd = numDigits(number);
    cout << "Number = " << number;
    cout << " String = " << asString(number) << " has " << nd <<  " digits " << endl;

    return 0;
}
