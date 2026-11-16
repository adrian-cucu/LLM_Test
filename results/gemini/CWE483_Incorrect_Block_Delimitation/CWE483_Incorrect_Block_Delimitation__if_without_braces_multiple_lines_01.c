/*
 * @description Incorrect Block Delimitation
 */

#include "std_testcase.h"

#define RANDOM_MODULO 3

static void checkZeroAndPrint(void)
{
    int x = (rand() % RANDOM_MODULO);
    int y = 0;

    /* Safety fix: add braces around if body so y = 1 only executes when x == 0 */
    if (x == 0)
    {
        printLine("x == 0");
        y = 1;
    }

    if (y)
    {
        printLine("x was 0\n");
    }
}

#ifndef OMITBAD

void CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_bad()
{
    checkZeroAndPrint();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    checkZeroAndPrint();
}

void CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_good()
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
    CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
