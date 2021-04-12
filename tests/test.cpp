#include <catch2/catch.hpp>
#include <phany/phany.hpp>
using namespace std;

TEST_CASE ("")
{
    any a1 = "hej";
    a1 = "kuk";
    any a2 = a1;
}
