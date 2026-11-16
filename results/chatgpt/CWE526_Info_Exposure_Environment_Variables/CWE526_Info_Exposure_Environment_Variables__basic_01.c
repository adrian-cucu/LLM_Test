/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE526_Info_Exposure_Environment_Variables__basic_01.c
Label Definition File: CWE526_Info_Exposure_Environment_Variables__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef OMITBAD
void CWE526_Info_Exposure_Environment_Variables__basic_01_bad()
{
    const char *path = getenv("PATH");
    /* getenv returns NULL for an unset variable; printLine needs a string. */
    if (path == NULL)
    {
        printLine("Not in path");
        return;
    }
    printLine(path);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    const char message[] = "Not in path";
    printLine(message);
}
void CWE526_Info_Exposure_Environment_Variables__basic_01_good()
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
    CWE526_Info_Exposure_Environment_Variables__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE526_Info_Exposure_Environment_Variables__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
