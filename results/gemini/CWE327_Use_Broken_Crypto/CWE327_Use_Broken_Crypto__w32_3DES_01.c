/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE327_Use_Broken_Crypto__w32_3DES_01.c
Label Definition File: CWE327_Use_Broken_Crypto__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 327 Use of a Broken or Risky Cryptographic Algorithm
 * Sinks: 3DES
 *    GoodSink: Use AES for decryption
 *    BadSink : Use Triple DES for decryption
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>

/* Link with the Advapi32.lib file for Crypt* functions */
#pragma comment (lib, "Advapi32")

#define BUFFER_SIZE 100
#define ENCRYPTED_FILE "encrypted.txt"

static size_t readPasswordFromStdin(char *password, size_t bufferSize)
{
    size_t passwordLen = 0;

    printLine("Enter the password: ");
    if (fgets(password, (int)bufferSize, stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
        return 0;
    }

    passwordLen = strlen(password);
    if (passwordLen > 0 && password[passwordLen - 1] == '\n')
    {
        password[passwordLen - 1] = '\0';
        passwordLen--;
    }
    return passwordLen;
}

static void decryptFileWithAes(void)
{
    FILE *pFile = NULL;
    HCRYPTPROV hCryptProv = 0;
    HCRYPTKEY hKey = 0;
    HCRYPTHASH hHash = 0;
    char password[BUFFER_SIZE] = "";
    size_t passwordLen = 0;
    char toBeDecrypted[BUFFER_SIZE];
    DWORD toBeDecryptedLen = (DWORD)(sizeof(toBeDecrypted) - 1);
    int failed = 0;

    memset(toBeDecrypted, 0, sizeof(toBeDecrypted));
    passwordLen = readPasswordFromStdin(password, sizeof(password));

    pFile = fopen(ENCRYPTED_FILE, "rb");
    if (pFile == NULL)
    {
        SecureZeroMemory(password, sizeof(password));
        exit(1);
    }

    if (fread(toBeDecrypted, sizeof(char), BUFFER_SIZE, pFile) != BUFFER_SIZE)
    {
        fclose(pFile);
        SecureZeroMemory(password, sizeof(password));
        exit(1);
    }
    fclose(pFile);
    pFile = NULL;
    toBeDecrypted[BUFFER_SIZE - 1] = '\0';

    if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
    {
        if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
        {
            printLine("Error in acquiring cryptographic context");
            SecureZeroMemory(password, sizeof(password));
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
        if (!CryptHashData(hHash, (BYTE *)password, (DWORD)passwordLen, 0))
        {
            printLine("Error in hashing password");
            failed = 1;
            break;
        }
        /* Safety fix: use AES-256 instead of broken Triple DES (CALG_3DES) */
        if (!CryptDeriveKey(hCryptProv, CALG_AES_256, hHash, 0, &hKey))
        {
            printLine("Error in CryptDeriveKey");
            failed = 1;
            break;
        }
        if (!CryptDecrypt(hKey, 0, 1, 0, (BYTE *)toBeDecrypted, &toBeDecryptedLen))
        {
            printLine("Error in decryption");
            failed = 1;
            break;
        }
    }
    while (0);

    SecureZeroMemory(password, sizeof(password));

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

    /* Safety fix: clamp NUL terminator index within toBeDecrypted bounds */
    if (toBeDecryptedLen >= sizeof(toBeDecrypted))
    {
        toBeDecryptedLen = (DWORD)(sizeof(toBeDecrypted) - 1);
    }
    toBeDecrypted[toBeDecryptedLen] = '\0';
    printLine(toBeDecrypted);
}

#ifndef OMITBAD

void CWE327_Use_Broken_Crypto__w32_3DES_01_bad()
{
    decryptFileWithAes();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    decryptFileWithAes();
}

void CWE327_Use_Broken_Crypto__w32_3DES_01_good()
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
    CWE327_Use_Broken_Crypto__w32_3DES_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE327_Use_Broken_Crypto__w32_3DES_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
