/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE367_TOC_TOU__access_01.c
Label Definition File: CWE367_TOC_TOU.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 367 Time-of-Check Time-Of-Use Race Condition
 * Sinks: access
 *    GoodSink: Open the file without checking the status information
 *    BadSink : Get status information on file using access(), open, write to, and close the file
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifdef _WIN32
#define OPEN _open
#define WRITE _write
#define O_RDWR _O_RDWR
#define CLOSE _close
#else
#include <unistd.h>
#define OPEN open
#define WRITE write
#define CLOSE close
#endif

#define FILENAME_BUFFER_SIZE 100
#define BAD_SINK_STRING "Bad Sink..."
#define GOOD_SINK_STRING "Good Sink..."

static void readFilenameFromStdin(char *buffer, size_t bufferSize)
{
    size_t len = 0;

    if (fgets(buffer, (int)bufferSize, stdin) == NULL)
    {
        printLine("fgets() failed");
        buffer[0] = '\0';
        return;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
}

static void openAndWriteFile(const char *filename, const char *content)
{
    int fileDesc = -1;

    /* Safety fix: Open the file directly without a prior access() check to avoid a TOCTOU race condition */
    fileDesc = OPEN(filename, O_RDWR);
    if (fileDesc == -1)
    {
        exit(1);
    }

    if (WRITE(fileDesc, content, (unsigned int)strlen(content)) == -1)
    {
        /* Safety fix: Close the file descriptor before exiting on write failure */
        CLOSE(fileDesc);
        exit(1);
    }

    CLOSE(fileDesc);
}

#ifndef OMITBAD

void CWE367_TOC_TOU__access_01_bad()
{
    char filename[FILENAME_BUFFER_SIZE] = "";

    readFilenameFromStdin(filename, sizeof(filename));
    openAndWriteFile(filename, BAD_SINK_STRING);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    char filename[FILENAME_BUFFER_SIZE] = "";

    readFilenameFromStdin(filename, sizeof(filename));
    openAndWriteFile(filename, GOOD_SINK_STRING);
}

void CWE367_TOC_TOU__access_01_good()
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
    CWE367_TOC_TOU__access_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE367_TOC_TOU__access_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
