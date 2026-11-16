/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE176_Improper_Handling_of_Unicode_Encoding__w32_01.c
Label Definition File: CWE176_Improper_Handling_of_Unicode_Encoding__w32.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 176 Improper Handling of Unicode Encoding
 * BadSource:  Initialize data as a large unicode string
 * GoodSource: Initialize data as a small unicode string
 * Sinks:
 *    GoodSink: Ensure the array index is valid
 *    BadSink : Improperly check the array index by not checking the upper bound
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#pragma comment( lib, "advapi32" )

#define WIDE_BUFFER_SIZE 100
#define CONVERTED_BUFFER_SIZE 10
#define LARGE_UNICODE_STR L"\\u9580\\u961c\\u9640\\u963f\\u963b\\u9644\\u9580\\u961c\\u9640\\u963f\\u963b\\u9644"
#define SMALL_UNICODE_STR L"\\u9580"

static void convertWideToMultiByte(const wchar_t *data)
{
    char convertedText[CONVERTED_BUFFER_SIZE] = "";
    int requiredSize = 0;

    if (data == NULL)
    {
        return;
    }

    requiredSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, data, -1, NULL, 0, NULL, NULL);
    /* Safety fix: verify requiredSize is positive and fits within convertedText before conversion */
    if (requiredSize > 0 && requiredSize <= (int)sizeof(convertedText))
    {
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, data, -1, convertedText, requiredSize, NULL, NULL);
    }
    else
    {
        printLine("Destination buffer not large enough to perform conversion.");
    }
}

#ifndef OMITBAD

void CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_bad()
{
    wchar_t dataBuffer[WIDE_BUFFER_SIZE];
    wchar_t *data = dataBuffer;

    wcsncpy(dataBuffer, LARGE_UNICODE_STR, WIDE_BUFFER_SIZE - 1);
    dataBuffer[WIDE_BUFFER_SIZE - 1] = L'\0';
    convertWideToMultiByte(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    wchar_t dataBuffer[WIDE_BUFFER_SIZE];
    wchar_t *data = dataBuffer;

    wcsncpy(dataBuffer, SMALL_UNICODE_STR, WIDE_BUFFER_SIZE - 1);
    dataBuffer[WIDE_BUFFER_SIZE - 1] = L'\0';
    convertWideToMultiByte(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    wchar_t dataBuffer[WIDE_BUFFER_SIZE];
    wchar_t *data = dataBuffer;

    wcsncpy(dataBuffer, LARGE_UNICODE_STR, WIDE_BUFFER_SIZE - 1);
    dataBuffer[WIDE_BUFFER_SIZE - 1] = L'\0';
    convertWideToMultiByte(data);
}

void CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_good()
{
    goodG2B();
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
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
