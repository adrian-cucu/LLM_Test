/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE242_Use_of_Inherently_Dangerous_Function__basic_01.c
Label Definition File: CWE242_Use_of_Inherently_Dangerous_Function__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#define DEST_SIZE 10
static void inputFailure(void)
{
    printLine("Error Condition: alter control flow to indicate action taken");
    exit(1);
}
#ifndef OMITBAD
void CWE242_Use_of_Inherently_Dangerous_Function__basic_01_bad(void)
{
    char destination[DEST_SIZE];
    size_t length = 0;
    int character;
    /* C11 has no gets. Preserve its newline consumption for fitting lines,
     * rejecting only input that would have overrun the original array. */
    while ((character = getchar()) != '\n' && character != EOF)
    {
        if (length + 1 >= sizeof(destination)) inputFailure();
        destination[length++] = (char)character;
    }
    if (ferror(stdin) || (character == EOF && length == 0)) inputFailure();
    destination[length] = '\0';
    printLine(destination);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    char destination[DEST_SIZE];
    if (fgets(destination, sizeof(destination), stdin) == NULL) inputFailure();
    destination[sizeof(destination) - 1] = '\0';
    printLine(destination);
}
void CWE242_Use_of_Inherently_Dangerous_Function__basic_01_good(void)
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
    CWE242_Use_of_Inherently_Dangerous_Function__basic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE242_Use_of_Inherently_Dangerous_Function__basic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
