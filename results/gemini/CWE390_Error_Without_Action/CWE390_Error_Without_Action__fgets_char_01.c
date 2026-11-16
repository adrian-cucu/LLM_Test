/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE390_Error_Without_Action__fgets_char_01.c
Label Definition File: CWE390_Error_Without_Action__fgets.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 390 Detection of Error Condition Without Action
 * Sinks:
 *    GoodSink: Check if fgets() failed and handle errors properly
 *    BadSink : Check to see if fgets() failed, but do nothing about it
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define INPUT_BUFFER_SIZE 100

static void readAndPrintInput(void)
{
    char dataBuffer[INPUT_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    printLine("Please enter a string: ");
    /* Safety fix: Check fgets() return value and handle failure instead of ignoring it */
    if (fgets(data, INPUT_BUFFER_SIZE, stdin) == NULL)
    {
        printLine("fgets failed!");
        exit(1);
    }

    printLine(data);
}

#ifndef OMITBAD

void CWE390_Error_Without_Action__fgets_char_01_bad()
{
    readAndPrintInput();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    readAndPrintInput();
}

void CWE390_Error_Without_Action__fgets_char_01_good()
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
    CWE390_Error_Without_Action__fgets_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE390_Error_Without_Action__fgets_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
