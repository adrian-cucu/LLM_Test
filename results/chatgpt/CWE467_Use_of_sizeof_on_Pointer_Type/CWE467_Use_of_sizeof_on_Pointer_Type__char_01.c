/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE467_Use_of_sizeof_on_Pointer_Type__char_01.c
Label Definition File: CWE467_Use_of_sizeof_on_Pointer_Type.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static void printAllocatedCharacter(char value, size_t allocationSize)
{
    char *character = malloc(allocationSize);
    if (character == NULL) { exit(-1); }
    *character = value;
    printHexCharLine(*character);
    free(character);
}
#ifndef OMITBAD
void CWE467_Use_of_sizeof_on_Pointer_Type__char_01_bad()
{
    /* Retain this variant's allocation size; it is sufficient for one char. */
    printAllocatedCharacter('B', sizeof(char *));
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    printAllocatedCharacter('G', sizeof(char));
}
void CWE467_Use_of_sizeof_on_Pointer_Type__char_01_good()
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
    CWE467_Use_of_sizeof_on_Pointer_Type__char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE467_Use_of_sizeof_on_Pointer_Type__char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
