#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton& getInstance()
    {
        return single;
    }

private:
    static Singleton single;
    Singleton() {}
};

Singleton Singleton::single;

