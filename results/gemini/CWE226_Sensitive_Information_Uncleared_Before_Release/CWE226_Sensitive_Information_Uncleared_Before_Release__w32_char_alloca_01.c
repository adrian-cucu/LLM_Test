/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01.c
Label Definition File: CWE226_Sensitive_Information_Uncleared_Before_Release__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 226 Sensitive Information Uncleared Before Release
 * Sinks: alloca
 *    GoodSink: Clear the password buffer before releasing the memory from the stack
 *    BadSink : Release password from the stack without first clearing the buffer
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

static void readPasswordAndLogon(void)
{
    char *password = (char *)ALLOCA(PASSWORD_BUFFER_SIZE * sizeof(char));
    size_t passwordLen = 0;
    HANDLE hUser = NULL;

    password[0] = '\0';
    if (fgets(password, PASSWORD_BUFFER_SIZE, stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
    }

    passwordLen = strlen(password);
    if (passwordLen > 0 && password[passwordLen - 1] == '\n')
    {
        password[passwordLen - 1] = '\0';
    }

    if (LogonUserA(
            DEFAULT_USERNAME,
            DEFAULT_DOMAIN,
            password,
            LOGON32_LOGON_NETWORK,
            LOGON32_PROVIDER_DEFAULT,
            &hUser) != 0)
    {
        printLine("User logged in successfully.");
        CloseHandle(hUser);
    }
    else
    {
        printLine("Unable to login.");
    }

    /* Safety fix: clear sensitive password buffer with SecureZeroMemory before returning */
    SecureZeroMemory(password, PASSWORD_BUFFER_SIZE * sizeof(char));
}

#ifndef OMITBAD

void CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_bad()
{
    readPasswordAndLogon();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    readPasswordAndLogon();
}

void CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_good()
{
    good1();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
