/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_01.c
Label Definition File: CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 591 Sensitive Data Storage in Improperly Locked Memory
 * BadSource:  Allocate memory for sensitive data without using VirtualLock() to lock the buffer into memory
 * GoodSource: Allocate memory for sensitive data and use VirtualLock() to lock the buffer into memory
 * Sink:
 *    BadSink : Authenticate the user using LogonUserA()
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <wchar.h>
#include <windows.h>

#pragma comment(lib, "advapi32.lib")

#define PASSWORD_BUFFER_SIZE 100
#define DEFAULT_PASSWORD "Password1234!"
#define DEFAULT_USERNAME "User"
#define DEFAULT_DOMAIN "Domain"

static char *allocateLockedPasswordBuffer(size_t bufferSize)
{
    char *password = (char *)malloc(bufferSize * sizeof(char));
    if (password == NULL)
    {
        printLine("Memory could not be allocated");
        exit(1);
    }
    if (!VirtualLock(password, bufferSize * sizeof(char)))
    {
        free(password);
        printLine("Memory could not be locked");
        exit(1);
    }
    return password;
}

static void authenticateAndCleanup(char *password, size_t bufferSize)
{
    HANDLE userHandle = NULL;

    if (LogonUserA(
            DEFAULT_USERNAME,
            DEFAULT_DOMAIN,
            password,
            LOGON32_LOGON_NETWORK,
            LOGON32_PROVIDER_DEFAULT,
            &userHandle) != 0)
    {
        printLine("User logged in successfully.");
        CloseHandle(userHandle);
    }
    else
    {
        printLine("Unable to login.");
    }

    SecureZeroMemory(password, bufferSize * sizeof(char));
    VirtualUnlock(password, bufferSize * sizeof(char));
    free(password);
}

#ifndef OMITBAD

void CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_01_bad()
{
    /* Safety fix: lock sensitive password memory with VirtualLock() and wipe before freeing. */
    char *password = allocateLockedPasswordBuffer(PASSWORD_BUFFER_SIZE);
    snprintf(password, PASSWORD_BUFFER_SIZE, "%s", DEFAULT_PASSWORD);
    authenticateAndCleanup(password, PASSWORD_BUFFER_SIZE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    char *password = allocateLockedPasswordBuffer(PASSWORD_BUFFER_SIZE);
    snprintf(password, PASSWORD_BUFFER_SIZE, "%s", DEFAULT_PASSWORD);
    authenticateAndCleanup(password, PASSWORD_BUFFER_SIZE);
}

void CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
