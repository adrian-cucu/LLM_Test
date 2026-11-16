/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE321_Hard_Coded_Cryptographic_Key__w32_char_01.c
Label Definition File: CWE321_Hard_Coded_Cryptographic_Key__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#define CRYPTO_KEY "Hardcoded"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "Advapi32")

static void encryptAndPrint(const char *cryptoKey)
{
    HCRYPTPROV provider = 0;
    HCRYPTKEY key = 0;
    HCRYPTHASH hash = 0;
    const char plaintext[] = "String to be encrypted";
    DWORD length = (DWORD)strlen(plaintext);
    BYTE encrypted[200];
    const char *error = NULL;
    memcpy(encrypted, plaintext, length);
    do
    {
        if (!CryptAcquireContext(&provider, NULL, MS_ENHANCED_PROV, PROV_RSA_AES, 0) &&
            !CryptAcquireContext(&provider, NULL, MS_ENHANCED_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
        {
            error = "Error in acquiring cryptographic context";
            break;
        }
        if (!CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash))
        {
            error = "Error in creating hash";
            break;
        }
        if (!CryptHashData(hash, (const BYTE *)cryptoKey, (DWORD)strlen(cryptoKey), 0))
        {
            error = "Error in hashing cryptoKey";
            break;
        }
        if (!CryptDeriveKey(provider, CALG_AES_256, hash, 0, &key))
        {
            error = "Error in CryptDeriveKey";
            break;
        }
        if (!CryptEncrypt(key, 0, 1, 0, encrypted, &length, sizeof(encrypted)))
        {
            error = "Error in CryptEncrypt";
            break;
        }
        printBytesLine(encrypted, length);
    } while (0);
    /* Release partially acquired resources on failures as well as success. */
    if (key) CryptDestroyKey(key);
    if (hash) CryptDestroyHash(hash);
    if (provider) CryptReleaseContext(provider, 0);
    SecureZeroMemory(encrypted, sizeof(encrypted));
    if (error != NULL)
    {
        printLine(error);
        exit(1);
    }
}
#ifndef OMITBAD
void CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_bad(void)
{
    char cryptoKey[100] = CRYPTO_KEY;
    encryptAndPrint(cryptoKey);
    SecureZeroMemory(cryptoKey, sizeof(cryptoKey));
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char cryptoKey[100] = "";
    size_t length;
    if (fgets(cryptoKey, sizeof(cryptoKey), stdin) == NULL)
    {
        printLine("fgets() failed");
        cryptoKey[0] = '\0';
    }
    length = strlen(cryptoKey);
    /* Preserve the original final-character removal before deriving the key. */
    if (length > 0) cryptoKey[length - 1] = '\0';
    encryptAndPrint(cryptoKey);
    SecureZeroMemory(cryptoKey, sizeof(cryptoKey));
}
void CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_good(void)
{
    goodG2B();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE321_Hard_Coded_Cryptographic_Key__w32_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
