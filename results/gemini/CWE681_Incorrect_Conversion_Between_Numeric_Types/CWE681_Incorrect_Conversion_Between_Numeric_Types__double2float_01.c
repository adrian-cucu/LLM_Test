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

static double read_double_from_stdin(void)
{
    char inputBuffer[CHAR_ARRAY_SIZE] = "";
    double doubleNumber = 0.0;

    if (fgets(inputBuffer, CHAR_ARRAY_SIZE, stdin) != NULL)
    {
        doubleNumber = atof(inputBuffer);
    }
    else
    {
        printLine("fgets() failed.");
    }

    return doubleNumber;
}

static void print_checked_float(double doubleNumber)
{
    /* Safety fix: verify doubleNumber is within representable float range before casting */
    if (doubleNumber > (double)FLT_MAX ||
        doubleNumber < -(double)FLT_MAX ||
        (doubleNumber != 0.0 && doubleNumber > -(double)FLT_MIN && doubleNumber < (double)FLT_MIN))
    {
        printLine("Value is too small or large to be represented as a float");
    }
    else
    {
        printFloatLine((float)doubleNumber);
    }
}

#ifndef OMITBAD

void CWE681_Incorrect_Conversion_Between_Numeric_Types__double2float_01_bad()
{
    double doubleNumber = read_double_from_stdin();
    print_checked_float(doubleNumber);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    double doubleNumber = read_double_from_stdin();
    if (doubleNumber > FLT_MAX || doubleNumber < FLT_MIN)
    {
        printLine("Value is too small or large to be represented as a float");
    }
    else
    {
        printFloatLine((float)doubleNumber);
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
