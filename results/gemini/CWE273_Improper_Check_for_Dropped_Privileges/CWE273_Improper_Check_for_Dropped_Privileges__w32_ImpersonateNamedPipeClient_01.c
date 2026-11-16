/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01.c
Label Definition File: CWE273_Improper_Check_for_Dropped_Privileges__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 273 Improper Check for Dropped Privileges
 * Sinks: ImpersonateNamedPipeClient
 *    GoodSink: Check if ImpersonateNamedPipeClient() succeeded or not
 *    BadSink : Failed to check return status of ImpersonateNamedPipeClient()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>

#pragma comment(lib, "advapi32.lib")
#define BUFSIZE 1024
#define PIPE_NAME "\\\\.\\pipe\\test_pipe"

static void runPipeImpersonation(void)
{
    HANDLE hPipe = INVALID_HANDLE_VALUE;

    hPipe = CreateNamedPipeA(
                PIPE_NAME,
                PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE,
                PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                BUFSIZE,
                BUFSIZE,
                NMPWAIT_USE_DEFAULT_WAIT,
                NULL);
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        exit(1);
    }

    if (!ConnectNamedPipe(hPipe, NULL) && GetLastError() != ERROR_PIPE_CONNECTED)
    {
        CloseHandle(hPipe);
        exit(1);
    }

    /* Safety fix: check return status of ImpersonateNamedPipeClient() before proceeding */
    if (!ImpersonateNamedPipeClient(hPipe))
    {
        printLine("Failed to impersonate");
    }
    else
    {
        printLine("Impersonated");
        if (!RevertToSelf())
        {
            CloseHandle(hPipe);
            exit(1);
        }
    }

    CloseHandle(hPipe);
}

#ifndef OMITBAD

void CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_bad()
{
    runPipeImpersonation();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    runPipeImpersonation();
}

void CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_good()
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
    CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
