/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE244_Heap_Inspection__w32_char_free_01.c
Label Definition File: CWE244_Heap_Inspection__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 244 Failure to Clear Heap Before Release (Heap Inspection)
 * Sinks: free
 *    GoodSink: Clear the password buffer before releasing the memory from the heap
 *    BadSink : Release password from the heap without first clearing the buffer
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

static void readPasswordLine(char *password, size_t bufferSize)
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

static void attemptLogonAndFree(void)
{
    char *password = (char *)malloc(PASSWORD_BUFFER_SIZE * sizeof(char));
    HANDLE hUser = NULL;

    if (password == NULL)
    {
        exit(-1);
    }

    readPasswordLine(password, PASSWORD_BUFFER_SIZE);

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

    /* Safety fix: clear sensitive password buffer in heap memory prior to freeing */
    SecureZeroMemory(password, PASSWORD_BUFFER_SIZE * sizeof(char));
    free(password);
}

#ifndef OMITBAD

void CWE244_Heap_Inspection__w32_char_free_01_bad()
{
    attemptLogonAndFree();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    attemptLogonAndFree();
}

void CWE244_Heap_Inspection__w32_char_free_01_good()
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
    CWE244_Heap_Inspection__w32_char_free_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE244_Heap_Inspection__w32_char_free_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
