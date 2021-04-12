#include <catch2/catch.hpp>
#include <phany/phany.hpp>
using namespace std;

TEST_CASE ("")
{
    any a1;
//    phany p1;
    phany p2 {test {}};
    phany p3 = p2;
    cout << sizeof (phany) << endl;
    cout << sizeof (any) << endl;
//    phany p4 = p3;
//    test a {};
    
    cout << "=========" << endl;
}

