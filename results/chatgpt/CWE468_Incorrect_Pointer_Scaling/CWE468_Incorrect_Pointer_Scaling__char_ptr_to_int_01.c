/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01.c
Label Definition File: CWE468_Incorrect_Pointer_Scaling.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void printByteAtOffset(size_t byteOffset)
{
    int values[5] = {1, 2, 3, 4, 5};
    const char *bytes = (const char *)values;
    /* Preserve byte access, including platform byte order and char signedness. */
    printIntLine((int)bytes[byteOffset]);
}
#ifndef OMITBAD
void CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_bad()
{
    printByteAtOffset(2);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printByteAtOffset(2 * sizeof(int));
}
void CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_good()
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
    CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE468_Incorrect_Pointer_Scaling__char_ptr_to_int_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
