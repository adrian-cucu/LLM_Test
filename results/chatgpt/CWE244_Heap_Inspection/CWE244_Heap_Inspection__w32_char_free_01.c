/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE244_Heap_Inspection__w32_char_free_01.c
Label Definition File: CWE244_Heap_Inspection__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
enum { PASSWORD_CAPACITY = 100 };
static void authenticateHeapPassword(void)
{
    char *password = malloc(PASSWORD_CAPACITY);
    size_t length;
    HANDLE user;
    if (password == NULL) exit(-1);
    password[0] = '\0';
    if (fgets(password, PASSWORD_CAPACITY, stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
    }
    length = strlen(password);
    /* Preserve the original last-character removal before authentication. */
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
    /* Wipe the whole allocation before releasing it, not just strlen bytes. */
    SecureZeroMemory(password, PASSWORD_CAPACITY);
    free(password);
}
#ifndef OMITBAD
void CWE244_Heap_Inspection__w32_char_free_01_bad(void)
{
    authenticateHeapPassword();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    authenticateHeapPassword();
}
void CWE244_Heap_Inspection__w32_char_free_01_good(void)
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
    CWE244_Heap_Inspection__w32_char_free_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE244_Heap_Inspection__w32_char_free_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
