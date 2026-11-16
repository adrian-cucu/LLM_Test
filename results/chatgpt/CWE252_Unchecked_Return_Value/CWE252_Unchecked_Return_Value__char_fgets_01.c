/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE252_Unchecked_Return_Value__char_fgets_01.c
Label Definition File: CWE252_Unchecked_Return_Value.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef _WIN32
#include <wchar.h>
#endif
static void readAndPrint(int exitOnFailure)
{
    char data[100] = "";
    printLine("Please enter a string: ");
    if (fgets(data, sizeof(data), stdin) == NULL)
    {
        if (exitOnFailure)
        {
            printLine("fgets failed!");
            exit(1);
        }
        /* On a read error fgets leaves indeterminate contents; restore a string. */
        data[0] = '\0';
    }
    printLine(data);
}
#ifndef OMITBAD
void CWE252_Unchecked_Return_Value__char_fgets_01_bad(void)
{
    readAndPrint(0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    readAndPrint(1);
}
void CWE252_Unchecked_Return_Value__char_fgets_01_good(void)
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
    CWE252_Unchecked_Return_Value__char_fgets_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE252_Unchecked_Return_Value__char_fgets_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
