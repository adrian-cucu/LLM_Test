/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE196_Unsigned_to_Signed_Conversion_Error__basic_01.c
Label Definition File: CWE196_Unsigned_to_Signed_Conversion_Error__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 196 Unsigned To Signed Conversion Error
 * Sinks:
 *    GoodSink: Don't allow very large values of intUnsigned
 *    BadSink : Convert a possibly large unsigned int (larger than INT_MAX) to an int
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

static unsigned int generateRandomUnsigned(void)
{
    unsigned int val = (unsigned int)rand();
    if (rand() % 2 == 0)
    {
        val = UINT_MAX - val;
    }
    return val;
}

static void convertAndPrintSigned(unsigned int intUnsigned)
{
    int intSigned = 0;

    /* Safety fix: reject unsigned values exceeding INT_MAX before converting to signed int */
    if (intUnsigned > (unsigned int)INT_MAX)
    {
        exit(1);
    }

    intSigned = (int)intUnsigned;
    printIntLine(intSigned);
}

#ifndef OMITBAD

void CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_bad()
{
    unsigned int intUnsigned = generateRandomUnsigned();
    convertAndPrintSigned(intUnsigned);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    unsigned int intUnsigned = generateRandomUnsigned();
    convertAndPrintSigned(intUnsigned);
}

void CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_good()
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
    CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE196_Unsigned_to_Signed_Conversion_Error__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
