/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE252_Unchecked_Return_Value__char_fgets_01.c
Label Definition File: CWE252_Unchecked_Return_Value.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 252 Unchecked Return Value
 * Sinks: fgets
 *    GoodSink: Check if fgets() fails before trying to use the destination buffer
 *    BadSink : Do not check if fgets() fails
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define INPUT_BUFFER_SIZE 100

static void readAndPrintInput(void)
{
    char dataBuffer[INPUT_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    printLine("Please enter a string: ");
    /* Safety fix: check fgets() return value for NULL before using buffer */
    if (fgets(data, INPUT_BUFFER_SIZE, stdin) == NULL)
    {
        printLine("fgets failed!");
        exit(1);
    }
    printLine(data);
}

#ifndef OMITBAD

void CWE252_Unchecked_Return_Value__char_fgets_01_bad()
{
    readAndPrintInput();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    readAndPrintInput();
}

void CWE252_Unchecked_Return_Value__char_fgets_01_good()
{
    good1();
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
    CWE252_Unchecked_Return_Value__char_fgets_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE252_Unchecked_Return_Value__char_fgets_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
