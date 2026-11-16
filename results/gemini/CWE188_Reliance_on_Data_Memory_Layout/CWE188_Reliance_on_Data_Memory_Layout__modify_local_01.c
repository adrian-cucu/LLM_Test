/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE188_Reliance_on_Data_Memory_Layout__modify_local_01.c
Label Definition File: CWE188_Reliance_on_Data_Memory_Layout.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 188 Reliance on Data Memory Layout
 * Sinks: modify_local
 *    GoodSink: Modify the second field of the struct using the field name
 *    BadSink : Attempt to modify second field in struct, assuming the first field is an int
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define INITIAL_CHAR_VAL 1
#define UPDATED_INT_VAL 5

static void updateAndPrintStruct(void)
{
    struct
    {
        char charFirst;
        int intSecond;
    } structCharInt = { INITIAL_CHAR_VAL, 0 };

    /* Safety fix: access structCharInt.intSecond directly instead of pointer arithmetic on struct layout */
    structCharInt.intSecond = UPDATED_INT_VAL;
    printIntLine(structCharInt.charFirst);
    printIntLine(structCharInt.intSecond);
}

#ifndef OMITBAD

void CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_bad()
{
    updateAndPrintStruct();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    updateAndPrintStruct();
}

void CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_good()
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
    CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE188_Reliance_on_Data_Memory_Layout__modify_local_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
