/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE398_Poor_Code_Quality__addition_01.c
Label Definition File: CWE398_Poor_Code_Quality.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef OMITBAD
void CWE398_Poor_Code_Quality__addition_01_bad()
{
    int first = 1;
    int second = 1;
    int sum = 0;
    printIntLine(sum);
    /* This variant intentionally discards the sum. */
    (void)(first + second);
    printIntLine(sum);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    int first = 1;
    int second = 1;
    int sum = 0;
    printIntLine(sum);
    sum = first + second;
    printIntLine(sum);
}
void CWE398_Poor_Code_Quality__addition_01_good()
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
    CWE398_Poor_Code_Quality__addition_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE398_Poor_Code_Quality__addition_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
