/*
 * @description Return of local buffer address to local buffer
 *
 */

#include "std_testcase.h"

#ifndef OMITBAD

static const char *helperBad(void)
{
    /* Safety fix: use static storage instead of returning a stack-allocated buffer address. */
    static const char charString[] = "helperBad string";
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

static void good1(void)
{
    printLine(helperGood1());
}

void CWE562_Return_of_Stack_Variable_Address__return_buf_01_good()
{
    good1();
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
