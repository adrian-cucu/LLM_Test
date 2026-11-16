/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE284_Improper_Access_Control__w32_char_CreateDesktop_01.c
Label Definition File: CWE284_Improper_Access_Control__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 284 Improper Access Control
 * Sinks: CreateDesktop
 *    GoodSink: Create a desktop using CreateDesktopA() without excessive privileges
 *    BadSink : Create a desktop using CreateDesktopA() with excessive privileges
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#pragma comment( lib, "user32" )

#define DESKTOP_NAME "DesktopExample"

static void createRestrictedDesktop(void)
{
    HDESK hDesk = NULL;

    /* Safety fix: use least-privilege GENERIC_READ instead of GENERIC_ALL */
    hDesk = CreateDesktopA(
                DESKTOP_NAME,
                NULL,
                NULL,
                0,
                GENERIC_READ,
                NULL);
    if (hDesk == NULL)
    {
        printLine("Desktop could not be created");
        return;
    }

    printLine("Desktop created successfully");
    CloseDesktop(hDesk);
}

#ifndef OMITBAD

void CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_bad()
{
    createRestrictedDesktop();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    createRestrictedDesktop();
}

void CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_good()
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
    CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE284_Improper_Access_Control__w32_char_CreateDesktop_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
