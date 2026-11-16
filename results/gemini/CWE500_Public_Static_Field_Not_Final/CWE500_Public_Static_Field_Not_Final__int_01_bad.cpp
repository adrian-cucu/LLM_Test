/*
 * @description Public Static Field Not Final
 */

#include "std_testcase.h"

using namespace std;

namespace CWE500_Public_Static_Field_Not_Final__int_01
{

#ifndef OMITBAD

class BadClass
{
    public:
        /* Safety fix: declare public static field as const to prevent unintended modification */
        static const int ONE_HUNDRED = 100;
};

const int BadClass::ONE_HUNDRED;

void bad()
{
    printIntLine(BadClass::ONE_HUNDRED);
}

#endif /* OMITBAD */

} /* close namespace */

#ifdef INCLUDEMAIN

using namespace CWE500_Public_Static_Field_Not_Final__int_01;

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
