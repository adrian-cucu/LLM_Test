/*
 * @description
 * CWE: 468 Incorrect Pointer Scaling
 * Sinks: char_ptr_to_int
 *    GoodSink: Correctly use sizeof() for pointer scaling
 *    BadSink : Do not use sizeof() in pointer scaling
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"
#include <string.h>

#define ARRAY_SIZE 5
#define TARGET_INDEX 2

static void printScaledIntElement(void)
{
    int intArray[ARRAY_SIZE] = { 1, 2, 3, 4, 5 };
    const char *charPointer = (const char *)intArray;
    int toPrint = 0;

    /* Safety fix: scale offset by sizeof(int) and use memcpy to avoid misaligned or strict-aliasing UB */
    memcpy(&toPrint, charPointer + (TARGET_INDEX * sizeof(int)), sizeof(toPrint));
    printIntLine(toPrint);
}

#ifndef OMITBAD

void CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_bad()
{
    printScaledIntElement();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printScaledIntElement();
}

void CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
