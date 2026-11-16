/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01.c
Label Definition File: CWE325_Missing_Required_Cryptographic_Step__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 325 Missing Required Cryptographic Step
 * Sinks: CryptCreateHash
 *    GoodSink: All required cryptographic steps are present
 *    BadSink : Missing call to CryptCreateHash()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>

#pragma comment(lib, "advapi32")

#define HASH_INPUT "ABCDEFG123456" /* INCIDENTAL: Hardcoded crypto */
#define PAYLOAD "plaintext"
#define PAYLOAD_BUFFER_SIZE 100

static void encryptPayload(void)
{
    BYTE payload[PAYLOAD_BUFFER_SIZE];
    DWORD payloadLen = (DWORD)strlen(PAYLOAD);
    HCRYPTPROV hCryptProv = (HCRYPTPROV)NULL;
    HCRYPTHASH hHash = (HCRYPTHASH)NULL;
    HCRYPTKEY hKey = (HCRYPTKEY)NULL;
    char hashData[PAYLOAD_BUFFER_SIZE] = HASH_INPUT;

    memset(payload, 0, sizeof(payload));
    if (payloadLen > sizeof(payload))
    {
        return;
    }

    do
    {
        memcpy(payload, PAYLOAD, payloadLen);

        if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
        {
            break;
        }
        /* Safety fix: create hash handle via CryptCreateHash() before CryptHashData() */
        if (!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash))
        {
            break;
        }
        if (!CryptHashData(hHash, (BYTE *)hashData, (DWORD)strlen(hashData), 0))
        {
            break;
        }
        if (!CryptDeriveKey(hCryptProv, CALG_AES_256, hHash, 0, &hKey))
        {
            break;
        }
        if (!CryptEncrypt(hKey, 0, 1, 0, payload, &payloadLen, sizeof(payload)))
        {
            break;
        }
    }
    while (0);

    SecureZeroMemory(hashData, sizeof(hashData));

    if (hKey)
    {
        CryptDestroyKey(hKey);
    }
    if (hHash)
    {
        CryptDestroyHash(hHash);
    }
    if (hCryptProv)
    {
        CryptReleaseContext(hCryptProv, 0);
    }

    printBytesLine(payload, payloadLen);
}

#ifndef OMITBAD

void CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_bad()
{
    encryptPayload();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    encryptPayload();
}

void CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_good()
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
    CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
