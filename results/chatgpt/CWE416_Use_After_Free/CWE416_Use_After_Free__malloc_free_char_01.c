/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__malloc_free_char_01.c
Label Definition File: CWE416_Use_After_Free__malloc_free.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>

static void useAllocatedString(int printData)
{
    const size_t capacity = 100;
    char *data = malloc(capacity * sizeof(*data));
    if (data == NULL) { exit(-1); }
    memset(data, 'A', capacity - 1);
    data[capacity - 1] = '\0';
    /* Keep the allocation alive until its final use, then release it. */
    if (printData) { printLine(data); }
    free(data);
}
#ifndef OMITBAD
void CWE416_Use_After_Free__malloc_free_char_01_bad()
{
    useAllocatedString(1);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    useAllocatedString(1);
}
static void goodB2G(void)
{
    useAllocatedString(0);
}
void CWE416_Use_After_Free__malloc_free_char_01_good()
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
    CWE416_Use_After_Free__malloc_free_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE416_Use_After_Free__malloc_free_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
