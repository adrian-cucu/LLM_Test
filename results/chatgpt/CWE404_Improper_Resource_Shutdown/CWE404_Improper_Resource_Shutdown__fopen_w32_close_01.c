/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE404_Improper_Resource_Shutdown__fopen_w32_close_01.c
Label Definition File: CWE404_Improper_Resource_Shutdown.label.xml
Template File: source-sinks-01.tmpl.c
*/
#include "std_testcase.h"

static void openAndCloseFile(void)
{
    FILE *stream = fopen("BadSource_fopen.txt", "w+");
    if (stream == NULL) { return; }
    /* A FILE pointer is not a descriptor; fclose releases both resources. */
    if (fclose(stream) == EOF)
    {
        printLine("fclose() failed");
    }
}
#ifndef OMITBAD
void CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_bad()
{
    openAndCloseFile();
}
#endif
#ifndef OMITGOOD
static void goodB2G(void)
{
    openAndCloseFile();
}
void CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_good()
{
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE404_Improper_Resource_Shutdown__fopen_w32_close_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
