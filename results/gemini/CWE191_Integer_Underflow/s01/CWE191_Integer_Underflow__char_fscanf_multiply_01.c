/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE191_Integer_Underflow__char_fscanf_multiply_01.c
Label Definition File: CWE191_Integer_Underflow.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 191 Integer Underflow
 * BadSource: fscanf Read data from the console using fscanf()
 * GoodSource: Set data to a small, non-zero number (negative two)
 * Sinks: multiply
 *    GoodSink: Ensure there will not be an underflow before multiplying data by 2
 *    BadSink : If data is negative, multiply by 2, which can cause an underflow
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define GOOD_SOURCE_VALUE (-2)
#define MULTIPLIER 2

static void readCharFromStdin(char *data)
{
    /* Safety fix: check fscanf return value so data remains initialized on input failure */
    if (fscanf(stdin, "%c", data) != 1)
    {
        *data = ' ';
    }
}

static void multiplyByTwoAndPrintSafely(char data)
{
    if (data >= 0)
    {
        return;
    }

    /* Safety fix: guard against signed char underflow before multiplying by 2 */
    if (data >= (CHAR_MIN / MULTIPLIER))
    {
        char result = (char)(data * MULTIPLIER);
        printHexCharLine(result);
    }
    else
    {
        printLine("data value is too small to perform multiplication.");
    }
}

#ifndef OMITBAD

void CWE191_Integer_Underflow__char_fscanf_multiply_01_bad()
{
    char data = ' ';

    readCharFromStdin(&data);
    multiplyByTwoAndPrintSafely(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char data = GOOD_SOURCE_VALUE;

    multiplyByTwoAndPrintSafely(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char data = ' ';

    readCharFromStdin(&data);
    multiplyByTwoAndPrintSafely(data);
}

void CWE191_Integer_Underflow__char_fscanf_multiply_01_good()
{
    goodG2B();
    goodB2G();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE191_Integer_Underflow__char_fscanf_multiply_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE191_Integer_Underflow__char_fscanf_multiply_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
