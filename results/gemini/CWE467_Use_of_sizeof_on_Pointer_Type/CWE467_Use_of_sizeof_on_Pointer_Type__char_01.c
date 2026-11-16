/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE467_Use_of_sizeof_on_Pointer_Type__char_01.c
Label Definition File: CWE467_Use_of_sizeof_on_Pointer_Type.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 467 Use of sizeof() on a Pointer Type
 * Sinks: char
 *    GoodSink: Use sizeof() the data type
 *    BadSink : Use sizeof() the pointer and not the data type
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

static void allocateAndPrintChar(char value)
{
    char *charPtr = NULL;

    /* Safety fix: Use sizeof(*charPtr) instead of sizeof(charPtr) to allocate the pointee type size */
    charPtr = (char *)malloc(sizeof(*charPtr));
    if (charPtr == NULL)
    {
        exit(-1);
    }

    *charPtr = value;
    printHexCharLine(*charPtr);
    free(charPtr);
}

#ifndef OMITBAD

void CWE467_Use_of_sizeof_on_Pointer_Type__char_01_bad()
{
    allocateAndPrintChar('B');
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    allocateAndPrintChar('G');
}

void CWE467_Use_of_sizeof_on_Pointer_Type__char_01_good()
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
    CWE467_Use_of_sizeof_on_Pointer_Type__char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE467_Use_of_sizeof_on_Pointer_Type__char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
