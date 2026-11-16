/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_char_01.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>

static void allocateAndRelease(void)
{
    char *data = malloc(100 * sizeof(*data));
    if (data == NULL) { exit(-1); }
    /* One allocation must have exactly one corresponding release. */
    free(data);
}
#ifndef OMITBAD
void CWE415_Double_Free__malloc_free_char_01_bad()
{
    allocateAndRelease();
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    allocateAndRelease();
}
static void goodB2G(void)
{
    allocateAndRelease();
}
void CWE415_Double_Free__malloc_free_char_01_good()
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
    CWE415_Double_Free__malloc_free_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
