/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE259_Hard_Coded_Password__w32_char_01.c
Label Definition File: CWE259_Hard_Coded_Password__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
#define PASSWORD "ABCD1234!"
static void authenticate(const char *password)
{
    HANDLE user;
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
}
#ifndef OMITBAD
void CWE259_Hard_Coded_Password__w32_char_01_bad(void)
{
    char password[100] = PASSWORD;
    authenticate(password);
    /* Wipe the mutable copy without changing the configured credential. */
    SecureZeroMemory(password, sizeof(password));
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char password[100] = "";
    size_t length;
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
    }
    length = strlen(password);
    /* Keep the original last-character removal policy. */
    if (length > 0) password[length - 1] = '\0';
    authenticate(password);
    SecureZeroMemory(password, sizeof(password));
}
void CWE259_Hard_Coded_Password__w32_char_01_good(void)
{
    goodG2B();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE259_Hard_Coded_Password__w32_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE259_Hard_Coded_Password__w32_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
