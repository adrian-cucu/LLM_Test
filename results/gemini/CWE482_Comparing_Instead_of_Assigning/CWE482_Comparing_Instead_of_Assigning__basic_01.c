/*
 * @description
 * CWE: 482 Comparing Instead of Assigning
 * Sinks:
 *    GoodSink: Assigning
 *    BadSink : Comparing instead of assigning
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define ASSIGNED_VALUE 5

static void updateAndPrintValue(void)
{
    int value = 0;

    printIntLine(value);
    /* Safety fix: use = for assignment instead of == comparison */
    value = ASSIGNED_VALUE;
    printIntLine(value);
}

#ifndef OMITBAD

void CWE482_Comparing_Instead_of_Assigning__basic_01_bad()
{
    updateAndPrintValue();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    updateAndPrintValue();
}

void CWE482_Comparing_Instead_of_Assigning__basic_01_good()
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
    CWE482_Comparing_Instead_of_Assigning__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE482_Comparing_Instead_of_Assigning__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
