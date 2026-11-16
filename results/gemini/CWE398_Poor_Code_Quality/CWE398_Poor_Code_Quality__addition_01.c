/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE398_Poor_Code_Quality__addition_01.c
Label Definition File: CWE398_Poor_Code_Quality.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 398 Poor Code Quality
 * Sinks: addition
 *    GoodSink: Adding two ints and storing the result
 *    BadSink : Adding two ints but not storing the result has no effect
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define FIRST_OPERAND 1
#define SECOND_OPERAND 1

static void addAndPrint(int first, int second)
{
    int intSum = 0;

    printIntLine(intSum);
    /* Safety fix: Store the result of the addition rather than leaving a no-op expression */
    intSum = first + second;
    printIntLine(intSum);
}

#ifndef OMITBAD

void CWE398_Poor_Code_Quality__addition_01_bad()
{
    addAndPrint(FIRST_OPERAND, SECOND_OPERAND);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    addAndPrint(FIRST_OPERAND, SECOND_OPERAND);
}

void CWE398_Poor_Code_Quality__addition_01_good()
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
    CWE398_Poor_Code_Quality__addition_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE398_Poor_Code_Quality__addition_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
