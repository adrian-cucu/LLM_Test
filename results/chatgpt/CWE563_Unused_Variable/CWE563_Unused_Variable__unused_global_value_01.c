/*
 * @description Unused global value
 * 
 * */

#include "std_testcase.h"

#ifndef OMITBAD

int CWE563_Unused_Variable__unused_global_value_01_badGlobal = 0;

void CWE563_Unused_Variable__unused_global_value_01_bad() 
{
    enum { PRINTED_GLOBAL_VALUE = 10 };
    CWE563_Unused_Variable__unused_global_value_01_badGlobal = PRINTED_GLOBAL_VALUE;
    printIntLine(CWE563_Unused_Variable__unused_global_value_01_badGlobal);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

int CWE563_Unused_Variable__unused_global_value_01_globalGood1 = 5;

void CWE563_Unused_Variable__unused_global_value_01_good() 
{
    printIntLine(CWE563_Unused_Variable__unused_global_value_01_globalGood1);
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on 
 *  its own for testing or for building a binary to use in testing binary 
 *  analysis tools. It is not used when compiling all the testcases as one 
 *  application, which is how source code analysis tools are tested. 
 */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[]) 
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE563_Unused_Variable__unused_global_value_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE563_Unused_Variable__unused_global_value_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
} 

#endif