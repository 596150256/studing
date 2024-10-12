#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton& getInstance();
private:
    Singleton() = default;
    ~Singleton() = default;

    Singleton(const Singleton& single) = delete;
    Singleton& operator= (const Singleton& single) = delete;
};

Singleton& Singleton::getInstance()
{
    static Singleton single;
    return single;
}

