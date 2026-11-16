/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE667_Improper_Locking__basic_01.c
Label Definition File: CWE667_Improper_Locking__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 667 Improper Locking
 * Sinks:
 *    GoodSink: Acquire a lock before releasing it
 *    BadSink : Release the lock before acquiring it
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include "std_thread.h"

static void runLockLifecycle(stdThreadLock *lock)
{
    printLine("Creating lock...");
    if (!stdThreadLockCreate(lock))
    {
        printLine("Could not create lock");
        exit(1);
    }
    printLine("Acquiring lock...");
    stdThreadLockAcquire(*lock);
    printLine("Releasing lock...");
    stdThreadLockRelease(*lock);
    printLine("Destroying lock...");
    stdThreadLockDestroy(*lock);
    *lock = NULL;
}

#ifndef OMITBAD

void CWE667_Improper_Locking__basic_01_bad()
{
    static stdThreadLock badLock = NULL;

    /* Safety fix: release and destroy the lock after acquiring it to prevent deadlock and resource leaks. */
    runLockLifecycle(&badLock);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    static stdThreadLock goodLock = NULL;
    runLockLifecycle(&goodLock);
}

void CWE667_Improper_Locking__basic_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE667_Improper_Locking__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE667_Improper_Locking__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
