/*
 * @description Expected Behavior Violation. The function throws an exception,
 * despite declaring that it does not.
 */
#include "std_testcase.h"
#include <string>
#include <iostream>
#include <stdexcept>

namespace CWE440_Expected_Behavior_Violation__exception_01
{
static void throwTestError()
{
    throw std::range_error("Test");
}
#ifndef OMITBAD
/* Keep the original exception contract, including its termination behavior. */
void bad() throw ()
{
    throwTestError();
}
#endif
#ifndef OMITGOOD
/* MSVC may warn that it ignores dynamic exception specifications. */
static void good1() throw (std::range_error)
{
    throwTestError();
}
void good()
{
    good1();
}
#endif
}
#ifdef INCLUDEMAIN
using namespace CWE440_Expected_Behavior_Violation__exception_01;
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
