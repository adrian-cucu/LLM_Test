/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE124_Buffer_Underwrite__char_alloca_cpy_01.c
Label Definition File: CWE124_Buffer_Underwrite.stack.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
enum { BUFFER_SIZE = 100 };
static void copyToAllocatedBuffer(void)
{
    char *data = (char *)ALLOCA(BUFFER_SIZE);
    char source[BUFFER_SIZE];
    memset(data, 'A', BUFFER_SIZE - 1);
    data[BUFFER_SIZE - 1] = '\0';
    memset(source, 'C', sizeof(source) - 1);
    source[sizeof(source) - 1] = '\0';
    /* Keep the destination inside its allocation; data - 8 was undefined. */
    strcpy(data, source);
    printLine(data);
}
#ifndef OMITBAD
void CWE124_Buffer_Underwrite__char_alloca_cpy_01_bad(void)
{
    copyToAllocatedBuffer();
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    copyToAllocatedBuffer();
}
void CWE124_Buffer_Underwrite__char_alloca_cpy_01_good(void)
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
    CWE124_Buffer_Underwrite__char_alloca_cpy_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE124_Buffer_Underwrite__char_alloca_cpy_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
