/*
 * @description Uncontrolled Recursion
 *
 */

#include "std_testcase.h"

#define DEFAULT_RECURSION_DEPTH 5U

static void recurseBounded(unsigned level)
{
    if (level == 0U)
    {
        return;
    }
    recurseBounded(level - 1U);
}

#ifndef OMITBAD

static void helperBad(unsigned level)
{
    /* Safety fix: add a recursion depth bound to prevent infinite recursion and stack overflow. */
    recurseBounded(level);
}

void CWE674_Uncontrolled_Recursion__infinite_recursive_call_01_bad()
{
    helperBad(DEFAULT_RECURSION_DEPTH);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void helperGood(unsigned level)
{
    recurseBounded(level);
}

static void good1(void)
{
    helperGood(DEFAULT_RECURSION_DEPTH);
}

void CWE674_Uncontrolled_Recursion__infinite_recursive_call_01_good()
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
    CWE674_Uncontrolled_Recursion__infinite_recursive_call_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE674_Uncontrolled_Recursion__infinite_recursive_call_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
