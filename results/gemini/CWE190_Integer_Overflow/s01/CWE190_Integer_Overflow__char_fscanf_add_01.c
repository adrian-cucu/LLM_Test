/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE190_Integer_Overflow__char_fscanf_add_01.c
Label Definition File: CWE190_Integer_Overflow.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 190 Integer Overflow
 * BadSource: fscanf Read data from the console using fscanf()
 * GoodSource: Set data to a small, non-zero number (two)
 * Sinks: add
 *    GoodSink: Ensure there will not be an overflow before adding 1 to data
 *    BadSink : Add 1 to data, which can cause an overflow
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define GOOD_SOURCE_VALUE 2

static void readCharFromStdin(char *data)
{
    /* Safety fix: check fscanf return value so data remains initialized on input failure */
    if (fscanf(stdin, "%c", data) != 1)
    {
        *data = ' ';
    }
}

static void addOneAndPrintSafely(char data)
{
    /* Safety fix: guard against signed char overflow before adding 1 */
    if (data < CHAR_MAX)
    {
        char result = (char)(data + 1);
        printHexCharLine(result);
    }
    else
    {
        printLine("data value is too large to perform arithmetic safely.");
    }
}

#ifndef OMITBAD

void CWE190_Integer_Overflow__char_fscanf_add_01_bad()
{
    char data = ' ';

    readCharFromStdin(&data);
    addOneAndPrintSafely(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char data = GOOD_SOURCE_VALUE;

    addOneAndPrintSafely(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char data = ' ';

    readCharFromStdin(&data);
    addOneAndPrintSafely(data);
}

void CWE190_Integer_Overflow__char_fscanf_add_01_good()
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
    CWE190_Integer_Overflow__char_fscanf_add_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE190_Integer_Overflow__char_fscanf_add_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
