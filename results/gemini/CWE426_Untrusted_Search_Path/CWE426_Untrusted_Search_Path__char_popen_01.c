/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE426_Untrusted_Search_Path__char_popen_01.c
Label Definition File: CWE426_Untrusted_Search_Path.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 426 Untrusted Search Path
 * BadSource:  Don't specify the full path in the OS command
 * GoodSource: Specify the full path in the OS command
 * Sink: popen
 *    BadSink : Execute the popen function
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

#define COMMAND_BUFFER_SIZE 100

#ifdef _WIN32
#define GOOD_OS_COMMAND "c:\\windows\\system32\\cmd.exe /c dir"
#define POPEN _popen
#define PCLOSE _pclose
#else /* NOT _WIN32 */
#define GOOD_OS_COMMAND "/usr/bin/ls -la"
#define POPEN popen
#define PCLOSE pclose
#endif /* end NOT _WIN32 */

static void executeCommandWithFullPath(const char *command)
{
    char dataBuffer[COMMAND_BUFFER_SIZE] = "";
    FILE *pipe = NULL;

    snprintf(dataBuffer, sizeof(dataBuffer), "%s", command);
    pipe = POPEN(dataBuffer, "wb");
    if (pipe != NULL)
    {
        PCLOSE(pipe);
    }
}

#ifndef OMITBAD

void CWE426_Untrusted_Search_Path__char_popen_01_bad()
{
    /* Safety fix: Specify the full executable path to prevent untrusted search path execution */
    executeCommandWithFullPath(GOOD_OS_COMMAND);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    executeCommandWithFullPath(GOOD_OS_COMMAND);
}

void CWE426_Untrusted_Search_Path__char_popen_01_good()
{
    goodG2B();
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
    CWE426_Untrusted_Search_Path__char_popen_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE426_Untrusted_Search_Path__char_popen_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
