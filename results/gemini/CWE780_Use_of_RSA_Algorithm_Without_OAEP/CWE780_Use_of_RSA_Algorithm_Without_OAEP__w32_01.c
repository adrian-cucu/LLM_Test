/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE780_Use_of_RSA_Algorithm_Without_OAEP__w32_01.c
Label Definition File: CWE780_Use_of_RSA_Algorithm_Without_OAEP__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 780 Use of RSA Algorithm Without OAEP
 * Sinks:
 *    GoodSink: Use RSA with OAEP
 *    BadSink : Use RSA without OAEP
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>

/* Link with the Advapi32.lib file for Crypt* functions */
#pragma comment (lib, "Advapi32")
#define HASH_INPUT "ABCDEFG123456" /* INCIDENTAL: Hardcoded crypto */
#define PAYLOAD "String to be encrypted"
#define PAYLOAD_BUFFER_SIZE 200

static void encrypt_payload_with_rsa(DWORD encryptFlags)
{
    BYTE payload[PAYLOAD_BUFFER_SIZE] = {0};
    DWORD payloadLen = (DWORD)strlen(PAYLOAD);
    HCRYPTPROV hCryptProv = (HCRYPTPROV)NULL;
    HCRYPTHASH hHash = (HCRYPTHASH)NULL;
    HCRYPTKEY hKey = (HCRYPTKEY)NULL;

    do
    {
        if (payloadLen >= sizeof(payload))
        {
            printLine("Payload too large");
            exit(1);
        }
        memcpy(payload, PAYLOAD, payloadLen);

        if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
        {
            if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
            {
                printLine("Error in acquiring cryptographic context");
                exit(1);
            }
        }
        if (!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash))
        {
            printLine("Error in creating hash");
            exit(1);
        }
        if (!CryptHashData(hHash, (BYTE *)HASH_INPUT, (DWORD)(strlen(HASH_INPUT) * sizeof(char)), 0))
        {
            printLine("Error in hashing HASH_INPUT");
            exit(1);
        }
        if (!CryptDeriveKey(hCryptProv, CALG_RSA_SIGN, hHash, 0, &hKey))
        {
            printLine("Error in CryptDeriveKey");
            exit(1);
        }
        if (!CryptEncrypt(hKey, (HCRYPTHASH)NULL, 1, encryptFlags, payload, &payloadLen, sizeof(payload)))
        {
            printLine("Error in CryptEncryptData");
            exit(1);
        }
    }
    while (0);

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

void CWE780_Use_of_RSA_Algorithm_Without_OAEP__w32_01_bad()
{
    /* Safety fix: use CRYPT_OAEP padding instead of 0 for RSA encryption */
    encrypt_payload_with_rsa(CRYPT_OAEP);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    encrypt_payload_with_rsa(CRYPT_OAEP);
}

void CWE780_Use_of_RSA_Algorithm_Without_OAEP__w32_01_good()
{
    good1();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE780_Use_of_RSA_Algorithm_Without_OAEP__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE780_Use_of_RSA_Algorithm_Without_OAEP__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
