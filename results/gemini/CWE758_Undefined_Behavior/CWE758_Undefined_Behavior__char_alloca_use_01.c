/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE758_Undefined_Behavior__char_alloca_use_01.c
Label Definition File: CWE758_Undefined_Behavior.alloc.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 758 Undefined Behavior
 * Sinks: alloca_use
 *    GoodSink: Initialize then use data
 *    BadSink : Use data from alloca without initialization
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define DEFAULT_CHAR_VALUE 5

static void init_and_print_alloca_char(char initialValue)
{
    char *pointer = (char *)ALLOCA(sizeof(char));
    /* Safety fix: initialize allocated memory before reading to avoid undefined behavior */
    if (pointer != NULL)
    {
        *pointer = initialValue;
        printHexCharLine(*pointer);
    }
}

#ifndef OMITBAD

void CWE758_Undefined_Behavior__char_alloca_use_01_bad()
{
    init_and_print_alloca_char(DEFAULT_CHAR_VALUE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    init_and_print_alloca_char(DEFAULT_CHAR_VALUE);
}

void CWE758_Undefined_Behavior__char_alloca_use_01_good()
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
    CWE758_Undefined_Behavior__char_alloca_use_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE758_Undefined_Behavior__char_alloca_use_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
