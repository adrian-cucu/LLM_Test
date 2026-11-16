/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE546_Suspicious_Comment__BUG_01.c
Label Definition File: CWE546_Suspicious_Comment.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void printGreeting(void)
{
    printLine("Hello");
}
#ifndef OMITBAD
void CWE546_Suspicious_Comment__BUG_01_bad()
{
    printGreeting();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printGreeting();
}
void CWE546_Suspicious_Comment__BUG_01_good()
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
    CWE546_Suspicious_Comment__BUG_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE546_Suspicious_Comment__BUG_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
