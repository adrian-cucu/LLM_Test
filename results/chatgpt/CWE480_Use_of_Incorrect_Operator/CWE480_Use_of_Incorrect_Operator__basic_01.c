/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE480_Use_of_Incorrect_Operator__basic_01.c
Label Definition File: CWE480_Use_of_Incorrect_Operator__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"

static char *staticStringBad = "Hello";
static char *staticStringGood = "Hello";

static char *helperBad(void)
{
    if (rand() % 2 == 0) { return NULL; }
    return staticStringBad;
}
static char *helperGood(void)
{
    if (rand() % 2 == 0) { return NULL; }
    return staticStringGood;
}
#ifndef OMITBAD
void CWE480_Use_of_Incorrect_Operator__basic_01_bad()
{
    /* This variant tests the address, not the result: do not consume rand(). */
    char *(*provider)(void) = helperBad;
    if (provider == NULL)
    {
        printLine("Got a NULL");
    }
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    char *result = helperGood();
    if (result == NULL)
    {
        printLine("Got a NULL");
    }
}
void CWE480_Use_of_Incorrect_Operator__basic_01_good()
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
    CWE480_Use_of_Incorrect_Operator__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE480_Use_of_Incorrect_Operator__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
