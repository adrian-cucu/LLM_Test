/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE196_Unsigned_to_Signed_Conversion_Error__basic_01.c
Label Definition File: CWE196_Unsigned_to_Signed_Conversion_Error__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <limits.h>
static unsigned int randomUnsigned(void)
{
    unsigned int value = (unsigned int)rand();
    if (rand() % 2 == 0) value = UINT_MAX - value;
    return value;
}
#ifndef OMITBAD
void CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_bad(void)
{
    unsigned int value = randomUnsigned();
    /* Retain the platform's original unsigned-to-signed conversion. */
    printIntLine((int)value);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    unsigned int value = randomUnsigned();
    if (value > INT_MAX) exit(1);
    printIntLine((int)value);
}
void CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_good(void)
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
    CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
