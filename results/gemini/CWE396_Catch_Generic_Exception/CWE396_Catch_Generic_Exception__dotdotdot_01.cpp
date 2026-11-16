/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE396_Catch_Generic_Exception__dotdotdot_01.cpp
Label Definition File: CWE396_Catch_Generic_Exception.label.xml
Template File: point-flaw-01.tmpl.cpp
*/
/*
 * @description
 * CWE: 396 Catch Generic Exception
 * Sinks: dotdotdot
 *    GoodSink: Catch specific exceptions
 *    BadSink : Catch ..., which will catch any exception
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <stdexcept> /* for out_of_range and domain_error */

using namespace std;

namespace CWE396_Catch_Generic_Exception__dotdotdot_01
{

static void maybeThrowExceptions()
{
    if (rand() % 2 == 0)
    {
        throw out_of_range("err1");
    }
    if (rand() % 2 == 0)
    {
        throw domain_error("err2");
    }
}

#ifndef OMITBAD

void bad()
{
    try
    {
        maybeThrowExceptions();
    }
    /* Safety fix: Catch specific exception types by const reference instead of generic catch (...) */
    catch (const out_of_range &)
    {
        printLine("out_of_range");
    }
    catch (const domain_error &)
    {
        printLine("domain_error");
        return;
    }
    printLine("ok");
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    try
    {
        maybeThrowExceptions();
    }
    catch (const out_of_range &)
    {
        printLine("out_of_range");
    }
    catch (const domain_error &)
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

#endif /* OMITGOOD */

} /* close namespace */

#ifdef INCLUDEMAIN

using namespace CWE396_Catch_Generic_Exception__dotdotdot_01;

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
