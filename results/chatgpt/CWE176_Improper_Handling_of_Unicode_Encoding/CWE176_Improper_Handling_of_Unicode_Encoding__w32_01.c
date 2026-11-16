/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE176_Improper_Handling_of_Unicode_Encoding__w32_01.c
Label Definition File: CWE176_Improper_Handling_of_Unicode_Encoding__w32.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#pragma comment(lib, "advapi32")
#define LARGE_TEXT L"\\u9580\\u961c\\u9640\\u963f\\u963b\\u9644\\u9580\\u961c\\u9640\\u963f\\u963b\\u9644"

static void convertText(const wchar_t *text, int checkFixedBuffer)
{
    char fixedBuffer[10] = "";
    char *converted = fixedBuffer;
    int required = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK,
                                      text, -1, NULL, 0, NULL, NULL);
    if (required <= 0) return;
    if (checkFixedBuffer && required >= (int)sizeof(fixedBuffer))
    {
        printLine("Destination buffer not large enough to perform conversion.");
        return;
    }
    /* Allocate the measured size rather than letting conversion overrun 10 bytes. */
    if (required > (int)sizeof(fixedBuffer))
    {
        converted = malloc((size_t)required);
        if (converted == NULL) return;
    }
    if (!WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK,
                            text, -1, converted, required, NULL, NULL))
    {
        converted[0] = '\0';
    }
    if (converted != fixedBuffer) free(converted);
}
#ifndef OMITBAD
void CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_bad(void)
{
    convertText(LARGE_TEXT, 0);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    convertText(L"\\u9580", 0);
}
static void goodB2G(void)
{
    convertText(LARGE_TEXT, 1);
}
void CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_good(void)
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE176_Improper_Handling_of_Unicode_Encoding__w32_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
