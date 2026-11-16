/*
 * @description Expression is always true via if (true_expression)
 *
 */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE571_Expression_Always_True__global_01_bad()
{
    if (globalTrue)
    {
        printLine("Always prints");
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    if (globalReturnsTrueOrFalse() == globalTrue)
    {
        printLine("Sometimes prints");
    }
}

void CWE571_Expression_Always_True__global_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE571_Expression_Always_True__global_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE571_Expression_Always_True__global_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
