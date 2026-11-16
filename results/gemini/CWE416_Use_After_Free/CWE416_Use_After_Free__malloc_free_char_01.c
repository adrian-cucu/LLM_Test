/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__malloc_free_char_01.c
Label Definition File: CWE416_Use_After_Free__malloc_free.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 416 Use After Free
 * BadSource:  Allocate data using malloc(), initialize memory block, and Deallocate data using free()
 * GoodSource: Allocate data using malloc() and initialize memory block
 * Sinks:
 *    GoodSink: Do nothing
 *    BadSink : Use data
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_SIZE 100
#define FILL_CHAR 'A'

static char *createFilledBuffer(size_t size, char fillChar)
{
    char *data = (char *)malloc(size * sizeof(char));
    if (data == NULL)
    {
        exit(-1);
    }

    if (size > 0)
    {
        memset(data, fillChar, size - 1);
        data[size - 1] = '\0';
    }

    return data;
}

#ifndef OMITBAD

void CWE416_Use_After_Free__malloc_free_char_01_bad()
{
    char *data = createFilledBuffer(BUFFER_SIZE, FILL_CHAR);

    /* Safety fix: Use data before freeing and nullify the pointer to prevent use-after-free */
    printLine(data);
    free(data);
    data = NULL;
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char *data = createFilledBuffer(BUFFER_SIZE, FILL_CHAR);

    printLine(data);
    /* Safety fix: Free allocated memory after use to prevent a memory leak */
    free(data);
    data = NULL;
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char *data = createFilledBuffer(BUFFER_SIZE, FILL_CHAR);

    free(data);
    data = NULL;
}

void CWE416_Use_After_Free__malloc_free_char_01_good()
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
    CWE416_Use_After_Free__malloc_free_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE416_Use_After_Free__malloc_free_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
