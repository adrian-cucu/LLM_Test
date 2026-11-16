/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE832_Unlock_of_Resource_That_is_Not_Locked__basic_01.c
Label Definition File: CWE832_Unlock_of_Resource_That_is_Not_Locked__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 832 Unlock Of Resource That Is Not Locked
 * Sinks:
 *    GoodSink: Acquire a lock before releasing it
 *    BadSink : Release the lock before acquiring it
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include "std_thread.h"

static void run_lock_cycle(stdThreadLock *lockPtr)
{
    printLine("Creating lock...");
    if (!stdThreadLockCreate(lockPtr))
    {
        printLine("Could not create lock");
        exit(1);
    }
    /* Safety fix: acquire the lock before releasing it */
    printLine("Acquiring lock...");
    stdThreadLockAcquire(*lockPtr);
    printLine("Releasing lock...");
    stdThreadLockRelease(*lockPtr);
    printLine("Destroying lock...");
    stdThreadLockDestroy(*lockPtr);
    *lockPtr = NULL;
}

#ifndef OMITBAD

void CWE832_Unlock_of_Resource_That_is_Not_Locked__basic_01_bad()
{
    static stdThreadLock badLock = NULL;
    run_lock_cycle(&badLock);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    static stdThreadLock goodLock = NULL;
    run_lock_cycle(&goodLock);
}

void CWE832_Unlock_of_Resource_That_is_Not_Locked__basic_01_good()
{
    good1();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE832_Unlock_of_Resource_That_is_Not_Locked__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE832_Unlock_of_Resource_That_is_Not_Locked__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
