/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE478_Missing_Default_Case_in_Switch__basic_01.c
Label Definition File: CWE478_Missing_Default_Case_in_Switch__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void printSelection(int selection, int skipOtherValues)
{
    const char *text;
    switch (selection)
    {
    case 0:
        text = "0";
        break;
    case 1:
        text = "1";
        break;
    default:
        if (skipOtherValues) { return; }
        text = "shouldn\'t see this value";
        break;
    }
    printLine(text);
}
#ifndef OMITBAD
void CWE478_Missing_Default_Case_in_Switch__basic_01_bad()
{
    printSelection(rand() % 3, 0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printSelection(rand() % 3, 1);
}
void CWE478_Missing_Default_Case_in_Switch__basic_01_good()
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
    CWE478_Missing_Default_Case_in_Switch__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE478_Missing_Default_Case_in_Switch__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
