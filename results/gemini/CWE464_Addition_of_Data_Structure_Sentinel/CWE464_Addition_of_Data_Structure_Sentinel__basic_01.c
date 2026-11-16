/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE464_Addition_of_Data_Structure_Sentinel__basic_01.c
Label Definition File: CWE464_Addition_of_Data_Structure_Sentinel__basic.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 464 Addition of Data Structure Sentinel
 * BadSource:  Read in data from the console and convert to an int
 * GoodSource: Set data to a fixed char
 * Sink:
 *    BadSink : Place data into and print an array
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#define SINK_ARRAY_SIZE 4
#define DEFAULT_CHAR 'a'

static void printSinkArray(char middleChar)
{
    char charArraySink[SINK_ARRAY_SIZE];

    charArraySink[0] = 'x';
    /* Safety fix: Guard against NUL sentinel injection in the middle of the string */
    charArraySink[1] = (middleChar != '\0') ? middleChar : DEFAULT_CHAR;
    charArraySink[2] = 'z';
    charArraySink[3] = '\0';
    printLine(charArraySink);
}

#ifndef OMITBAD

void CWE464_Addition_of_Data_Structure_Sentinel__basic_01_bad()
{
    char data = DEFAULT_CHAR;
    int inputChar = getc(stdin);

    if (inputChar != EOF)
    {
        char charArraySource[2];
        charArraySource[0] = (char)inputChar;
        charArraySource[1] = '\0';
        data = (char)atoi(charArraySource);
    }

    printSinkArray(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char data = DEFAULT_CHAR;

    printSinkArray(data);
}

void CWE464_Addition_of_Data_Structure_Sentinel__basic_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;

    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE464_Addition_of_Data_Structure_Sentinel__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE464_Addition_of_Data_Structure_Sentinel__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
