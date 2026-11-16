/*
 * @description
 * CWE: 479 Signal Handler Use of Non-Reentrant Function
 * Sinks:
 *    GoodSink: Don't call a function from within the signal handler
 *    BadSink : malloc() and free() inside a signal handler
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#include <signal.h>

static volatile sig_atomic_t volatileSigAtomic = 0;

static void helperBad(int sig)
{
    /* Safety fix: avoid non-reentrant malloc/free/exit in signal handler; only set sig_atomic_t flag */
    volatileSigAtomic = sig;
}

static void helperGood(int sig)
{
    volatileSigAtomic = sig;
}

#ifndef OMITBAD

void CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_bad()
{
    signal(SIGINT, helperBad);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    signal(SIGINT, helperGood);
}

void CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_good()
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
    CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
