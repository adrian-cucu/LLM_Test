/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE401_Memory_Leak__char_calloc_01.c
Label Definition File: CWE401_Memory_Leak.c.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>

static void printAllocatedString(void)
{
    char *data = calloc(100, sizeof(*data));
    if (data == NULL) { exit(-1); }
    strcpy(data, "A String");
    printLine(data);
    /* The allocation has a single owner and is released after its last use. */
    free(data);
}
#ifndef OMITBAD
void CWE401_Memory_Leak__char_calloc_01_bad()
{
    printAllocatedString();
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char data[100];
    strcpy(data, "A String");
    printLine(data);
}
static void goodB2G(void)
{
    printAllocatedString();
}
void CWE401_Memory_Leak__char_calloc_01_good()
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE401_Memory_Leak__char_calloc_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE401_Memory_Leak__char_calloc_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
