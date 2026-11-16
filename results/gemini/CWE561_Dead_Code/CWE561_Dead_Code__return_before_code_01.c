/*
 * @description Unused code via 'return' before code
 */

#include "std_testcase.h"

static void printGreetingAndReturn(void)
{
    /* Safety fix: place printLine before return so it is not unreachable dead code */
    printLine("Hello");
    return;
}

#ifndef OMITBAD

void CWE561_Dead_Code__return_before_code_01_bad()
{
    printGreetingAndReturn();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printGreetingAndReturn();
}

void CWE561_Dead_Code__return_before_code_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE561_Dead_Code__return_before_code_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE561_Dead_Code__return_before_code_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
