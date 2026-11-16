/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE366_Race_Condition_Within_Thread__global_int_01.c
Label Definition File: CWE366_Race_Condition_Within_Thread.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 366 Race Condition Within a Thread
 * Sinks: global_int
 *    GoodSink: Acquire a lock before attempting to increment a global integer using another function
 *    BadSink : Do not acquire a lock before attempting to increment a global integer using another function
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"
#include "std_thread.h"

#define N_ITERS 1000000

static int gBadInt = 0;
static stdThreadLock gBadLock = NULL;
static int gGoodInt = 0;
static stdThreadLock gGoodLock = NULL;

static void helperBad(void *args)
{
    int i = 0;
    (void)args;

    /* Safety fix: acquire lock before incrementing shared global integer */
    stdThreadLockAcquire(gBadLock);
    for (i = 0; i < N_ITERS; i++)
    {
        gBadInt = gBadInt + 1;
    }
    stdThreadLockRelease(gBadLock);
}

static void helperGood(void *args)
{
    int i = 0;
    (void)args;

    stdThreadLockAcquire(gGoodLock);
    for (i = 0; i < N_ITERS; i++)
    {
        gGoodInt = gGoodInt + 1;
    }
    stdThreadLockRelease(gGoodLock);
}

static void runTwoThreadIncrement(void (*worker)(void *), int *sharedCounter, stdThreadLock *lock)
{
    stdThread threadA = NULL;
    stdThread threadB = NULL;

    *sharedCounter = 0;
    if (!stdThreadLockCreate(lock))
    {
        return;
    }

    if (!stdThreadCreate(worker, NULL, &threadA))
    {
        threadA = NULL;
    }
    if (!stdThreadCreate(worker, NULL, &threadB))
    {
        threadB = NULL;
    }

    if (threadA != NULL && stdThreadJoin(threadA))
    {
        stdThreadDestroy(threadA);
    }
    if (threadB != NULL && stdThreadJoin(threadB))
    {
        stdThreadDestroy(threadB);
    }

    stdThreadLockDestroy(*lock);
    *lock = NULL;
    printIntLine(*sharedCounter);
}

#ifndef OMITBAD

void CWE366_Race_Condition_Within_Thread__global_int_01_bad()
{
    runTwoThreadIncrement(helperBad, &gBadInt, &gBadLock);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    runTwoThreadIncrement(helperGood, &gGoodInt, &gGoodLock);
}

void CWE366_Race_Condition_Within_Thread__global_int_01_good()
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
    CWE366_Race_Condition_Within_Thread__global_int_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE366_Race_Condition_Within_Thread__global_int_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
