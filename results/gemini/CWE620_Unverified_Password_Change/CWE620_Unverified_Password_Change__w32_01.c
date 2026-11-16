/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE620_Unverified_Password_Change__w32_01.c
Label Definition File: CWE620_Unverified_Password_Change__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 620 Unverified Password Change
 * Sinks: w32NetUserSetInfo
 *    GoodSink: Require old password to set new password using NetUserChangePassword()
 *    BadSink : Set new password without verifying the old one using NetUserSetInfo()
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <windows.h>
#include <lm.h>
#pragma comment(lib, "netapi32.lib")

#define USERNAME L"cwe620testuser"
#define PASSWORD_BUFFER_SIZE 256
#define USER_INFO_PASSWORD_LEVEL 1003

static void readPassword(const wchar_t *prompt, wchar_t *buffer, size_t bufferSize)
{
    if (buffer == NULL || bufferSize == 0)
    {
        return;
    }

    buffer[0] = L'\0';
    printWLine(prompt);
    if (fwscanf(stdin, L"%255ls", buffer) != 1)
    {
        buffer[0] = L'\0';
    }
    buffer[bufferSize - 1] = L'\0';
}

static void reportNetApiStatus(const wchar_t *apiName, NET_API_STATUS status)
{
    if (status == NERR_Success)
    {
        printWLine(L"Success!");
    }
    else
    {
        wprintf(L"%ls failed.  Status = %u = 0x%x\n", apiName, status, status);
    }
}

#ifndef OMITBAD

void CWE620_Unverified_Password_Change__w32_01_bad()
{
    wchar_t newPassword[PASSWORD_BUFFER_SIZE] = L"";
    USER_INFO_1003 myUserInfo;
    NET_API_STATUS status = 0;

    readPassword(L"Enter new password: ", newPassword, PASSWORD_BUFFER_SIZE);
    myUserInfo.usri1003_password = newPassword;

    status = NetUserSetInfo(NULL, USERNAME, USER_INFO_PASSWORD_LEVEL, (LPBYTE)&myUserInfo, NULL);
    reportNetApiStatus(L"NetUserSetInfo", status);

    SecureZeroMemory(newPassword, sizeof(newPassword));
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    wchar_t oldPassword[PASSWORD_BUFFER_SIZE] = L"";
    wchar_t newPassword[PASSWORD_BUFFER_SIZE] = L"";
    NET_API_STATUS status = 0;

    readPassword(L"Enter old password: ", oldPassword, PASSWORD_BUFFER_SIZE);
    readPassword(L"Enter new password: ", newPassword, PASSWORD_BUFFER_SIZE);

    status = NetUserChangePassword(NULL, USERNAME, oldPassword, newPassword);
    reportNetApiStatus(L"NetUserChangePassword", status);

    SecureZeroMemory(oldPassword, sizeof(oldPassword));
    SecureZeroMemory(newPassword, sizeof(newPassword));
}

void CWE620_Unverified_Password_Change__w32_01_good()
{
    good1();
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
    CWE620_Unverified_Password_Change__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE620_Unverified_Password_Change__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
