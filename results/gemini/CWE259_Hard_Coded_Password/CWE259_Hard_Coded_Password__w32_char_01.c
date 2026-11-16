/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE259_Hard_Coded_Password__w32_char_01.c
Label Definition File: CWE259_Hard_Coded_Password__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 259 Use of Hard-coded Password
 * BadSource:  Use a hardcoded password
 * GoodSource: Read the password from the console
 * Sink:
 *    BadSink : Authenticate the user using LogonUserA()
 * Flow Variant: 01 Baseline
 *
 * */

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

    password[0] = '\0';
    if (fgets(password, (int)bufferSize, stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
        return;
    }

    passwordLen = strlen(password);
    if (passwordLen > 0 && password[passwordLen - 1] == '\n')
    {
        password[passwordLen - 1] = '\0';
    }
}

static void authenticateUser(const char *username, const char *domain, const char *password)
{
    HANDLE pHandle = NULL;
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
}

#ifndef OMITBAD

void CWE259_Hard_Coded_Password__w32_char_01_bad()
{
    char passwordBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *password = passwordBuffer;

    /* Safety fix: read password from stdin instead of using a hardcoded password */
    readPasswordFromStdin(password, sizeof(passwordBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, password);
    SecureZeroMemory(passwordBuffer, sizeof(passwordBuffer));
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B(void)
{
    char passwordBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *password = passwordBuffer;

    readPasswordFromStdin(password, sizeof(passwordBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, password);
    SecureZeroMemory(passwordBuffer, sizeof(passwordBuffer));
}

void CWE259_Hard_Coded_Password__w32_char_01_good()
{
    goodG2B();
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
    CWE259_Hard_Coded_Password__w32_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE259_Hard_Coded_Password__w32_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
