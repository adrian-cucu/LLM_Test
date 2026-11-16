/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__struct_01.c
Label Definition File: CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__struct.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 588 Attempt to Access Child of Non Structure Pointer
 * BadSource:  Void pointer to an int
 * GoodSource: Void pointer to a twoints struct
 * Sink:
 *    BadSink : Print data
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#define DEFAULT_STRUCT_INT_ONE 0
#define DEFAULT_STRUCT_INT_TWO 0

static void printInitializedStruct(void)
{
    twoIntsStruct dataGoodBuffer;
    void *data = NULL;

    dataGoodBuffer.intOne = DEFAULT_STRUCT_INT_ONE;
    dataGoodBuffer.intTwo = DEFAULT_STRUCT_INT_TWO;
    data = &dataGoodBuffer;

    printStructLine((twoIntsStruct *)data);
}

#ifndef OMITBAD

void CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__struct_01_bad()
{
    /* Safety fix: point data to a valid twoIntsStruct instead of an int to prevent type confusion. */
    printInitializedStruct();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    printInitializedStruct();
}

void CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__struct_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__struct_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__struct_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
