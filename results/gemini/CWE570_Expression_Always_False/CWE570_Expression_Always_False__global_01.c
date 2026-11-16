/*
 * @description Expression is always false via if (false_expression)
 *
 */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE570_Expression_Always_False__global_01_bad()
{
    if (globalFalse)
    {
        printLine("Never prints");
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    if (globalReturnsTrueOrFalse() == globalFalse)
    {
        printLine("Sometimes prints");
    }
}

void CWE570_Expression_Always_False__global_01_good()
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
    CWE570_Expression_Always_False__global_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE570_Expression_Always_False__global_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
