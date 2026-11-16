/*
 * @description
 * CWE: 476 NULL Pointer Dereference
 * Sinks: binary_if
 *    GoodSink: Do not check for NULL after the pointer has been dereferenced
 *    BadSink : Check for NULL after a pointer has already been dereferenced
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define TARGET_VALUE 5

static void checkStructValue(const twoIntsStruct *structPtr)
{
    /* Safety fix: use logical && instead of bitwise & to short-circuit NULL check */
    if ((structPtr != NULL) && (structPtr->intOne == TARGET_VALUE))
    {
        printLine("intOne == 5");
    }
}

#ifndef OMITBAD

void CWE476_NULL_Pointer_Dereference__binary_if_01_bad()
{
    twoIntsStruct *twoIntsStructPointer = NULL;
    checkStructValue(twoIntsStructPointer);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    twoIntsStruct *twoIntsStructPointer = NULL;
    checkStructValue(twoIntsStructPointer);
}

void CWE476_NULL_Pointer_Dereference__binary_if_01_good()
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
    CWE476_NULL_Pointer_Dereference__binary_if_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE476_NULL_Pointer_Dereference__binary_if_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
