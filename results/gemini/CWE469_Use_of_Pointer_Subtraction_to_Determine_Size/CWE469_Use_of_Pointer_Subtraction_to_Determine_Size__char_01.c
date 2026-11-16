/*
 * @description
 * CWE: 469 Use of Pointer Subtraction to Determine Size
 * Sinks:
 *    GoodSink: Subtract pointers within the same string
 *    BadSink : Subtract pointers to two different strings
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#include <wchar.h>

#define SOURCE_STRING "abc/opqrstu"
#define TARGET_CHAR '/'

static void printSlashIndex(void)
{
    char string1[] = SOURCE_STRING;
    const char *slashInString1 = strchr(string1, TARGET_CHAR);
    size_t indexOfSlashInString1 = 0;

    if (slashInString1 == NULL)
    {
        return;
    }

    /* Safety fix: subtract pointers within the same array (string1) to avoid undefined behavior */
    indexOfSlashInString1 = (size_t)(slashInString1 - string1);
    printUnsignedLine(indexOfSlashInString1);
}

#ifndef OMITBAD

void CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_bad()
{
    printSlashIndex();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printSlashIndex();
}

void CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE469_Use_of_Pointer_Subtraction_to_Determine_Size__char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
