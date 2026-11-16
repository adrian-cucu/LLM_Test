/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE188_Reliance_on_Data_Memory_Layout__modify_local_01.c
Label Definition File: CWE188_Reliance_on_Data_Memory_Layout.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
static void modifyAndPrintFields(void)
{
    struct
    {
        char charFirst;
        int intSecond;
    } value = {1, 0};
    /* Named access avoids pointer arithmetic across a member and padding. */
    value.intSecond = 5;
    printIntLine(value.charFirst);
    printIntLine(value.intSecond);
}
#ifndef OMITBAD
void CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_bad(void)
{
    modifyAndPrintFields();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    modifyAndPrintFields();
}
void CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_good(void)
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
    CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
