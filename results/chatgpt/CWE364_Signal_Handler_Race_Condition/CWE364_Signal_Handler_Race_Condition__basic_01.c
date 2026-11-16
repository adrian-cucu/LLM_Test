/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE364_Signal_Handler_Race_Condition__basic_01.c
Label Definition File: CWE364_Signal_Handler_Race_Condition__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <signal.h>
typedef struct _structSigAtomic
{
    sig_atomic_t val;
} structSigAtomic;
structSigAtomic *CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicBad = NULL;
structSigAtomic *CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicGood = NULL;
static volatile sig_atomic_t badSignal = 0;
static volatile sig_atomic_t goodSignal = 0;

/* A handler may set a volatile sig_atomic_t, but must not traverse heap pointers.
 * Defer the heap update to normal execution so freeing cannot race the handler. */
static void helperBad(int sig)
{
    (void)sig;
    badSignal = 1;
}
static void helperGood(int sig)
{
    (void)sig;
    goodSignal = 1;
}
static void exerciseSignal(structSigAtomic **target,
                           volatile sig_atomic_t *pending,
                           void (*handler)(int), int resetDuringFree)
{
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) exit(1);
    free(*target);
    *target = malloc(sizeof(**target));
    if (*target == NULL) exit(-1);
    (*target)->val = 1;
    *pending = 0;
    if (signal(SIGINT, handler) == SIG_ERR) exit(1);
    if (*pending) (*target)->val = 2;
    if (resetDuringFree && signal(SIGINT, SIG_DFL) == SIG_ERR) exit(1);
    free(*target);
    *target = NULL;
    if (resetDuringFree && signal(SIGINT, handler) == SIG_ERR) exit(1);
}
#ifndef OMITBAD
void CWE364_Signal_Handler_Race_Condition__basic_01_bad(void)
{
    exerciseSignal(&CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicBad,
                   &badSignal, helperBad, 0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    exerciseSignal(&CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicGood,
                   &goodSignal, helperGood, 1);
}
void CWE364_Signal_Handler_Race_Condition__basic_01_good(void)
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
    CWE364_Signal_Handler_Race_Condition__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE364_Signal_Handler_Race_Condition__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
