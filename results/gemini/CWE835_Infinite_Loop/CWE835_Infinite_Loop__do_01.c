/*
 * @description Infinite Loop - do..while()
 *
 * */

#include "std_testcase.h"

#define LOOP_MODULUS 256
#define LOOP_LIMIT 10

static void print_bounded_sequence(int limit)
{
    int i = 0;

    do
    {
        /* Safety fix: enforce a termination condition to prevent an infinite loop */
        if (i == limit)
        {
            break;
        }
        printIntLine(i);
        i = (i + 1) % LOOP_MODULUS;
    }
    while (i >= 0);
}

#ifndef OMITBAD

void CWE835_Infinite_Loop__do_01_bad()
{
    print_bounded_sequence(LOOP_LIMIT);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    print_bounded_sequence(LOOP_LIMIT);
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
