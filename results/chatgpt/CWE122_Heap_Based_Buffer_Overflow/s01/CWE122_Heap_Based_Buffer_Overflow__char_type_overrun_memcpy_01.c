/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE122_Heap_Based_Buffer_Overflow__char_type_overrun_memcpy_01.c
Label Definition File: CWE122_Heap_Based_Buffer_Overflow.label.xml
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

static void displayHeapCopy(void)
{
    charVoid *value = malloc(sizeof(*value));
    if (value == NULL) exit(-1);
    value->voidSecond = (void *)SRC_STR;
    value->voidThird = NULL;
    printLine((char *)value->voidSecond);
    /* Copy only the character member, leaving both pointer members intact. */
    memcpy(value->charFirst, SRC_STR, sizeof(value->charFirst) - 1);
    value->charFirst[sizeof(value->charFirst) - 1] = '\0';
    printLine(value->charFirst);
    printLine((char *)value->voidSecond);
    free(value);
}
#ifndef OMITBAD
void CWE122_Heap_Based_Buffer_Overflow__char_type_overrun_memcpy_01_bad(void)
{
    displayHeapCopy();
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    displayHeapCopy();
}
void CWE122_Heap_Based_Buffer_Overflow__char_type_overrun_memcpy_01_good(void)
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
    CWE122_Heap_Based_Buffer_Overflow__char_type_overrun_memcpy_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE122_Heap_Based_Buffer_Overflow__char_type_overrun_memcpy_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
