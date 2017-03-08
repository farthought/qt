#include <iostream>
#include "stock10.h"

stock::stock()
{
    std::cout << "Default constructor is called \n";
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;

}

stock::stock(const std::string &co, long n, double pr)
{
    std::cout << "Constructor using " << co << " is called\n";
    company = co;

    if(n < 0)
    {
        std::cout << "Number of shares should not be negative; "
                  << company << " shares set to 0 \n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}

stock::~stock()
{
    std::cout << "Bye " << company << "\n";
}

void stock::buy(long num, double pr)
{
    if(num < 0)
    {
        std::cout << "Number of shares to purchase should not be negative. "
                  << "transaction is aborted\n";
    }
    else
    {
        shares += num;
        share_val = pr;
        set_tot();
    }
}

void stock::sell(long num, double pr)
{
    if(num < 0)
    {
        std::cout << "Number of shares to sell should not be negative. "
                  << "Transaction is aborted.\n";

    }
    else if (num > shares)
    {
        std::cout << "You can't sell more than you have! "
                  << "Transaction is aborted.\n";

    }
    else
    {
        shares -= num;
        share_val = pr;
        set_tot();
    }
}

void stock::update(double pr)
{
    share_val = pr;
    set_tot();
}

void stock::show() const
{
    using std::cout;
    using std::ios_base;

    ios_base::fmtflags orig=
            cout.setf(ios_base::fixed, ios_base::floatfield);
    std::streamsize prec = cout.precision(3);
    cout << "company: " << company << " shares: " << shares << "\n";
    cout << "share price: $" << share_val << "\n";
    cout.precision(2);
    cout << "total value: $" << total_val << "\n";

    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}
