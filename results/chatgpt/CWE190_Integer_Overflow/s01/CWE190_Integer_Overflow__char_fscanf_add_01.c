/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE190_Integer_Overflow__char_fscanf_add_01.c
Label Definition File: CWE190_Integer_Overflow.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <limits.h>
static char readCharacter(void)
{
    char data = ' ';
    if (fscanf(stdin, "%c", &data) != 1) return ' ';
    return data;
}
#ifndef OMITBAD
void CWE190_Integer_Overflow__char_fscanf_add_01_bad(void)
{
    char data = readCharacter();
    char result = (char)(data + 1);
    printHexCharLine(result);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char data = 2;
    printHexCharLine((char)(data + 1));
}
static void goodB2G(void)
{
    char data = readCharacter();
    if (data < CHAR_MAX)
    {
        printHexCharLine((char)(data + 1));
    }
    else
    {
        printLine("data value is too large to perform arithmetic safely.");
    }
}
void CWE190_Integer_Overflow__char_fscanf_add_01_good(void)
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE190_Integer_Overflow__char_fscanf_add_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE190_Integer_Overflow__char_fscanf_add_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
