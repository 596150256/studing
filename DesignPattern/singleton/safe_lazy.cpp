#include <iostream>
#include <mutex>

using namespace std;

class Singleton
{
public:
    static Singleton* getInstance()
    {
        unique_lock<mutex> lock(mtx);
        if (single == nullptr)
            single = new Singleton();

        return single;
    }

private:
    static Singleton* single;
    static mutex mtx;
    Singleton() {}
};

Singleton* Singleton::single = nullptr;
mutex Singleton::mtx; // default construction

