#include <catch2/catch.hpp>
#include <phany/phany.hpp>
#include <ph_time/timer.hpp>
using namespace std;

TEST_CASE ("")
{
    any a1;
//    phany p1;
    phany p2 {test {}};
    phany p3 = move (p2);
//    cout << sizeof (phany) << endl;
    cout << sizeof (any) << endl;
    
//    phany p4 = p3;
//    test a {};
    
    cout << "=========" << endl;
}

TEST_CASE("is class")
{
    int max = 10000000;
    {
        Timer<true> t ("any");
        for (int i = 0; i < max; ++i)
        {
            any a1 {test {}};
        }
    }
    {
        Timer<true> t ("phany");
        for (int i = 0; i < max; ++i)
        {
            phany a1 {test {}};
        }
    }
    
    
}

TEST_CASE("is not class")
{
    return;
    int max = 100000000;
    {
        Timer<true> t ("any");
        for (int i = 0; i < max; ++i)
        {
            any a1 {2};
        }
    }
    {
        Timer<true> t ("phany");
        for (int i = 0; i < max; ++i)
        {
            phany a1 {2};
        }
    }
}
