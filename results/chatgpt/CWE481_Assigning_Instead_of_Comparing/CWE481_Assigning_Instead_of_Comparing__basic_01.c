/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE481_Assigning_Instead_of_Comparing__basic_01.c
Label Definition File: CWE481_Assigning_Instead_of_Comparing__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef OMITBAD
void CWE481_Assigning_Instead_of_Comparing__basic_01_bad()
{
    int value = rand();
    /* Keep the assignment semantics, but make the side effect explicit. */
    value = 5;
    if (value != 0)
    {
        printLine("i was 5");
    }
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    const int value = rand();
    if (value == 5)
    {
        printLine("i was 5");
    }
}
void CWE481_Assigning_Instead_of_Comparing__basic_01_good()
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
    CWE481_Assigning_Instead_of_Comparing__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE481_Assigning_Instead_of_Comparing__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
