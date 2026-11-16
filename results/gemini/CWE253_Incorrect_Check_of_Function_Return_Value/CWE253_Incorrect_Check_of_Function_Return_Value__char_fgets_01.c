/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01.c
Label Definition File: CWE253_Incorrect_Check_of_Function_Return_Value.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 253 Incorrect Check of Return Value
 * Sinks: fgets
 *    GoodSink: Correctly check if fgets() failed before trying to use the destination buffer
 *    BadSink : Incorrectly check if fgets() failed
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
    /* Safety fix: check fgets() return value against NULL instead of < 0 */
    if (fgets(data, INPUT_BUFFER_SIZE, stdin) == NULL)
    {
        printLine("fgets failed!");
        exit(1);
    }
    printLine(data);
}

#ifndef OMITBAD

void CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_bad()
{
    readAndPrintInput();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    readAndPrintInput();
}

void CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_good()
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
    CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
