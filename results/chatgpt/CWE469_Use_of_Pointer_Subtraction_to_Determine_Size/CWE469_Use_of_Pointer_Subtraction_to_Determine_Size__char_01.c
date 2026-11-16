/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01.c
Label Definition File: CWE469_Use_of_Pointer_Subtraction_to_Determine_Size.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#define SOURCE_STRING "abc/opqrstu"

static void printSlashIndex(void)
{
    char source[] = SOURCE_STRING;
    const char *slash = strchr(source, '/');
    size_t index;
    if (slash == NULL) { exit(1); }
    /* Pointer differences are defined only within the same array. */
    index = (size_t)(slash - source);
    printUnsignedLine(index);
}
#ifndef OMITBAD
void CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_bad()
{
    printSlashIndex();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printSlashIndex();
}
void CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_good()
{
    good1();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
