/*
 * @description Return of local buffer address to local buffer
 * 
 * */

#include "std_testcase.h"

/* this REQUIRES secondary functions */

#ifndef OMITBAD

static const char *helperBad(void)
{
    static const char charString[] = "helperBad string";

    /* Static storage keeps the returned string alive after this call. */
    return charString;
}

void CWE562_Return_of_Stack_Variable_Address__return_buf_01_bad() 
{
    printLine(helperBad());
}

#endif /* OMITBAD */


#ifndef OMITGOOD

static const char *helperGood1(void)
{
    static const char charString[] = "helperGood1 string";

    return charString;
}

static void good1() 
{
    printLine(helperGood1());
}

void CWE562_Return_of_Stack_Variable_Address__return_buf_01_good() 
{
    good1();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on 
 * its own for testing or for building a binary to use in testing binary 
 * analysis tools. It is not used when compiling all the testcases as one 
 * application, which is how source code analysis tools are tested. 
 */ 

#ifdef INCLUDEMAIN

int main(int argc, char * argv[]) 
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE562_Return_of_Stack_Variable_Address__return_buf_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE562_Return_of_Stack_Variable_Address__return_buf_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
} 

#endif
