/*
 * @description Expected Behavior Violation. In this case, the function throws an exception,
 * so it must not declare a non-throwing exception specification.
 *
 * */

#include "std_testcase.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace CWE440_Expected_Behavior_Violation__exception_01
{

#ifndef OMITBAD

/* Safety fix: Remove contradictory throw() specification so throwing std::range_error does not trigger std::unexpected/std::terminate */
void bad()
{
    throw range_error("Test");
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* Throws std::range_error */
static void good1()
{
    throw range_error("Test");
}

void good()
{
    good1();
}

#endif /* OMITGOOD */

} /* close namespace */

#ifdef INCLUDEMAIN

using namespace CWE440_Expected_Behavior_Violation__exception_01;

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;

    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
