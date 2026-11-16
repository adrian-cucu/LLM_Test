/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE338_Weak_PRNG__w32_01.c
Label Definition File: CWE338_Weak_PRNG__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 338 Use of Cryptographically Weak PRNG
 * Sinks:
 *    GoodSink: Use CryptGenRandom() to generate a random number
 *    BadSink : Use rand() to generate a random number
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")

static void printCryptoRandomInt(void)
{
    HCRYPTPROV hCryptProv = 0;
    int data = 0;

    if (!CryptAcquireContextW(&hCryptProv, 0, 0, PROV_RSA_FULL, 0))
    {
        exit(1);
    }

    /* Safety fix: use CryptGenRandom() instead of cryptographically weak rand() */
    if (!CryptGenRandom(hCryptProv, sizeof(data), (BYTE *)&data))
    {
        CryptReleaseContext(hCryptProv, 0);
        exit(1);
    }

    CryptReleaseContext(hCryptProv, 0);
    printIntLine(data);
}

#ifndef OMITBAD

void CWE338_Weak_PRNG__w32_01_bad()
{
    printCryptoRandomInt();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    printCryptoRandomInt();
}

void CWE338_Weak_PRNG__w32_01_good()
{
    good1();
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
    CWE338_Weak_PRNG__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE338_Weak_PRNG__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
