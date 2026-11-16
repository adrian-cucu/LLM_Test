/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE459_Incomplete_Cleanup__char_01.c
Label Definition File: CWE459_Incomplete_Cleanup.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 459 Incomplete Cleanup
 * Sinks:
 *    GoodSink: Clean up properly
 *    BadSink : Don't unlink
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define TEMP_FILENAME_BUF_SIZE 50

#ifdef _WIN32
#define UNLINK _unlink
#define CLOSE _close
#define FDOPEN _fdopen
#define MKSTEMP _mkstemp

static int _mkstemp(char *tmpl)
{
    size_t len = 0;

    if (tmpl == NULL)
    {
        return -1;
    }

    len = strlen(tmpl) + 1;
    /* Safety fix: Validate template length before passing to _mktemp_s */
    if (len > TEMP_FILENAME_BUF_SIZE)
    {
        return -1;
    }

    if (_mktemp_s(tmpl, len) != 0)
    {
        return -1;
    }

    return _open(tmpl, _O_RDWR | _O_CREAT | _O_EXCL, _S_IREAD | _S_IWRITE);
}
#else
#include <unistd.h>
#define UNLINK unlink
#define CLOSE close
#define FDOPEN fdopen
#define MKSTEMP mkstemp
#endif

static void createWriteAndCleanupTempFile(char *filename)
{
    int fileDesc = MKSTEMP(filename);
    FILE *pFile = NULL;

    if (fileDesc == -1)
    {
        return;
    }

    pFile = FDOPEN(fileDesc, "w");
    if (pFile == NULL)
    {
        /* Safety fix: Close file descriptor and unlink file if fdopen() fails */
        CLOSE(fileDesc);
        UNLINK(filename);
        return;
    }

    fprintf(pFile, "Temporary file");
    fclose(pFile);
    /* Safety fix: Unlink the temporary file after closing to ensure complete cleanup */
    UNLINK(filename);
}

#ifndef OMITBAD

void CWE459_Incomplete_Cleanup__char_01_bad()
{
    char filename[] = "badXXXXXX";

    createWriteAndCleanupTempFile(filename);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    char filename[] = "goodXXXXXX";

    createWriteAndCleanupTempFile(filename);
}

void CWE459_Incomplete_Cleanup__char_01_good()
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
    CWE459_Incomplete_Cleanup__char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE459_Incomplete_Cleanup__char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
