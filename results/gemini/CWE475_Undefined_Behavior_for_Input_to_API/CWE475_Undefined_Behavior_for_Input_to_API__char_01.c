/*
 * @description
 * CWE: 475 Undefined Behavior for Input to API
 * Sinks:
 *    GoodSink: Copy overlapping memory regions using memmove()
 *    BadSink : Copy overlapping memory regions using memcpy()
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#include <wchar.h>

#define BUFFER_SIZE 100
#define COPY_SRC_OFFSET 4
#define COPY_DST_OFFSET 6
#define COPY_LEN 10
#define ALPHABET_STR "abcdefghijklmnopqrstuvwxyz"

static void copyOverlappingAndPrint(void)
{
    char dataBuffer[BUFFER_SIZE] = "";
    char *data = dataBuffer;

    strcpy(data, ALPHABET_STR);
    /* Safety fix: use memmove() instead of memcpy() for overlapping memory regions */
    memmove(data + COPY_DST_OFFSET, data + COPY_SRC_OFFSET, COPY_LEN * sizeof(char));
    printLine(data);
}

#ifndef OMITBAD

void CWE475_Undefined_Behavior_for_Input_to_API__char_01_bad()
{
    copyOverlappingAndPrint();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    copyOverlappingAndPrint();
}

void CWE475_Undefined_Behavior_for_Input_to_API__char_01_good()
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
    CWE475_Undefined_Behavior_for_Input_to_API__char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE475_Undefined_Behavior_for_Input_to_API__char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
