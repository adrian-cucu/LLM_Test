/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE366_Race_Condition_Within_Thread__global_int_01.c
Label Definition File: CWE366_Race_Condition_Within_Thread.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include "std_thread.h"
#include <limits.h>
#define N_ITERS 1000000
static int gBadInt = 0;
static int gGoodInt = 0;
static stdThreadLock gBadLock = NULL;
static stdThreadLock gGoodLock = NULL;

static void incrementCounter(int *counter, stdThreadLock lock)
{
    int i;
    /* Protect both variants: concurrent non-atomic increments were undefined. */
    stdThreadLockAcquire(lock);
    for (i = 0; i < N_ITERS; ++i)
    {
        /* Repeated calls must not overflow the persistent good counter. */
        if (*counter == INT_MAX) exit(-1);
        ++*counter;
    }
    stdThreadLockRelease(lock);
}
static void helperBad(void *args)
{
    (void)args;
    incrementCounter(&gBadInt, gBadLock);
}
static void helperGood(void *args)
{
    (void)args;
    incrementCounter(&gGoodInt, gGoodLock);
}
static void joinWorker(stdThread thread)
{
    if (thread != NULL)
    {
        /* Never release a worker's lock while a failed join leaves it running. */
        if (!stdThreadJoin(thread)) exit(1);
        stdThreadDestroy(thread);
    }
}
static void runWorkers(void (*worker)(void *))
{
    stdThread threadA = NULL;
    stdThread threadB = NULL;
    if (!stdThreadCreate(worker, NULL, &threadA)) threadA = NULL;
    if (!stdThreadCreate(worker, NULL, &threadB)) threadB = NULL;
    joinWorker(threadA);
    joinWorker(threadB);
}
#ifndef OMITBAD
void CWE366_Race_Condition_Within_Thread__global_int_01_bad(void)
{
    if (!stdThreadLockCreate(&gBadLock)) return;
    gBadInt = 0;
    runWorkers(helperBad);
    stdThreadLockDestroy(gBadLock);
    gBadLock = NULL;
    printIntLine(gBadInt);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    if (!stdThreadLockCreate(&gGoodLock)) return;
    runWorkers(helperGood);
    stdThreadLockDestroy(gGoodLock);
    gGoodLock = NULL;
    printIntLine(gGoodInt);
}
void CWE366_Race_Condition_Within_Thread__global_int_01_good(void)
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
    CWE366_Race_Condition_Within_Thread__global_int_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE366_Race_Condition_Within_Thread__global_int_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
