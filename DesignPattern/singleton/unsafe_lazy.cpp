#include <iostream>

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (single == nullptr)
            single = new Singleton();

        return single;
    }

private:
    Singleton() {}
    static Singleton* single;
};

Singleton* Singleton::single = nullptr;