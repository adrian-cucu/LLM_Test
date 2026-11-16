/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE126_Buffer_Overread__char_alloca_loop_01.c
Label Definition File: CWE126_Buffer_Overread.stack.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
static void copyAndPrint(const char *source)
{
    char destination[100];
    size_t i;
    /* Stop at the source terminator instead of reading the destination length. */
    for (i = 0; i + 1 < sizeof(destination) && source[i] != '\0'; ++i)
    {
        destination[i] = source[i];
    }
    destination[i] = '\0';
    printLine(destination);
}
#ifndef OMITBAD
void CWE126_Buffer_Overread__char_alloca_loop_01_bad(void)
{
    char *smallBuffer = (char *)ALLOCA(50);
    char *largeBuffer = (char *)ALLOCA(100);
    memset(smallBuffer, 'A', 49);
    smallBuffer[49] = '\0';
    memset(largeBuffer, 'A', 99);
    largeBuffer[99] = '\0';
    copyAndPrint(smallBuffer);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char *smallBuffer = (char *)ALLOCA(50);
    char *largeBuffer = (char *)ALLOCA(100);
    memset(smallBuffer, 'A', 49);
    smallBuffer[49] = '\0';
    memset(largeBuffer, 'A', 99);
    largeBuffer[99] = '\0';
    copyAndPrint(largeBuffer);
}
void CWE126_Buffer_Overread__char_alloca_loop_01_good(void)
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
    CWE126_Buffer_Overread__char_alloca_loop_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE126_Buffer_Overread__char_alloca_loop_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
