/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01.c
Label Definition File: CWE272_Least_Privilege_Violation__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 272 Least Privilege Violation
 * Sinks: CreateProcess
 *    GoodSink: Create a process using CreateProcessA() with quotes for the executable path
 *    BadSink : Create a process using CreateProcessA() without quotes for the executable path
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <shlwapi.h>
#pragma comment( lib, "shlwapi" )

#define QUOTED_COMMAND_LINE "\"C:\\Program Files\\GoodApp\" arg1 arg2"
#define CMD_BUFFER_SIZE 256

static void launchProcessQuoted(void)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    /* Safety fix: use a mutable command line buffer (CreateProcessA may modify lpCommandLine) */
    char commandLine[CMD_BUFFER_SIZE] = QUOTED_COMMAND_LINE;

    /* Safety fix: zero-initialize STARTUPINFOA and PROCESS_INFORMATION and set cb */
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    /* Safety fix: quote the executable path containing spaces to prevent unquoted path hijacking */
    if (!CreateProcessA(NULL,
                        commandLine,
                        NULL,
                        NULL,
                        FALSE,
                        0,
                        NULL,
                        NULL,
                        &si,
                        &pi))
    {
        printLine("CreateProcess failed");
        return;
    }

    printLine("CreateProcess successful");
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

#ifndef OMITBAD

void CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_bad()
{
    launchProcessQuoted();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    launchProcessQuoted();
}

void CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE272_Least_Privilege_Violation__w32_char_CreateProcess_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
