#include <iostream>
#include <mutex>
using namespace std;

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (single == nullptr)
        {
            unique_lock<mutex> lock(mtx);
            if (single == nullptr)
            {
                single = new Singleton();
            }
        }

        return single;
    }

private:
    Singleton() {}
    static Singleton* single;
    static mutex mtx;
};

Singleton* Singleton::single = nullptr;
mutex Singleton::mtx;