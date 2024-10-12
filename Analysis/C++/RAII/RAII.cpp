#include <iostream>
#include <stdexcept>
using namespace std;

class Resource
{
public:
    Resource() {}
    ~Resource() noexcept
    {
        try
        {
            throw runtime_error("Error while releasing resource.");
        }
        catch(...)
        {
            cerr << "Exception caught in destructor.Resource release failed." << endl;
            // throw runtime_error("Error while releasing resource.");     not do this!
        }
    }
};

int main()
{
    try
    {
        Resource res;
        throw runtime_error("Error occurred during execution.");
    }
    catch(const exception& e)
    {
        cerr << "Caught exception: " << e.what() << endl;
    }

    return 0;
}