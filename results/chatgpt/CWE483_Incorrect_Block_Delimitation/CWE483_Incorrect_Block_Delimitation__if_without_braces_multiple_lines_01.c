/*
 * @description Incorrect Block Delimitation
 */
#include "std_testcase.h"
#ifndef OMITBAD
void CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_bad()
{
    int x = rand() % 3;
    int y = 0;
    if (x == 0)
    {
        printLine("x == 0");
    }
    /* Preserve the original unconditional assignment, now clearly scoped. */
    y = 1;
    if (y)
    {
        printLine("x was 0\n");
    }
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    int x = rand() % 3;
    int y = 0;
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
void CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_good()
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
    CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE483_Incorrect_Block_Delimitation__if_without_braces_multiple_lines_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
