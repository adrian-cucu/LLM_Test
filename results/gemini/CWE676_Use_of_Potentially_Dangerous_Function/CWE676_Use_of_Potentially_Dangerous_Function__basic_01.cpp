/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE676_Use_of_Potentially_Dangerous_Function__basic_01.cpp
Label Definition File: CWE676_Use_of_Potentially_Dangerous_Function__basic.label.xml
Template File: point-flaw-01.tmpl.cpp
*/
/*
 * @description
 * CWE: 676 Use of Potentially Dangerous Function
 * Sinks:
 *    GoodSink: Use cin after specifying the length of the input
 *    BadSink : Use cin without specifying the length of the input
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <iostream>

using namespace std;

#define CHAR_BUFFER_SIZE 10

namespace CWE676_Use_of_Potentially_Dangerous_Function__basic_01
{

static void readAndPrintBoundedInput()
{
    char charBuffer[CHAR_BUFFER_SIZE] = {0};

    /* Safety fix: set cin.width(CHAR_BUFFER_SIZE) to prevent unbounded extraction buffer overflow. */
    cin.width(CHAR_BUFFER_SIZE);
    cin >> charBuffer;
    charBuffer[CHAR_BUFFER_SIZE - 1] = '\0';
    printLine(charBuffer);
}

#ifndef OMITBAD

void bad()
{
    readAndPrintBoundedInput();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    readAndPrintBoundedInput();
}

void good()
{
    good1();
}

#endif /* OMITGOOD */

} /* close namespace */

#ifdef INCLUDEMAIN

using namespace CWE676_Use_of_Potentially_Dangerous_Function__basic_01;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
