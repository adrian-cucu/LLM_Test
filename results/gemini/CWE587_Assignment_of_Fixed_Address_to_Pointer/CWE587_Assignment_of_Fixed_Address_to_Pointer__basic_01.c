/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE587_Assignment_of_Fixed_Address_to_Pointer__basic_01.c
Label Definition File: CWE587_Assignment_of_Fixed_Address_to_Pointer__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 587 Assignment of Fixed Address to Pointer
 * Sinks:
 *    GoodSink: Assign the pointer to a stack variable
 *    BadSink : Assign fixed address to pointer
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#define DEFAULT_CHAR_VALUE 'a'

static void printStackCharHex(void)
{
    char charStack = DEFAULT_CHAR_VALUE;
    char *charPointer = &charStack;
    printHexCharLine(*charPointer);
}

#ifndef OMITBAD

void CWE587_Assignment_of_Fixed_Address_to_Pointer__basic_01_bad()
{
    /* Safety fix: point to a valid stack variable instead of dereferencing a fixed address. */
    printStackCharHex();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    printStackCharHex();
}

void CWE587_Assignment_of_Fixed_Address_to_Pointer__basic_01_good()
{
    good1();
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
    CWE587_Assignment_of_Fixed_Address_to_Pointer__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE587_Assignment_of_Fixed_Address_to_Pointer__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
