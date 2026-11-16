/*
 * @description
 * CWE: 484 Omitted Break Statement in Switch
 * Sinks:
 *    GoodSink: Use breaks at the end of cases to prevent fall through
 *    BadSink : Missing break in first case
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define RANDOM_MODULO 3

static void printSwitchedNumber(void)
{
    int x = (rand() % RANDOM_MODULO);

    switch (x)
    {
    case 0:
        printLine("0");
        /* Safety fix: add missing break statement in case 0 to prevent unintended fallthrough */
        break;
    case 1:
        printLine("1");
        break;
    case 2:
        printLine("2");
        break;
    default:
        printLine("Invalid Number");
        break;
    }
}

#ifndef OMITBAD

void CWE484_Omitted_Break_Statement_in_Switch__basic_01_bad()
{
    printSwitchedNumber();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printSwitchedNumber();
}

void CWE484_Omitted_Break_Statement_in_Switch__basic_01_good()
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
    CWE484_Omitted_Break_Statement_in_Switch__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE484_Omitted_Break_Statement_in_Switch__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
