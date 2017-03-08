#include <iostream>
#include "stack.h"
#include <cctype>

int main()
{
    using namespace std;
    stack st;
    char ch;
    unsigned long po;

    cout << "Please enter A to add a purchase order,\n"
         << "P to process a pop, or Q to quit.\n";

    while(cin >> ch && toupper(ch) != 'Q')
    {
        while(cin.get() != '\n')
            continue;

        if(!isalpha(ch))
        {
            cout << '\a';
            continue;
        }
        switch(ch)
        {
        case 'A':
        case 'a':
            cout << "Enter a PO number to add:";
            cin >> po;
            if(st.isfull())
                cout << "stack is already full.\n";
            else
                st.push(po);

            break;
        case 'p':
        case 'P':
            if(st.isempty())
                cout << "stack is already empty.\n";
            else
            {
                st.pop(po);
                cout << "PO #" << po << "is poped\n";
            }
            break;
        }
        cout << "Please enter A to add a purchase order,\n"
             << "P to process a pop, or Q to quit.\n";
    }
    cout << "Bye\n";
    return 0;
}

