/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument__basic_01.c
Label Definition File: CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 688 Function Call With Incorrect Variable or Reference as Argument
 * Sinks:
 *    GoodSink: Use the correct format to print a string
 *    BadSink : Use a string format to print an int
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define DEST_SIZE 100
#define SAMPLE_INT_VALUE 5

static void format_and_print_int(int value)
{
    char dest[DEST_SIZE] = "";
    /* Safety fix: use %d format specifier matching the int argument and snprintf for bounds safety */
    snprintf(dest, sizeof(dest), "%d", value);
    printLine(dest);
}

#ifndef OMITBAD

void CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument__basic_01_bad()
{
    format_and_print_int(SAMPLE_INT_VALUE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    format_and_print_int(SAMPLE_INT_VALUE);
}

void CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument__basic_01_good()
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
    CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
