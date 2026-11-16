/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE681_Incorrect_Conversion_Between_Numeric_Types__double2float_01.c
Label Definition File: CWE681_Incorrect_Conversion_Between_Numeric_Types.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 681 Incorrect Conversion Between Numeric Types
 * Sinks: double2float
 *    GoodSink: check for conversion error
 *    BadSink : explicit cast
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <float.h>
#define CHAR_ARRAY_SIZE 256

#if !defined(OMITBAD) || !defined(OMITGOOD)
static double readDoubleNumber(void)
{
    char inputBuffer[CHAR_ARRAY_SIZE];
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
    {
        printLine("fgets() failed.");
        return 0.0;
    }
    /* strtod has defined range-error handling, unlike atof on overflow. */
    return strtod(inputBuffer, NULL);
}
#endif

#ifndef OMITBAD

void CWE681_Incorrect_Conversion_Between_Numeric_Types__double2float_01_bad()
{
    {
        double doubleNumber = readDoubleNumber();
        /* Enter: 1e-50, result should be 0.0 (for bad case)
         *
         * Note: alternate input
         * 999999999999999999999999999999999999999999999999999999999999999
         */
        /* Conversion outside the finite float range has undefined behavior in C. */
        if (doubleNumber > FLT_MAX || doubleNumber < -FLT_MAX)
        {
            printLine("Value is too small or large to be represented as a float");
            return;
        }
        printFloatLine((float)doubleNumber);
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    {
        double doubleNumber = readDoubleNumber();
        /* Enter: 1e-50, result should be 0.0 (for bad case)
         *
         * Note: alternate input
         * 999999999999999999999999999999999999999999999999999999999999999
         */
        /* FIX: check to make sure conversion is safe */
        if (doubleNumber > FLT_MAX || doubleNumber < FLT_MIN)
        {
            printLine("Value is too small or large to be represented as a float");
        }
        else
        {
            printFloatLine((float)doubleNumber);
        }
    }
}

void CWE681_Incorrect_Conversion_Between_Numeric_Types__double2float_01_good()
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
    CWE681_Incorrect_Conversion_Between_Numeric_Types__double2float_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE681_Incorrect_Conversion_Between_Numeric_Types__double2float_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
