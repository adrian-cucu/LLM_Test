/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01.c
Label Definition File: CWE253_Incorrect_Check_of_Function_Return_Value.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef _WIN32
#include <wchar.h>
#endif
static void readAndPrint(void)
{
    char data[100] = "";
    printLine("Please enter a string: ");
    /* fgets returns a pointer, so compare to NULL rather than an integer. */
    if (fgets(data, sizeof(data), stdin) == NULL)
    {
        printLine("fgets failed!");
        exit(1);
    }
    printLine(data);
}
#ifndef OMITBAD
void CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_bad(void)
{
    readAndPrint();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    readAndPrint();
}
void CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_good(void)
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
    CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE253_Incorrect_Check_of_Function_Return_Value__char_fgets_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
