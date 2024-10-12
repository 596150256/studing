#include <iostream>

using namespace std;

class Object
{
public:
    int val;
    Object(int x) : val(x) {}
};

class Reference
{
private:
    Object& obj;

public:
    Reference(Object& o) : obj(o) {}
    void modify(int newValue)
    {
        obj.val = newValue;
    }

    int getValue() const
    {
        return obj.val;
    }
};

int main()
{
    Object obj(10);
    Reference ref(obj);

    cout << ref.getValue() << endl;

    ref.modify(20);
    cout << ref.getValue() << endl;

    return 0;
}