/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01.c
Label Definition File: CWE273_Improper_Check_for_Dropped_Privileges__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
#define BUFSIZE 1024
static void impersonateClient(int checkResult)
{
    HANDLE pipe = CreateNamedPipeA(
        "\\\\.\\pipe\\test_pipe",
        PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE,
        NMPWAIT_USE_DEFAULT_WAIT, NULL);
    BOOL impersonated;
    if (pipe == INVALID_HANDLE_VALUE) exit(1);
    /* A client connecting before ConnectNamedPipe is already connected. */
    if (!ConnectNamedPipe(pipe, NULL) && GetLastError() != ERROR_PIPE_CONNECTED)
    {
        CloseHandle(pipe);
        exit(1);
    }
    impersonated = ImpersonateNamedPipeClient(pipe);
    if (checkResult && !impersonated)
    {
        printLine("Failed to impersonate");
    }
    else
    {
        printLine("Impersonated");
        if (!RevertToSelf())
        {
            /* Close our handle even when reverting fails; then terminate. */
            CloseHandle(pipe);
            exit(1);
        }
    }
    CloseHandle(pipe);
}
#ifndef OMITBAD
void CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_bad(void)
{
    impersonateClient(0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    impersonateClient(1);
}
void CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_good(void)
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
    CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE273_Improper_Check_for_Dropped_Privileges__w32_ImpersonateNamedPipeClient_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
