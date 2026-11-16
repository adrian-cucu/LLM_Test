/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE391_Unchecked_Error_Condition__sqrt_01.c
Label Definition File: CWE391_Unchecked_Error_Condition.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <errno.h>
#include <math.h>

#ifndef OMITBAD
void CWE391_Unchecked_Error_Condition__sqrt_01_bad()
{
    double result = sqrt(-1.0);
    printDoubleLine(result);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    double result;
    errno = 0;
    result = sqrt(-1.0);
    /* C implementations need not report math errors through errno alone. */
    if (errno == EDOM || isnan(result))
    {
        printLine("sqrt() failed");
        exit(1);
    }
    printDoubleLine(result);
}
void CWE391_Unchecked_Error_Condition__sqrt_01_good()
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
    CWE391_Unchecked_Error_Condition__sqrt_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE391_Unchecked_Error_Condition__sqrt_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
