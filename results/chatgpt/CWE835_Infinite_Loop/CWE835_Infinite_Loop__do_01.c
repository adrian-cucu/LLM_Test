/*
 * @description Infinite Loop - do..while()
 * 
 * */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE835_Infinite_Loop__do_01_bad() 
{
    int i = 0;
    
    /* This entry point intentionally emits a repeating 0..255 sequence. */
    do
    {
        printIntLine(i);
        i = i == 255 ? 0 : i + 1;
    } while(i >= 0);
}

#endif /* OMITBAD */


#ifndef OMITGOOD

static void good1() 
{
    int i = 0;

    do
    {
        printIntLine(i);
        ++i;
    } while (i < 10);
}

void CWE835_Infinite_Loop__do_01_good() 
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
    CWE835_Infinite_Loop__do_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE835_Infinite_Loop__do_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
} 

#endif
