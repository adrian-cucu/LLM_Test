/*
 * @description
 * CWE: 480 Use of Incorrect Operator
 * Sinks:
 *    GoodSink: Include parens
 *    BadSink : Forget parens
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#define RANDOM_MODULO 2

static const char *staticStringBad = "Hello";
static const char *staticStringGood = "Hello";

static const char * helperBad(void)
{
    if ((rand() % RANDOM_MODULO) == 0)
    {
        return NULL;
    }
    return staticStringBad;
}

static const char * helperGood(void)
{
    if ((rand() % RANDOM_MODULO) == 0)
    {
        return NULL;
    }
    return staticStringGood;
}

#ifndef OMITBAD

void CWE480_Use_of_Incorrect_Operator__basic_01_bad()
{
    /* Safety fix: invoke helperBad() with () instead of comparing function address to NULL */
    if (helperBad() == NULL)
    {
        printLine("Got a NULL");
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    if (helperGood() == NULL)
    {
        printLine("Got a NULL");
    }
}

void CWE480_Use_of_Incorrect_Operator__basic_01_good()
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
    CWE480_Use_of_Incorrect_Operator__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE480_Use_of_Incorrect_Operator__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
