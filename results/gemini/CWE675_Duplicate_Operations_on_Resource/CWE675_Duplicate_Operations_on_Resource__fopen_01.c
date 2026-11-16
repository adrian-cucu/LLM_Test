/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE675_Duplicate_Operations_on_Resource__fopen_01.c
Label Definition File: CWE675_Duplicate_Operations_on_Resource.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 675 Duplicate Operations on Resource
 * BadSource: fopen Open and close a file using fopen() and flose()
 * GoodSource: Open a file using fopen()
 * Sinks:
 *    GoodSink: Do nothing
 *    BadSink : Close the file
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#define BAD_SOURCE_FILENAME "BadSource_fopen.txt"
#define GOOD_SOURCE_FILENAME "GoodSource_fopen.txt"
#define FILE_OPEN_MODE "w+"

static void safeCloseFile(FILE **filePtr)
{
    if (filePtr != NULL && *filePtr != NULL)
    {
        fclose(*filePtr);
        *filePtr = NULL;
    }
}

#ifndef OMITBAD

void CWE675_Duplicate_Operations_on_Resource__fopen_01_bad()
{
    FILE *data = fopen(BAD_SOURCE_FILENAME, FILE_OPEN_MODE);

    /* Safety fix: null-check and clear the FILE pointer after fclose() to prevent a double close. */
    safeCloseFile(&data);
    safeCloseFile(&data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    FILE *data = fopen(GOOD_SOURCE_FILENAME, FILE_OPEN_MODE);
    safeCloseFile(&data);
}

static void goodB2G(void)
{
    FILE *data = fopen(BAD_SOURCE_FILENAME, FILE_OPEN_MODE);
    safeCloseFile(&data);
}

void CWE675_Duplicate_Operations_on_Resource__fopen_01_good()
{
    goodG2B();
    goodB2G();
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
    CWE675_Duplicate_Operations_on_Resource__fopen_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE675_Duplicate_Operations_on_Resource__fopen_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
