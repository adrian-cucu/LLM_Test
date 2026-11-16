/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE126_Buffer_Overread__char_alloca_loop_01.c
Label Definition File: CWE126_Buffer_Overread.stack.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 126 Buffer Over-read
 * BadSource:  Set data pointer to a small buffer
 * GoodSource: Set data pointer to a large buffer
 * Sink: loop
 *    BadSink : Copy data to string using a loop
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define SMALL_BUFFER_SIZE 50
#define LARGE_BUFFER_SIZE 100

static void initBufferWithChar(char *buffer, size_t bufferSize, char fillChar)
{
    if (buffer == NULL || bufferSize == 0)
    {
        return;
    }
    memset(buffer, fillChar, bufferSize - 1);
    buffer[bufferSize - 1] = '\0';
}

static void copyDataLoopAndPrint(const char *data)
{
    char dest[LARGE_BUFFER_SIZE];
    size_t i = 0;
    size_t destLen = 0;
    size_t dataLen = 0;
    size_t copyLen = 0;

    initBufferWithChar(dest, sizeof(dest), 'C');
    destLen = strlen(dest);
    dataLen = (data != NULL) ? strlen(data) : 0;

    /* Safety fix: bound loop by strlen(data) as well as destLen to prevent buffer overread */
    copyLen = (dataLen < destLen) ? dataLen : destLen;
    for (i = 0; i < copyLen; i++)
    {
        dest[i] = data[i];
    }
    dest[copyLen] = '\0';
    printLine(dest);
}

#ifndef OMITBAD

void CWE126_Buffer_Overread__char_alloca_loop_01_bad()
{
    char *dataBadBuffer = (char *)ALLOCA(SMALL_BUFFER_SIZE * sizeof(char));
    char *dataGoodBuffer = (char *)ALLOCA(LARGE_BUFFER_SIZE * sizeof(char));
    char *data = NULL;

    initBufferWithChar(dataBadBuffer, SMALL_BUFFER_SIZE, 'A');
    initBufferWithChar(dataGoodBuffer, LARGE_BUFFER_SIZE, 'A');
    data = dataBadBuffer;
    copyDataLoopAndPrint(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char *dataBadBuffer = (char *)ALLOCA(SMALL_BUFFER_SIZE * sizeof(char));
    char *dataGoodBuffer = (char *)ALLOCA(LARGE_BUFFER_SIZE * sizeof(char));
    char *data = NULL;

    initBufferWithChar(dataBadBuffer, SMALL_BUFFER_SIZE, 'A');
    initBufferWithChar(dataGoodBuffer, LARGE_BUFFER_SIZE, 'A');
    data = dataGoodBuffer;
    copyDataLoopAndPrint(data);
}

void CWE126_Buffer_Overread__char_alloca_loop_01_good()
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
    CWE126_Buffer_Overread__char_alloca_loop_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE126_Buffer_Overread__char_alloca_loop_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
