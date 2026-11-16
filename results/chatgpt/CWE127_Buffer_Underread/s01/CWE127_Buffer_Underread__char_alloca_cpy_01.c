/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE127_Buffer_Underread__char_alloca_cpy_01.c
Label Definition File: CWE127_Buffer_Underread.stack.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
enum { SOURCE_SIZE = 100, DESTINATION_SIZE = 200 };
static void copyAllocatedString(void)
{
    char *source = (char *)ALLOCA(SOURCE_SIZE);
    char destination[DESTINATION_SIZE];
    memset(source, 'A', SOURCE_SIZE - 1);
    source[SOURCE_SIZE - 1] = '\0';
    memset(destination, 'C', sizeof(destination) - 1);
    destination[sizeof(destination) - 1] = '\0';
    /* Use the allocation's start, not an out-of-bounds source - 8 pointer. */
    strcpy(destination, source);
    printLine(destination);
}
#ifndef OMITBAD
void CWE127_Buffer_Underread__char_alloca_cpy_01_bad(void)
{
    copyAllocatedString();
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    copyAllocatedString();
}
void CWE127_Buffer_Underread__char_alloca_cpy_01_good(void)
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
    CWE127_Buffer_Underread__char_alloca_cpy_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE127_Buffer_Underread__char_alloca_cpy_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
