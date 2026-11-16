/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE475_Undefined_Behavior_for_Input_to_API__char_01.c
Label Definition File: CWE475_Undefined_Behavior_for_Input_to_API.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>

static void moveAndPrint(void)
{
    char data[100] = "abcdefghijklmnopqrstuvwxyz";
    /* These ranges overlap, so memcpy would have undefined behavior. */
    memmove(data + 6, data + 4, 10 * sizeof(*data));
    printLine(data);
}
#ifndef OMITBAD
void CWE475_Undefined_Behavior_for_Input_to_API__char_01_bad()
{
    moveAndPrint();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    moveAndPrint();
}
void CWE475_Undefined_Behavior_for_Input_to_API__char_01_good()
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
    CWE475_Undefined_Behavior_for_Input_to_API__char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE475_Undefined_Behavior_for_Input_to_API__char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
