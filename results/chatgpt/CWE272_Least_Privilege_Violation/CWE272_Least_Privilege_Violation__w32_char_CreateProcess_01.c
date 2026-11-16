/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01.c
Label Definition File: CWE272_Least_Privilege_Violation__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi")
static void launchAndWait(char *commandLine, int detailedErrors)
{
    /* CreateProcess requires initialized STARTUPINFO and a writable command line. */
    STARTUPINFOA startup = {0};
    PROCESS_INFORMATION process = {0};
    startup.cb = sizeof(startup);
    if (!CreateProcessA(NULL, commandLine, NULL, NULL, FALSE, 0,
                        NULL, NULL, &startup, &process))
    {
        if (detailedErrors)
            printf("CreateProcess failed (%lu).\n", (unsigned long)GetLastError());
        else
            printLine("CreateProcess failed");
        return;
    }
    printLine("CreateProcess successful");
    WaitForSingleObject(process.hProcess, INFINITE);
    CloseHandle(process.hProcess);
    CloseHandle(process.hThread);
}
#ifndef OMITBAD
void CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_bad(void)
{
    char commandLine[] = "C:\\Program Files\\GoodApp arg1 arg2";
    launchAndWait(commandLine, 0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    char commandLine[] = "\"C:\\Program Files\\GoodApp\" arg1 arg2";
    launchAndWait(commandLine, 1);
}
void CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_good(void)
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
    CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
