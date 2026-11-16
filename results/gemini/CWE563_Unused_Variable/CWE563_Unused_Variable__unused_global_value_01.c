/*
 * @description Unused global value
 *
 */

#include "std_testcase.h"

#define INITIAL_BAD_GLOBAL_VALUE 0
#define UPDATED_BAD_GLOBAL_VALUE 10
#define GOOD_GLOBAL_VALUE 5

#ifndef OMITBAD

int CWE563_Unused_Variable__unused_global_value_01_badGlobal = INITIAL_BAD_GLOBAL_VALUE;

void CWE563_Unused_Variable__unused_global_value_01_bad()
{
    CWE563_Unused_Variable__unused_global_value_01_badGlobal = UPDATED_BAD_GLOBAL_VALUE;
    printIntLine(CWE563_Unused_Variable__unused_global_value_01_badGlobal);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

int CWE563_Unused_Variable__unused_global_value_01_globalGood1 = GOOD_GLOBAL_VALUE;

static void good1(void)
{
    printIntLine(CWE563_Unused_Variable__unused_global_value_01_globalGood1);
}

void CWE563_Unused_Variable__unused_global_value_01_good()
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
    CWE563_Unused_Variable__unused_global_value_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE563_Unused_Variable__unused_global_value_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
