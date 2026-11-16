/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE390_Error_Without_Action__fgets_char_01.c
Label Definition File: CWE390_Error_Without_Action__fgets.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void readAndPrint(int fatalOnError)
{
    char data[100] = "";
    printLine("Please enter a string: ");
    if (fgets(data, sizeof(data), stdin) == NULL)
    {
        /* A failed read must not leave a partially modified string in use. */
        data[0] = '\0';
        if (fatalOnError)
        {
            printLine("fgets failed!");
            exit(1);
        }
    }
    printLine(data);
}
#ifndef OMITBAD
void CWE390_Error_Without_Action__fgets_char_01_bad()
{
    readAndPrint(0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    readAndPrint(1);
}
void CWE390_Error_Without_Action__fgets_char_01_good()
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
    CWE390_Error_Without_Action__fgets_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE390_Error_Without_Action__fgets_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
