/*
 * @description
 * CWE: 535 Information Exposure Through Shell Error Message
 * Sinks:
 *    GoodSink: Write to stderr, but do not write the password
 *    BadSink : Write to stderr and include the password
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#include <wchar.h>

#include <windows.h>
#pragma comment(lib, "advapi32.lib")

#define PASSWORD_BUFFER_SIZE 100
#define DEFAULT_USERNAME "User"
#define DEFAULT_DOMAIN "Domain"

static void readPasswordFromStdin(char *password, size_t bufferSize)
{
    size_t passwordLen = 0;

    if (password == NULL || bufferSize == 0)
    {
        return;
    }

    if (fgets(password, (int)bufferSize, stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
        return;
    }

    passwordLen = strlen(password);
    /* Safety fix: only strip trailing newline if present */
    if (passwordLen > 0 && password[passwordLen - 1] == '\n')
    {
        password[passwordLen - 1] = '\0';
    }
}

static void attemptUserLoginAndReportError(void)
{
    char password[PASSWORD_BUFFER_SIZE] = "";
    HANDLE pHandle = NULL;
    char *username = DEFAULT_USERNAME;
    char *domain = DEFAULT_DOMAIN;

    readPasswordFromStdin(password, sizeof(password));

    if (LogonUserA(
            username,
            domain,
            password,
            LOGON32_LOGON_NETWORK,
            LOGON32_PROVIDER_DEFAULT,
            &pHandle) != 0)
    {
        printLine("User logged in successfully.");
        CloseHandle(pHandle);
    }
    else
    {
        printLine("Unable to login.");
    }

    /* Safety fix: do not write sensitive password to stderr */
    fprintf(stderr, "User attempted access\n");
}

#ifndef OMITBAD

void CWE535_Info_Exposure_Shell_Error__w32_char_01_bad()
{
    attemptUserLoginAndReportError();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    attemptUserLoginAndReportError();
}

void CWE535_Info_Exposure_Shell_Error__w32_char_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE535_Info_Exposure_Shell_Error__w32_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE535_Info_Exposure_Shell_Error__w32_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
