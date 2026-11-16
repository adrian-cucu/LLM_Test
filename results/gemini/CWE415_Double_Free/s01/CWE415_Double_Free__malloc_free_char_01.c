/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_char_01.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_SIZE 100

static char *allocateCharBuffer(size_t count)
{
    char *data = (char *)malloc(count * sizeof(char));
    if (data == NULL)
    {
        exit(-1);
    }
    return data;
}

static void safeFreeCharBuffer(char **bufferPtr)
{
    if (bufferPtr != NULL && *bufferPtr != NULL)
    {
        free(*bufferPtr);
        *bufferPtr = NULL;
    }
}

#ifndef OMITBAD

void CWE415_Double_Free__malloc_free_char_01_bad()
{
    char *data = allocateCharBuffer(BUFFER_SIZE);

    /* Safety fix: Free the buffer once and nullify the pointer to prevent a double free */
    safeFreeCharBuffer(&data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char *data = allocateCharBuffer(BUFFER_SIZE);

    safeFreeCharBuffer(&data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char *data = allocateCharBuffer(BUFFER_SIZE);

    safeFreeCharBuffer(&data);
}

void CWE415_Double_Free__malloc_free_char_01_good()
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
    CWE415_Double_Free__malloc_free_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
