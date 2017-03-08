#ifndef STACK_H
#define STACK_H
typedef unsigned long Item;

class stack
{
private:
    enum {MAX = 10};
    Item items[MAX];
    int top;

public:
    stack();
    bool isempty() const;
    bool isfull() const;
    bool push(const Item & item);
    bool pop(Item & item);
};

#endif // STACK_H
