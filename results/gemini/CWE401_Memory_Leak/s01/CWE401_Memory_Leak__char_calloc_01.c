/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE401_Memory_Leak__char_calloc_01.c
Label Definition File: CWE401_Memory_Leak.c.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 401 Memory Leak
 * BadSource: calloc Allocate data using calloc()
 * GoodSource: Allocate data on the stack
 * Sinks:
 *    GoodSink: call free() on data
 *    BadSink : no deallocation of data
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define STRING_BUFFER_SIZE 100
#define INITIAL_TEXT "A String"

static char *allocateAndInitHeapString(size_t count, const char *text)
{
    char *data = (char *)calloc(count, sizeof(char));
    if (data == NULL)
    {
        exit(-1);
    }

    snprintf(data, count, "%s", text);
    return data;
}

#ifndef OMITBAD

void CWE401_Memory_Leak__char_calloc_01_bad()
{
    char *data = allocateAndInitHeapString(STRING_BUFFER_SIZE, INITIAL_TEXT);

    printLine(data);
    /* Safety fix: Free heap-allocated memory to prevent a memory leak */
    free(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char *data = (char *)ALLOCA(STRING_BUFFER_SIZE * sizeof(char));

    snprintf(data, STRING_BUFFER_SIZE, "%s", INITIAL_TEXT);
    printLine(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char *data = allocateAndInitHeapString(STRING_BUFFER_SIZE, INITIAL_TEXT);

    printLine(data);
    free(data);
}

void CWE401_Memory_Leak__char_calloc_01_good()
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
    CWE401_Memory_Leak__char_calloc_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE401_Memory_Leak__char_calloc_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
