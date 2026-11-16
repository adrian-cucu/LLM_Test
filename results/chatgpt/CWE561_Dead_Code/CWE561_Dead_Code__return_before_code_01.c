/*
 * @description Unused code via 'return' before code
 */
#include "std_testcase.h"
#ifndef OMITBAD
void CWE561_Dead_Code__return_before_code_01_bad()
{
    /* The original returned without printing; keep that observable behavior. */
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printLine("Hello");
}
void CWE561_Dead_Code__return_before_code_01_good()
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
    CWE561_Dead_Code__return_before_code_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE561_Dead_Code__return_before_code_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
