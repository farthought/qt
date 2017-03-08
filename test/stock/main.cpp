#include <iostream>
#include "stock10.h"

using namespace std;

int main()
{
    cout << "Using constructor to create new object\n";
    stock stock1 = stock("jingdong", 12, 10.0);
    stock1.show();
    stock stock2 = stock("taobao", 10, 100);
    stock2.show();

    cout << "Assigning stock1 to stock2: \n";
    stock2 = stock1;

    cout << "listing stock1 and stock2:\n";

    stock1.show();
    stock2.show();

    cout << "using constructor to reset an object:\n";

    stock2 = stock("puhua", 23, 2);

    cout << "Revisited stock2:\n";
    stock2.show();

    cout << "Done.\n";

    return 0;
}

