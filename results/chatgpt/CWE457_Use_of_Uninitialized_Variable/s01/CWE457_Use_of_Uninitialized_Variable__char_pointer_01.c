/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE457_Use_of_Uninitialized_Variable__char_pointer_01.c
Label Definition File: CWE457_Use_of_Uninitialized_Variable.c.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#ifndef OMITBAD
void CWE457_Use_of_Uninitialized_Variable__char_pointer_01_bad()
{
    /* Supply a valid string instead of reading an indeterminate pointer. */
    const char *data = "string";
    printLine(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    const char *data = "string";
    printLine(data);
}
static void goodB2G(void)
{
    const char *data = "string";
    printLine(data);
}
void CWE457_Use_of_Uninitialized_Variable__char_pointer_01_good()
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE457_Use_of_Uninitialized_Variable__char_pointer_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE457_Use_of_Uninitialized_Variable__char_pointer_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
