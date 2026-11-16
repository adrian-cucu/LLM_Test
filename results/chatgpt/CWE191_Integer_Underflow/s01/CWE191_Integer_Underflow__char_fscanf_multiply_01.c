/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE191_Integer_Underflow__char_fscanf_multiply_01.c
Label Definition File: CWE191_Integer_Underflow.label.xml
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
void CWE191_Integer_Underflow__char_fscanf_multiply_01_bad(void)
{
    char data = readCharacter();
    if (data < 0)
    {
        char result = (char)(data * 2);
        printHexCharLine(result);
    }
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char data = -2;
    if (data < 0) printHexCharLine((char)(data * 2));
}
static void goodB2G(void)
{
    char data = readCharacter();
    if (data < 0)
    {
        if (data > CHAR_MIN / 2)
        {
            printHexCharLine((char)(data * 2));
        }
        else
        {
            printLine("data value is too small to perform multiplication.");
        }
    }
}
void CWE191_Integer_Underflow__char_fscanf_multiply_01_good(void)
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
    CWE191_Integer_Underflow__char_fscanf_multiply_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE191_Integer_Underflow__char_fscanf_multiply_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
