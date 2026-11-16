/*
 * @description
 * CWE: 511 Logic Time Bomb
 * Sinks: counter
 *    GoodSink: If counter reaches a certain value, do something harmless
 *    BadSink : If counter reaches a certain value, do something bad
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define COUNT_CHECK 20000

static void runCounterLoop(void)
{
    int count = 0;

    /* Safety fix: bound loop to avoid infinite loop and signed integer overflow UB */
    for (count = 0; count <= COUNT_CHECK; count++)
    {
        if (count == COUNT_CHECK)
        {
            /* Safety fix: replace destructive UNLINK time bomb with harmless message */
            printLine("Happy New Year!");
        }
    }
}

#ifndef OMITBAD

void CWE511_Logic_Time_Bomb__counter_01_bad()
{
    runCounterLoop();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    runCounterLoop();
}

void CWE511_Logic_Time_Bomb__counter_01_good()
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
    CWE511_Logic_Time_Bomb__counter_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE511_Logic_Time_Bomb__counter_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
