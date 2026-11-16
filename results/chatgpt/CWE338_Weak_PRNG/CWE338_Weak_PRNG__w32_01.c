/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE338_Weak_PRNG__w32_01.c
Label Definition File: CWE338_Weak_PRNG__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")
#ifndef OMITBAD
void CWE338_Weak_PRNG__w32_01_bad(void)
{
    int value = rand();
    printIntLine(value);
}
#endif
#ifndef OMITGOOD
static int cryptographicRandomInteger(void)
{
    HCRYPTPROV provider = 0;
    int value;
    BOOL generated;
    if (!CryptAcquireContextW(&provider, 0, 0, PROV_RSA_FULL, 0)) exit(1);
    generated = CryptGenRandom(provider, sizeof(value), (BYTE *)&value);
    CryptReleaseContext(provider, 0);
    if (!generated) exit(1);
    return value;
}
static void good1(void)
{
    printIntLine(cryptographicRandomInteger());
}
void CWE338_Weak_PRNG__w32_01_good(void)
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
    CWE338_Weak_PRNG__w32_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE338_Weak_PRNG__w32_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
