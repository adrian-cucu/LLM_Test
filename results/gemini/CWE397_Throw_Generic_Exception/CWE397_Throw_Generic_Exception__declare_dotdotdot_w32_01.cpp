/*
 * @description Declare that the function throws "...", which is valid in Visual Studio, but not gcc.
 * In this test case, we throw a specific std::range_error exception.
 *
 * */

#include "std_testcase.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace CWE397_Throw_Generic_Exception__declare_dotdotdot_w32_01
{

#ifndef OMITBAD

/* Safety fix: Remove non-standard MSVC-specific throw(...) exception specification for standard C++ compatibility; throws std::range_error */
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

using namespace CWE397_Throw_Generic_Exception__declare_dotdotdot_w32_01;

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
