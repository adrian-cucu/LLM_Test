/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE615_Info_Exposure_by_Comment__w32_01.c
Label Definition File: CWE615_Info_Exposure_by_Comment__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 615 Information Exposure by Comment
 * Sinks:
 *    GoodSink: Do not place username and password in comment
 *    BadSink : Information exposure by comment
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <windows.h>
#pragma comment(lib, "advapi32.lib")

#define PASSWORD "ABCD1234!"
#define USERNAME "XXXXX Smith!"
#define DEFAULT_DOMAIN "Domain"

static void attemptLogon(const char *successMessage)
{
    HANDLE userHandle = NULL;

    if (LogonUserA(
            USERNAME,
            DEFAULT_DOMAIN,
            PASSWORD,
            LOGON32_LOGON_NETWORK,
            LOGON32_PROVIDER_DEFAULT,
            &userHandle) != 0)
    {
        printLine(successMessage);
        CloseHandle(userHandle);
    }
    else
    {
        printLine("Unable to login.");
    }
}

#ifndef OMITBAD

void CWE615_Info_Exposure_by_Comment__w32_01_bad()
{
    /* Safety fix: removed sensitive username and password from comment. */
    attemptLogon("User logged in successfully");
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    attemptLogon("User logged in successfully with password");
}

void CWE615_Info_Exposure_by_Comment__w32_01_good()
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
    CWE615_Info_Exposure_by_Comment__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE615_Info_Exposure_by_Comment__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
