/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE391_Unchecked_Error_Condition__sqrt_01.c
Label Definition File: CWE391_Unchecked_Error_Condition.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 391 Unchecked Error Condition
 * Sinks: sqrt
 *    GoodSink: Perform error checks and handling
 *    BadSink : Do not check if sqrt() failed
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <errno.h>
#include <math.h>

#define SQRT_TEST_VALUE (-1.0)

static void computeAndPrintSqrt(double input)
{
    double doubleNumber = 0.0;

    /* Safety fix: Clear errno before calling sqrt() and check for domain errors */
    errno = 0;
    doubleNumber = sqrt(input);
    if (errno == EDOM || isnan(doubleNumber))
    {
        printLine("sqrt() failed");
        exit(1);
    }

    printDoubleLine(doubleNumber);
}

#ifndef OMITBAD

void CWE391_Unchecked_Error_Condition__sqrt_01_bad()
{
    computeAndPrintSqrt(SQRT_TEST_VALUE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    computeAndPrintSqrt(SQRT_TEST_VALUE);
}

void CWE391_Unchecked_Error_Condition__sqrt_01_good()
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
    CWE391_Unchecked_Error_Condition__sqrt_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE391_Unchecked_Error_Condition__sqrt_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
