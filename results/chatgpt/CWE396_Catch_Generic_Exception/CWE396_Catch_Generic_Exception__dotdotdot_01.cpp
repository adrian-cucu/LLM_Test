/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE396_Catch_Generic_Exception__dotdotdot_01.cpp
Label Definition File: CWE396_Catch_Generic_Exception.label.xml
Template File: point-flaw-01.tmpl.cpp
*/
#include "std_testcase.h"
#include <stdexcept>

namespace CWE396_Catch_Generic_Exception__dotdotdot_01
{
static void chooseException()
{
    if (rand() % 2 == 0) { throw std::out_of_range("err1"); }
    if (rand() % 2 == 0) { throw std::domain_error("err2"); }
}
#ifndef OMITBAD
void bad()
{
    try
    {
        chooseException();
    }
    catch (...)
    {
        printLine("exception");
    }
    printLine("ok");
}
#endif
#ifndef OMITGOOD
static void good1()
{
    try
    {
        chooseException();
    }
    catch (const std::out_of_range &)
    {
        printLine("out_of_range");
    }
    catch (const std::domain_error &)
    {
        printLine("domain_error");
        return;
    }
    printLine("ok");
}
void good()
{
    good1();
}
#endif
}
#ifdef INCLUDEMAIN
using namespace CWE396_Catch_Generic_Exception__dotdotdot_01;
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
