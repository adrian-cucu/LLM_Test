/*
 * @description
 * CWE: 481 Assigning Instead of Comparing
 * Sinks:
 *    GoodSink: Comparing
 *    BadSink : Assigning instead of comparing
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define TARGET_VALUE 5

static void checkRandomTarget(void)
{
    int intRand = rand();

    /* Safety fix: use == for comparison instead of = assignment */
    if (intRand == TARGET_VALUE)
    {
        printLine("i was 5");
    }
}

#ifndef OMITBAD

void CWE481_Assigning_Instead_of_Comparing__basic_01_bad()
{
    checkRandomTarget();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    checkRandomTarget();
}

void CWE481_Assigning_Instead_of_Comparing__basic_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE481_Assigning_Instead_of_Comparing__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE481_Assigning_Instead_of_Comparing__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
