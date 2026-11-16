/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE482_Comparing_Instead_of_Assigning__basic_01.c
Label Definition File: CWE482_Comparing_Instead_of_Assigning__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef OMITBAD
void CWE482_Comparing_Instead_of_Assigning__basic_01_bad()
{
    int value = 0;
    printIntLine(value);
    /* Explicitly discard the comparison without turning it into assignment. */
    (void)(value == 5);
    printIntLine(value);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    int value = 0;
    printIntLine(value);
    value = 5;
    printIntLine(value);
}
void CWE482_Comparing_Instead_of_Assigning__basic_01_good()
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
    CWE482_Comparing_Instead_of_Assigning__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE482_Comparing_Instead_of_Assigning__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
