/*
 * @description
 * CWE: 478 Missing Default Case in Switch
 * Sinks:
 *    GoodSink: Use default case in switch statement
 *    BadSink : No default case in a switch statement
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define RANDOM_MODULO 3

static void printRandomChoice(void)
{
    const char *charString = "shouldn't see this value";
    int x = (rand() % RANDOM_MODULO);

    switch (x)
    {
    case 0:
        charString = "0";
        break;
    case 1:
        charString = "1";
        break;
    /* Safety fix: add default case to handle unexpected switch values */
    default:
        return;
    }

    printLine(charString);
}

#ifndef OMITBAD

void CWE478_Missing_Default_Case_in_Switch__basic_01_bad()
{
    printRandomChoice();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printRandomChoice();
}

void CWE478_Missing_Default_Case_in_Switch__basic_01_good()
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
    CWE478_Missing_Default_Case_in_Switch__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE478_Missing_Default_Case_in_Switch__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
