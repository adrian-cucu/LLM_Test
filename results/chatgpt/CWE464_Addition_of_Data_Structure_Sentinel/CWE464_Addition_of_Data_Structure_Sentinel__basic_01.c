/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE464_Addition_of_Data_Structure_Sentinel__basic_01.c
Label Definition File: CWE464_Addition_of_Data_Structure_Sentinel__basic.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"

static void printCharacterArray(char middle)
{
    char text[] = {'x', middle, 'z', '\0'};
    /* A zero middle character retains the original string truncation. */
    printLine(text);
}
#ifndef OMITBAD
void CWE464_Addition_of_Data_Structure_Sentinel__basic_01_bad()
{
    char input[2] = {(char)getc(stdin), '\0'};
    char data = (char)atoi(input);
    printCharacterArray(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    printCharacterArray('a');
}
void CWE464_Addition_of_Data_Structure_Sentinel__basic_01_good()
{
    goodG2B();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE464_Addition_of_Data_Structure_Sentinel__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE464_Addition_of_Data_Structure_Sentinel__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
