/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE404_Improper_Resource_Shutdown__fopen_w32_close_01.c
Label Definition File: CWE404_Improper_Resource_Shutdown.label.xml
Template File: source-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 404 Improper Resource Shutdown or Release
 * BadSource: fopen Open a file using fopen()
 * Sinks: w32_close
 *    GoodSink: Close the file using fclose()
 *    BadSink : Close the file using close()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define TARGET_FILENAME "BadSource_fopen.txt"
#define FILE_OPEN_MODE "w+"

static void openAndCloseFileSafely(const char *filename, const char *mode)
{
    FILE *data = NULL;

    data = fopen(filename, mode);
    if (data != NULL)
    {
        /* Safety fix: Close FILE* stream using fclose() instead of _close((int)data) */
        fclose(data);
    }
}

#ifndef OMITBAD

void CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_bad()
{
    openAndCloseFileSafely(TARGET_FILENAME, FILE_OPEN_MODE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodB2G() uses the BadSource with the GoodSink */
static void goodB2G()
{
    openAndCloseFileSafely(TARGET_FILENAME, FILE_OPEN_MODE);
}

void CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_good()
{
    goodB2G();
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
    CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
