/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE843_Type_Confusion__char_01.c
Label Definition File: CWE843_Type_Confusion.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 843 Type Confusion
 * BadSource: char Point data to a char data type
 * GoodSource: Point data to an int data type
 * Sink:
 *    BadSink : Attempt to access data as an int
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define DEFAULT_INT_VALUE 8

static void print_int_from_void_ptr(const void *data)
{
    if (data != NULL)
    {
        printIntLine(*((const int *)data));
    }
}

#ifndef OMITBAD

void CWE843_Type_Confusion__char_01_bad()
{
    /* Safety fix: point data to an int in-scope rather than a block-scoped char to avoid type confusion and dangling pointer */
    int intBuffer = (int)'a';
    void *data = &intBuffer;
    print_int_from_void_ptr(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    /* Safety fix: keep intBuffer in scope across the dereference */
    int intBuffer = DEFAULT_INT_VALUE;
    void *data = &intBuffer;
    print_int_from_void_ptr(data);
}

void CWE843_Type_Confusion__char_01_good()
{
    goodG2B();
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
    CWE843_Type_Confusion__char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE843_Type_Confusion__char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
