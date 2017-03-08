#ifndef STOCK10_H
#define STOCK10_H

class stock
{
private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot(){total_val = shares * share_val;}
public:
    stock();
    stock(const std::string &co, long n, double pr);
    ~stock();
    void buy(long num, double pr);
    void sell(long num, double pr);
    void update(double pr);
    void show() const;
};

#endif // STOCK10_H
