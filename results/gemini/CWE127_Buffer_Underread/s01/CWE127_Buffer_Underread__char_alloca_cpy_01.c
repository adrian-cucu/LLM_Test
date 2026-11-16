/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE127_Buffer_Underread__char_alloca_cpy_01.c
Label Definition File: CWE127_Buffer_Underread.stack.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 127 Buffer Under-read
 * BadSource:  Set data pointer to before the allocated memory buffer
 * GoodSource: Set data pointer to the allocated memory buffer
 * Sink: cpy
 *    BadSink : Copy data to string using strcpy
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define SRC_BUFFER_SIZE 100
#define DEST_BUFFER_SIZE (SRC_BUFFER_SIZE * 2)

static void copyToDestAndPrint(const char *data)
{
    char dest[DEST_BUFFER_SIZE];

    memset(dest, 'C', DEST_BUFFER_SIZE - 1);
    dest[DEST_BUFFER_SIZE - 1] = '\0';

    /* Safety fix: use bounded copy into dest */
    snprintf(dest, sizeof(dest), "%s", data);
    printLine(dest);
}

#ifndef OMITBAD

void CWE127_Buffer_Underread__char_alloca_cpy_01_bad()
{
    char *dataBuffer = (char *)ALLOCA(SRC_BUFFER_SIZE * sizeof(char));
    char *data = NULL;

    memset(dataBuffer, 'A', SRC_BUFFER_SIZE - 1);
    dataBuffer[SRC_BUFFER_SIZE - 1] = '\0';

    /* Safety fix: keep data pointing to the start of dataBuffer to prevent buffer underread */
    data = dataBuffer;
    copyToDestAndPrint(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char *dataBuffer = (char *)ALLOCA(SRC_BUFFER_SIZE * sizeof(char));
    char *data = NULL;

    memset(dataBuffer, 'A', SRC_BUFFER_SIZE - 1);
    dataBuffer[SRC_BUFFER_SIZE - 1] = '\0';
    data = dataBuffer;
    copyToDestAndPrint(data);
}

void CWE127_Buffer_Underread__char_alloca_cpy_01_good()
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
    CWE127_Buffer_Underread__char_alloca_cpy_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE127_Buffer_Underread__char_alloca_cpy_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
