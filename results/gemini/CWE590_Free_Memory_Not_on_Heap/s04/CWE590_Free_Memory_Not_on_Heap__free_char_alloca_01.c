/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE590_Free_Memory_Not_on_Heap__free_char_alloca_01.c
Label Definition File: CWE590_Free_Memory_Not_on_Heap__free.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 590 Free Memory Not on Heap
 * BadSource: alloca Data buffer is allocated on the stack with alloca()
 * GoodSource: Allocate memory on the heap
 * Sink:
 *    BadSink : Print then free data
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_SIZE 100
#define FILL_CHAR 'A'

static char *createFilledHeapBuffer(size_t size, char fillChar)
{
    char *buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL)
    {
        printLine("malloc() failed");
        exit(1);
    }
    memset(buffer, fillChar, size - 1);
    buffer[size - 1] = '\0';
    return buffer;
}

static void printAndFreeBuffer(char **bufferPtr)
{
    if (bufferPtr != NULL && *bufferPtr != NULL)
    {
        printLine(*bufferPtr);
        free(*bufferPtr);
        *bufferPtr = NULL;
    }
}

#ifndef OMITBAD

void CWE590_Free_Memory_Not_on_Heap__free_char_alloca_01_bad()
{
    /* Safety fix: allocate on the heap with malloc() instead of ALLOCA() so free() is valid. */
    char *data = createFilledHeapBuffer(BUFFER_SIZE, FILL_CHAR);
    printAndFreeBuffer(&data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    char *data = createFilledHeapBuffer(BUFFER_SIZE, FILL_CHAR);
    printAndFreeBuffer(&data);
}

void CWE590_Free_Memory_Not_on_Heap__free_char_alloca_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE590_Free_Memory_Not_on_Heap__free_char_alloca_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_char_alloca_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
