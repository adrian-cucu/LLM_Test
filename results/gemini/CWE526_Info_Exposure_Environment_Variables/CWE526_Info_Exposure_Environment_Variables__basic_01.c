/*
 * @description
 * CWE: 526 Information Exposure Through Environment Variables
 * Sinks:
 *    GoodSink: Print a generic error message to the console
 *    BadSink : Expose the contents of an environment variable to the console
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

static void printGenericStatus(void)
{
    /* Safety fix: do not expose environment variable contents; print generic message */
    printLine("Not in path");
}

#ifndef OMITBAD

void CWE526_Info_Exposure_Environment_Variables__basic_01_bad()
{
    printGenericStatus();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    printGenericStatus();
}

void CWE526_Info_Exposure_Environment_Variables__basic_01_good()
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
    CWE526_Info_Exposure_Environment_Variables__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE526_Info_Exposure_Environment_Variables__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
