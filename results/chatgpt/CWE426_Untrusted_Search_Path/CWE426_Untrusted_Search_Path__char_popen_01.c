/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE426_Untrusted_Search_Path__char_popen_01.c
Label Definition File: CWE426_Untrusted_Search_Path.label.xml
Template File: sources-sink-01.tmpl.c
*/
#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#endif
#include "std_testcase.h"
#include <wchar.h>
#ifdef _WIN32
#define BAD_OS_COMMAND "cmd.exe /c dir"
/* REVIEWERS NOTE: This path assumes Windows is installed on drive C:.
 * It may not be correct on older or alternate-drive installations. */
#define GOOD_OS_COMMAND "c:\\windows\\system32\\cmd.exe /c dir"
#define POPEN _popen
#define PCLOSE _pclose
#else
#define BAD_OS_COMMAND "ls -la"
#define GOOD_OS_COMMAND "/usr/bin/ls -la"
#define POPEN popen
#define PCLOSE pclose
#endif

static void executeCommand(const char *command)
{
#ifdef _WIN32
    FILE *pipe = POPEN(command, "wb");
#else
    /* POSIX popen accepts only "r" or "w", not a binary-mode suffix. */
    FILE *pipe = POPEN(command, "w");
#endif
    if (pipe != NULL)
    {
        PCLOSE(pipe);
    }
}
#ifndef OMITBAD
void CWE426_Untrusted_Search_Path__char_popen_01_bad()
{
    executeCommand(BAD_OS_COMMAND);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    executeCommand(GOOD_OS_COMMAND);
}
void CWE426_Untrusted_Search_Path__char_popen_01_good()
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
    CWE426_Untrusted_Search_Path__char_popen_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE426_Untrusted_Search_Path__char_popen_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
