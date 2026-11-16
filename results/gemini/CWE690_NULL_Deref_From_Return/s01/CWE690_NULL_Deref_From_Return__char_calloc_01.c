/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE690_NULL_Deref_From_Return__char_calloc_01.c
Label Definition File: CWE690_NULL_Deref_From_Return.free.label.xml
Template File: source-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 690 Unchecked Return Value To NULL Pointer
 * BadSource: calloc Allocate data using calloc()
 * Sinks:
 *    GoodSink: Check to see if the data allocation failed and if not, use data
 *    BadSink : Don't check for NULL and use data
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_CHAR_COUNT 20
#define INIT_TEXT "Initialize"

static void init_print_and_free(char *data, size_t capacity)
{
    /* Safety fix: check for NULL before dereferencing allocated memory */
    if (data != NULL)
    {
        snprintf(data, capacity, "%s", INIT_TEXT);
        printLine(data);
        free(data);
    }
}

#ifndef OMITBAD

void CWE690_NULL_Deref_From_Return__char_calloc_01_bad()
{
    char *data = (char *)calloc(BUFFER_CHAR_COUNT, sizeof(char));
    init_print_and_free(data, BUFFER_CHAR_COUNT);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodB2G() uses the BadSource with the GoodSink */
static void goodB2G()
{
    char *data = (char *)calloc(BUFFER_CHAR_COUNT, sizeof(char));
    init_print_and_free(data, BUFFER_CHAR_COUNT);
}

void CWE690_NULL_Deref_From_Return__char_calloc_01_good()
{
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
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE690_NULL_Deref_From_Return__char_calloc_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE690_NULL_Deref_From_Return__char_calloc_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
