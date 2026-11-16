/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE377_Insecure_Temporary_File__char_mktemp_01.c
Label Definition File: CWE377_Insecure_Temporary_File.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 377 Insecure Temporary File
 * Sinks: mktemp
 *    GoodSink: Create and open a temporary file more securely, with mkstemp()
 *    BadSink : Create and open a temporary file, created with mktemp(), insecurely
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#define TEMP_FILENAME_BUF_SIZE 50

#ifdef _WIN32
#define OPEN _open
#define CLOSE _close
#define MKSTEMP _mkstemp

static int _mkstemp(const char *tmpl)
{
    size_t len = 0;
    char buf[TEMP_FILENAME_BUF_SIZE] = "";

    if (tmpl == NULL)
    {
        return -1;
    }

    len = strlen(tmpl) + 1;
    /* Safety fix: Validate template length before copying into fixed-size buffer */
    if (len > sizeof(buf))
    {
        return -1;
    }

    memcpy(buf, tmpl, len);
    if (_mktemp_s(buf, len) != 0)
    {
        return -1;
    }

    return _open(buf, _O_RDWR | _O_CREAT | _O_EXCL, _S_IREAD | _S_IWRITE);
}
#else
#define OPEN open
#define CLOSE close
#define MKSTEMP mkstemp
#endif

static void createAndCloseTempFile(char *tmpl)
{
    /* Safety fix: Use mkstemp() to atomically create and open the temporary file with exclusive flags */
    int fileDesc = MKSTEMP(tmpl);

    printLine(tmpl);
    if (fileDesc != -1)
    {
        printLine("Temporary file was opened...now closing file");
        CLOSE(fileDesc);
    }
}

#ifndef OMITBAD

void CWE377_Insecure_Temporary_File__char_mktemp_01_bad()
{
    char tmpl[] = "fnXXXXXX";

    createAndCloseTempFile(tmpl);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    char filename[] = "/tmp/fileXXXXXX";

    createAndCloseTempFile(filename);
}

void CWE377_Insecure_Temporary_File__char_mktemp_01_good()
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
    CWE377_Insecure_Temporary_File__char_mktemp_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE377_Insecure_Temporary_File__char_mktemp_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
