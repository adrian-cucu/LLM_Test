/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE672_Operation_on_Resource_After_Expiration_or_Release__list_int_01.cpp
Label Definition File: CWE672_Operation_on_Resource_After_Expiration_or_Release__list_int.label.xml
Template File: sources-sinks-01.tmpl.cpp
*/
/*
 * @description
 * CWE: 672 Operation on Resource After Expiration or Release
 * BadSource:  Add values to the list, including the number zero
 * GoodSource: Add value to the list that are not zero
 * Sinks:
 *    GoodSink: Iterate through the list without attempting to clear its contents
 *    BadSink : Iterate through the list, but clear the list if it contains a zero
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <wchar.h>
#include <list>
#include <iostream>

using namespace std;

namespace CWE672_Operation_on_Resource_After_Expiration_or_Release__list_int_01
{

static const int FIRST_VALUE = 100;
static const int SECOND_GOOD_VALUE = 200;
static const int ZERO_VALUE = 0;

static void printAndClearOnZero(list<int> &data)
{
    cout << "The list contains: ";
    for (list<int>::iterator it = data.begin(); it != data.end(); ++it)
    {
        if (*it == ZERO_VALUE)
        {
            /* Safety fix: break out of the loop after clearing the list to avoid dereferencing an invalidated iterator. */
            data.clear();
            break;
        }
        cout << " " << *it;
    }
    cout << endl;
}

static void printList(const list<int> &data)
{
    cout << "The list contains: ";
    for (list<int>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        cout << " " << *it;
    }
    cout << endl;
}

#ifndef OMITBAD

void bad()
{
    list<int> data;
    data.push_back(FIRST_VALUE);
    data.push_back(ZERO_VALUE);
    printAndClearOnZero(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B()
{
    list<int> data;
    data.push_back(FIRST_VALUE);
    data.push_back(SECOND_GOOD_VALUE);
    printAndClearOnZero(data);
}

static void goodB2G()
{
    list<int> data;
    data.push_back(FIRST_VALUE);
    data.push_back(ZERO_VALUE);
    printList(data);
}

void good()
{
    goodG2B();
    goodB2G();
}

#endif /* OMITGOOD */

} /* close namespace */

#ifdef INCLUDEMAIN

using namespace CWE672_Operation_on_Resource_After_Expiration_or_Release__list_int_01;

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
