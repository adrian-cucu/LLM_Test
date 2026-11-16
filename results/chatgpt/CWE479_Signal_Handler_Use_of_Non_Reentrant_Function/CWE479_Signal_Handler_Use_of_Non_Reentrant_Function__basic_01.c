/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01.c
Label Definition File: CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <signal.h>

static volatile sig_atomic_t volatileSigAtomic = 0;
static void helperBad(int sig)
{
    /* Allocator calls are not signal-safe; record the signal without them. */
    volatileSigAtomic = sig;
}
static void helperGood(int sig)
{
    volatileSigAtomic = sig;
}

static void installHandler(void (*handler)(int))
{
    /* Registration errors can be reported here, outside the signal handler. */
    if (signal(SIGINT, handler) == SIG_ERR)
    {
        printLine("signal() failed");
    }
}
#ifndef OMITBAD
void CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_bad()
{
    installHandler(helperBad);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    installHandler(helperGood);
}
void CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_good()
{
    good1();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE479_Signal_Handler_Use_of_Non_Reentrant_Function__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
