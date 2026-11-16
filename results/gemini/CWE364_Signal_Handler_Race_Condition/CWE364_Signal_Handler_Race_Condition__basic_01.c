/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE364_Signal_Handler_Race_Condition__basic_01.c
Label Definition File: CWE364_Signal_Handler_Race_Condition__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 364 Signal Handler Race Condition
 * Sinks:
 *    GoodSink: Disable the signal handler while performing non-atomic operations
 *    BadSink : Do not disable the signal handler while performing non-atomic operations
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <signal.h>

typedef struct _structSigAtomic
{
    sig_atomic_t val;
} structSigAtomic;

structSigAtomic *CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicBad = NULL;
structSigAtomic *CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicGood = NULL;

static void helperBad(int sig)
{
    (void)sig;
    if (CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicBad != NULL)
    {
        CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicBad->val = 2;
    }
}

static void helperGood(int sig)
{
    (void)sig;
    if (CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicGood != NULL)
    {
        CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicGood->val = 2;
    }
}

static void runSigAtomicWithGuard(structSigAtomic **target, void (*handler)(int))
{
    structSigAtomic *allocated = NULL;

    signal(SIGINT, SIG_DFL);
    if (*target != NULL)
    {
        free(*target);
        *target = NULL;
    }

    allocated = (structSigAtomic *)malloc(sizeof(structSigAtomic));
    if (allocated == NULL)
    {
        exit(-1);
    }

    *target = allocated;
    (*target)->val = 1;
    signal(SIGINT, handler);

    /* Safety fix: disable signal handler around non-atomic free and NULL assignment */
    signal(SIGINT, SIG_DFL);
    if (*target != NULL)
    {
        free(*target);
        *target = NULL;
    }
    signal(SIGINT, handler);
}

#ifndef OMITBAD

void CWE364_Signal_Handler_Race_Condition__basic_01_bad()
{
    runSigAtomicWithGuard(&CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicBad, helperBad);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    runSigAtomicWithGuard(&CWE364_Signal_Handler_Race_Condition__basic_01StructSigAtomicGood, helperGood);
}

void CWE364_Signal_Handler_Race_Condition__basic_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE364_Signal_Handler_Race_Condition__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE364_Signal_Handler_Race_Condition__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
