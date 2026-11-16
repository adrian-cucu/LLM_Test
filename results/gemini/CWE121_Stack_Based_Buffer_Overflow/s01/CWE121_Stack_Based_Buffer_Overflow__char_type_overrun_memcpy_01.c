/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01.c
Label Definition File: CWE121_Stack_Based_Buffer_Overflow.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 121 Stack Based Buffer Overflow
 * Sinks: type_overrun_memcpy
 *    GoodSink: Perform the memcpy() and prevent overwriting part of the structure
 *    BadSink : Overwrite part of the structure by incorrectly using the sizeof(struct) in memcpy()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

/* SRC_STR is 32 char long, including the null terminator, for 64-bit architectures */
#define SRC_STR "0123456789abcdef0123456789abcde"
#define CHAR_FIRST_SIZE 16

typedef struct _charVoid
{
    char charFirst[CHAR_FIRST_SIZE];
    void * voidSecond;
    void * voidThird;
} charVoid;

static void copyAndPrintCharVoid(size_t copySize)
{
    charVoid structCharVoid;
    size_t boundedSize = copySize;

    memset(&structCharVoid, 0, sizeof(structCharVoid));
    structCharVoid.voidSecond = (void *)SRC_STR;
    printLine((char *)structCharVoid.voidSecond);

    /* Safety fix: clamp copySize to sizeof(structCharVoid.charFirst) to prevent stack buffer overflow */
    if (boundedSize > sizeof(structCharVoid.charFirst))
    {
        boundedSize = sizeof(structCharVoid.charFirst);
    }

    memcpy(structCharVoid.charFirst, SRC_STR, boundedSize);
    structCharVoid.charFirst[CHAR_FIRST_SIZE - 1] = '\0';
    printLine((char *)structCharVoid.charFirst);
    printLine((char *)structCharVoid.voidSecond);
}

#ifndef OMITBAD

void CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_bad()
{
    copyAndPrintCharVoid(sizeof(charVoid));
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    copyAndPrintCharVoid(CHAR_FIRST_SIZE);
}

void CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_good()
{
    good1();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
