/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE476_NULL_Pointer_Dereference__binary_if_01.c
Label Definition File: CWE476_NULL_Pointer_Dereference.pointflaw.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void printIfFive(const twoIntsStruct *value)
{
    /* Short circuit before evaluating a member of a null pointer. */
    if (value != NULL && value->intOne == 5)
    {
        printLine("intOne == 5");
    }
}
#ifndef OMITBAD
void CWE476_NULL_Pointer_Dereference__binary_if_01_bad()
{
    twoIntsStruct *value = NULL;
    printIfFive(value);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    twoIntsStruct *value = NULL;
    printIfFive(value);
}
void CWE476_NULL_Pointer_Dereference__binary_if_01_good()
{
    good1();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE476_NULL_Pointer_Dereference__binary_if_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE476_NULL_Pointer_Dereference__binary_if_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
