/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE665_Improper_Initialization__char_cat_01.c
Label Definition File: CWE665_Improper_Initialization.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 665 Improper Initialization
 * BadSource:  Do not initialize data properly
 * GoodSource: Initialize data
 * Sink: cat
 *    BadSink : Copy string to data using strcat
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_SIZE 100
#define SOURCE_FILL_CHAR 'C'

static void appendAndPrint(char *data, size_t dataSize)
{
    char source[BUFFER_SIZE];
    size_t currentLen = strlen(data);

    memset(source, SOURCE_FILL_CHAR, BUFFER_SIZE - 1);
    source[BUFFER_SIZE - 1] = '\0';

    if (currentLen < dataSize - 1)
    {
        strncat(data, source, dataSize - currentLen - 1);
    }
    printLine(data);
}

#ifndef OMITBAD

void CWE665_Improper_Initialization__char_cat_01_bad()
{
    char dataBuffer[BUFFER_SIZE];
    char *data = dataBuffer;

    /* Safety fix: initialize dataBuffer with a null terminator before calling strcat/strncat. */
    data[0] = '\0';
    appendAndPrint(data, BUFFER_SIZE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    char dataBuffer[BUFFER_SIZE];
    char *data = dataBuffer;

    data[0] = '\0';
    appendAndPrint(data, BUFFER_SIZE);
}

void CWE665_Improper_Initialization__char_cat_01_good()
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
    CWE665_Improper_Initialization__char_cat_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE665_Improper_Initialization__char_cat_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
