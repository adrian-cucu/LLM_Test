/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE484_Omitted_Break_Statement_in_Switch__basic_01.c
Label Definition File: CWE484_Omitted_Break_Statement_in_Switch__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void printSelection(int selection, int includeFollowingCase)
{
    switch (selection)
    {
    case 0:
        printLine("0");
        /* Preserve the first variant's extra output without implicit fallthrough. */
        if (includeFollowingCase) { printLine("1"); }
        break;
    case 1:
        printLine("1");
        break;
    case 2:
        printLine("2");
        break;
    default:
        printLine("Invalid Number");
        break;
    }
}
#ifndef OMITBAD
void CWE484_Omitted_Break_Statement_in_Switch__basic_01_bad()
{
    printSelection(rand() % 3, 1);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printSelection(rand() % 3, 0);
}
void CWE484_Omitted_Break_Statement_in_Switch__basic_01_good()
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
    CWE484_Omitted_Break_Statement_in_Switch__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE484_Omitted_Break_Statement_in_Switch__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
