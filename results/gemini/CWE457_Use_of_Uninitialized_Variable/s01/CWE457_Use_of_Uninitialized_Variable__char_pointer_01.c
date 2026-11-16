/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE457_Use_of_Uninitialized_Variable__char_pointer_01.c
Label Definition File: CWE457_Use_of_Uninitialized_Variable.c.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 457 Use of Uninitialized Variable
 * BadSource: no_init Don't initialize data
 * GoodSource: Initialize data
 * Sinks: use
 *    GoodSink: Initialize then use data
 *    BadSink : Use data
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define DEFAULT_STRING "string"

#ifndef OMITBAD

void CWE457_Use_of_Uninitialized_Variable__char_pointer_01_bad()
{
    /* Safety fix: Initialize pointer before passing it to printLine() */
    const char *data = DEFAULT_STRING;

    printLine(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    const char *data = DEFAULT_STRING;

    printLine(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    const char *data = DEFAULT_STRING;

    printLine(data);
}

void CWE457_Use_of_Uninitialized_Variable__char_pointer_01_good()
{
    goodG2B();
    goodB2G();
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
    CWE457_Use_of_Uninitialized_Variable__char_pointer_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE457_Use_of_Uninitialized_Variable__char_pointer_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
