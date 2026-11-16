/*
 * @description Declare that the function throws "...", which is valid in
 * Visual Studio, but not gcc.
 */
#include "std_testcase.h"
#include <string>
#include <iostream>
#include <stdexcept>

namespace CWE397_Throw_Generic_Exception__declare_dotdotdot_w32_01
{
static void throwTestError()
{
    throw std::range_error("Test");
}
#ifndef OMITBAD
/* This exception specification is specific to Visual Studio. */
void bad() throw (...)
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
using namespace CWE397_Throw_Generic_Exception__declare_dotdotdot_w32_01;
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
