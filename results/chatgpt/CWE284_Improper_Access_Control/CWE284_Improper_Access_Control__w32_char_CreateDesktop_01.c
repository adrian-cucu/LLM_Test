/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE284_Improper_Access_Control__w32_char_CreateDesktop_01.c
Label Definition File: CWE284_Improper_Access_Control__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#pragma comment(lib, "user32")
static void createAndCloseDesktop(ACCESS_MASK access)
{
    HDESK desktop = CreateDesktopA("DesktopExample", NULL, NULL, 0, access, NULL);
    if (desktop == NULL)
    {
        printLine("Desktop could not be created");
        return;
    }
    printLine("Desktop created successfully");
    CloseDesktop(desktop);
}
#ifndef OMITBAD
void CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_bad(void)
{
    createAndCloseDesktop(GENERIC_ALL);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    createAndCloseDesktop(GENERIC_READ);
}
void CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_good(void)
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
    CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
