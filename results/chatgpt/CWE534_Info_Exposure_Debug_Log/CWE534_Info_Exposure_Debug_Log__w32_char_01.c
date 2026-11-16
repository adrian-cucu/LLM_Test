/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE534_Info_Exposure_Debug_Log__w32_char_01.c
Label Definition File: CWE534_Info_Exposure_Debug_Log__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")

static void attemptLogin(int includePassword)
{
    char password[100] = "";
    size_t length;
    HANDLE token;
    FILE *log = fopen("debug.txt", "a+");
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
    }
    length = strlen(password);
    if (length > 0) { password[length - 1] = '\0'; }
    if (LogonUserA("User", "Domain", password, LOGON32_LOGON_NETWORK,
                   LOGON32_PROVIDER_DEFAULT, &token) != 0)
    {
        printLine("User logged in successfully.");
        CloseHandle(token);
    }
    else
    {
        printLine("Unable to login.");
    }
    /* A failed fopen must not be passed to fprintf. Authentication still runs. */
    if (log != NULL)
    {
        if (includePassword)
        {
            fprintf(log, "User attempted access with password: %s\n", password);
        }
        else
        {
            fprintf(log, "User attempted access\n");
        }
        fclose(log);
    }
}
#ifndef OMITBAD
void CWE534_Info_Exposure_Debug_Log__w32_char_01_bad()
{
    attemptLogin(1);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    attemptLogin(0);
}
void CWE534_Info_Exposure_Debug_Log__w32_char_01_good()
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
    CWE534_Info_Exposure_Debug_Log__w32_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE534_Info_Exposure_Debug_Log__w32_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
