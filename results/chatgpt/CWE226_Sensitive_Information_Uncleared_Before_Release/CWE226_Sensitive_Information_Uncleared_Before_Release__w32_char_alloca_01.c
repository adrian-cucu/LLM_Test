/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01.c
Label Definition File: CWE226_Sensitive_Information_Uncleared_Before_Release__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
enum { PASSWORD_CAPACITY = 100 };
static void authenticateStackPassword(void)
{
    char *password = (char *)ALLOCA(PASSWORD_CAPACITY);
    size_t length;
    HANDLE user;
    password[0] = '\0';
    if (fgets(password, PASSWORD_CAPACITY, stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
    }
    length = strlen(password);
    /* Retain the original last-character removal policy for authentication. */
    if (length > 0) password[length - 1] = '\0';
    if (LogonUserA("User", "Domain", password, LOGON32_LOGON_NETWORK,
                   LOGON32_PROVIDER_DEFAULT, &user))
    {
        printLine("User logged in successfully.");
        CloseHandle(user);
    }
    else
    {
        printLine("Unable to login.");
    }
    /* Clear the entire allocation, including bytes beyond an embedded NUL. */
    SecureZeroMemory(password, PASSWORD_CAPACITY);
}
#ifndef OMITBAD
void CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_bad(void)
{
    authenticateStackPassword();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    authenticateStackPassword();
}
void CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_good(void)
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
    CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE226_Sensitive_Information_Uncleared_Before_Release__w32_char_alloca_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
