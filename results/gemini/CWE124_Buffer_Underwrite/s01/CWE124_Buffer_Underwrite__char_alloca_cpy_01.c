/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE124_Buffer_Underwrite__char_alloca_cpy_01.c
Label Definition File: CWE124_Buffer_Underwrite.stack.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 124 Buffer Underwrite
 * BadSource:  Set data pointer to before the allocated memory buffer
 * GoodSource: Set data pointer to the allocated memory buffer
 * Sink: cpy
 *    BadSink : Copy string to data using strcpy
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_SIZE 100

static void copySourceAndPrint(char *dest, size_t destSize)
{
    char source[BUFFER_SIZE];

    memset(source, 'C', BUFFER_SIZE - 1);
    source[BUFFER_SIZE - 1] = '\0';

    /* Safety fix: use bounded copy into dest to prevent buffer overflow */
    snprintf(dest, destSize, "%s", source);
    printLine(dest);
}

#ifndef OMITBAD

void CWE124_Buffer_Underwrite__char_alloca_cpy_01_bad()
{
    char *dataBuffer = (char *)ALLOCA(BUFFER_SIZE * sizeof(char));
    char *data = NULL;

    memset(dataBuffer, 'A', BUFFER_SIZE - 1);
    dataBuffer[BUFFER_SIZE - 1] = '\0';

    /* Safety fix: keep data pointing to the start of dataBuffer to prevent buffer underwrite */
    data = dataBuffer;
    copySourceAndPrint(data, BUFFER_SIZE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char *dataBuffer = (char *)ALLOCA(BUFFER_SIZE * sizeof(char));
    char *data = NULL;

    memset(dataBuffer, 'A', BUFFER_SIZE - 1);
    dataBuffer[BUFFER_SIZE - 1] = '\0';
    data = dataBuffer;
    copySourceAndPrint(data, BUFFER_SIZE);
}

void CWE124_Buffer_Underwrite__char_alloca_cpy_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE124_Buffer_Underwrite__char_alloca_cpy_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE124_Buffer_Underwrite__char_alloca_cpy_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
