/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE511_Logic_Time_Bomb__counter_01.c
Label Definition File: CWE511_Logic_Time_Bomb.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <limits.h>
#ifdef _WIN32
#define UNLINK _unlink
#else
#include <unistd.h>
#define UNLINK unlink
#endif
#define COUNT_CHECK 20000

static void runCounter(int deleteFile)
{
    int count = 0;
    for (;;)
    {
        if (count == COUNT_CHECK)
        {
            if (deleteFile)
            {
                UNLINK("important_file.txt");
            }
            else
            {
                printLine("Happy New Year!");
            }
        }
        /* Saturate to avoid signed overflow while keeping the loop infinite
         * and the action a one-time event. */
        if (count < INT_MAX) { ++count; }
    }
}
#ifndef OMITBAD
void CWE511_Logic_Time_Bomb__counter_01_bad()
{
    runCounter(1);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    runCounter(0);
}
void CWE511_Logic_Time_Bomb__counter_01_good()
{
    good1();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE511_Logic_Time_Bomb__counter_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE511_Logic_Time_Bomb__counter_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
