/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE321_Hard_Coded_Cryptographic_Key__w32_char_01.c
Label Definition File: CWE321_Hard_Coded_Cryptographic_Key__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 321 Use of Hard-coded Cryptographic Key
 * BadSource:  Copy a hardcoded value into cryptoKey
 * GoodSource: Read cryptoKey from the console
 * Sink:
 *    BadSink : Hash cryptoKey and use the value to encrypt a string
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>

/* Link with the Advapi32.lib file for Crypt* functions */
#pragma comment (lib, "Advapi32")

#define KEY_BUFFER_SIZE 100
#define ENCRYPTED_BUFFER_SIZE 200
#define PLAINTEXT_SAMPLE "String to be encrypted"

static void readCryptoKeyFromStdin(char *cryptoKey, size_t bufferSize)
{
    size_t cryptoKeyLen = strlen(cryptoKey);

    if (bufferSize <= cryptoKeyLen + 1)
    {
        return;
    }

    if (fgets(cryptoKey + cryptoKeyLen, (int)(bufferSize - cryptoKeyLen), stdin) == NULL)
    {
        printLine("fgets() failed");
        cryptoKey[cryptoKeyLen] = '\0';
        return;
    }

    cryptoKeyLen = strlen(cryptoKey);
    if (cryptoKeyLen > 0 && cryptoKey[cryptoKeyLen - 1] == '\n')
    {
        cryptoKey[cryptoKeyLen - 1] = '\0';
    }
}

static void encryptSampleWithKey(const char *cryptoKey)
{
    HCRYPTPROV hCryptProv = 0;
    HCRYPTKEY hKey = 0;
    HCRYPTHASH hHash = 0;
    char toBeEncrypted[] = PLAINTEXT_SAMPLE;
    DWORD encryptedLen = (DWORD)(strlen(toBeEncrypted) * sizeof(char));
    BYTE encrypted[ENCRYPTED_BUFFER_SIZE];
    int failed = 0;

    memset(encrypted, 0, sizeof(encrypted));
    memcpy(encrypted, toBeEncrypted, encryptedLen);

    if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_AES, 0))
    {
        if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
        {
            printLine("Error in acquiring cryptographic context");
            exit(1);
        }
    }

    do
    {
        if (!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash))
        {
            printLine("Error in creating hash");
            failed = 1;
            break;
        }
        if (!CryptHashData(hHash, (BYTE *)cryptoKey, (DWORD)(strlen(cryptoKey) * sizeof(char)), 0))
        {
            printLine("Error in hashing cryptoKey");
            failed = 1;
            break;
        }
        if (!CryptDeriveKey(hCryptProv, CALG_AES_256, hHash, 0, &hKey))
        {
            printLine("Error in CryptDeriveKey");
            failed = 1;
            break;
        }
        if (!CryptEncrypt(hKey, (HCRYPTHASH)NULL, 1, 0, encrypted, &encryptedLen, sizeof(encrypted)))
        {
            printLine("Error in CryptEncrypt");
            failed = 1;
            break;
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

    if (failed)
    {
        exit(1);
    }

    printBytesLine(encrypted, encryptedLen);
}

#ifndef OMITBAD

void CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_bad()
{
    char cryptoKeyBuffer[KEY_BUFFER_SIZE] = "";
    char *cryptoKey = cryptoKeyBuffer;

    /* Safety fix: obtain cryptographic key from stdin instead of using a hardcoded key */
    readCryptoKeyFromStdin(cryptoKey, sizeof(cryptoKeyBuffer));
    encryptSampleWithKey(cryptoKey);
    SecureZeroMemory(cryptoKeyBuffer, sizeof(cryptoKeyBuffer));
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B(void)
{
    char cryptoKeyBuffer[KEY_BUFFER_SIZE] = "";
    char *cryptoKey = cryptoKeyBuffer;

    readCryptoKeyFromStdin(cryptoKey, sizeof(cryptoKeyBuffer));
    encryptSampleWithKey(cryptoKey);
    SecureZeroMemory(cryptoKeyBuffer, sizeof(cryptoKeyBuffer));
}

void CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_good()
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
    CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
