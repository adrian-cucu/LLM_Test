/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE242_Use_of_Inherently_Dangerous_Function__basic_01.c
Label Definition File: CWE242_Use_of_Inherently_Dangerous_Function__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 242 Use of Inherently Dangerous Function
 * Sinks:
 *    GoodSink: Use fgets() for bounded user input
 *    BadSink : Use gets() for user input
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define DEST_SIZE 10

static void readAndPrintBoundedLine(void)
{
    char dest[DEST_SIZE] = "";
    /* Safety fix: use fgets() for bounded input instead of inherently dangerous gets() */
    if (fgets(dest, DEST_SIZE, stdin) == NULL)
    {
        printLine("Error Condition: alter control flow to indicate action taken");
        exit(1);
    }
    dest[DEST_SIZE - 1] = '\0';
    printLine(dest);
}

#ifndef OMITBAD

void CWE242_Use_of_Inherently_Dangerous_Function__basic_01_bad()
{
    readAndPrintBoundedLine();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    readAndPrintBoundedLine();
}

void CWE242_Use_of_Inherently_Dangerous_Function__basic_01_good()
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
    CWE242_Use_of_Inherently_Dangerous_Function__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE242_Use_of_Inherently_Dangerous_Function__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
