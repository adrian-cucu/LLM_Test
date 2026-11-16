/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01.c
Label Definition File: CWE121_Stack_Based_Buffer_Overflow.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef _WIN32
#include <wchar.h>
#endif
#define SRC_STR "0123456789abcdef0123456789abcde"
typedef struct _charVoid
{
    char charFirst[16];
    void *voidSecond;
    void *voidThird;
} charVoid;

static void displayStructureCopy(void)
{
    charVoid value = {{0}, (void *)SRC_STR, NULL};
    printLine((char *)value.voidSecond);
    /* Bound the copy to the array: copying the struct size corrupted pointers. */
    memcpy(value.charFirst, SRC_STR, sizeof(value.charFirst) - 1);
    value.charFirst[sizeof(value.charFirst) - 1] = '\0';
    printLine(value.charFirst);
    printLine((char *)value.voidSecond);
}
#ifndef OMITBAD
void CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_bad(void)
{
    displayStructureCopy();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    displayStructureCopy();
}
void CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_good(void)
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
    CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE121_Stack_Based_Buffer_Overflow__char_type_overrun_memcpy_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
