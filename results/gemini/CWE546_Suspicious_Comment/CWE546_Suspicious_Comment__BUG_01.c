/*
 * @description
 * CWE: 546 Suspicious Comment
 * Sinks: BUG
 *    GoodSink: Comments show no indications of bugs
 *    BadSink : Comment contains the word BUG
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

static void printGreeting(void)
{
    /* Safety fix: removed suspicious comment */
    printLine("Hello");
}

#ifndef OMITBAD

void CWE546_Suspicious_Comment__BUG_01_bad()
{
    printGreeting();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printGreeting();
}

void CWE546_Suspicious_Comment__BUG_01_good()
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
    CWE546_Suspicious_Comment__BUG_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE546_Suspicious_Comment__BUG_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
