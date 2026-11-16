/*
 * @description Public Static Field Not Final
 */
#include "std_testcase.h"

namespace CWE500_Public_Static_Field_Not_Final__int_01
{
#ifndef OMITBAD
class BadClass
{
public:
    /* Remains mutable for callers that depend on the original public field. */
    static int ONE_HUNDRED;
    static int currentValue()
    {
        return ONE_HUNDRED;
    }
};

int BadClass::ONE_HUNDRED = 100;

void bad()
{
    printIntLine(BadClass::currentValue());
}
#endif
}
#ifdef INCLUDEMAIN
using namespace CWE500_Public_Static_Field_Not_Final__int_01;
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
