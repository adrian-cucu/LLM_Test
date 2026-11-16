/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE256_Plaintext_Storage_of_Password__w32_char_01.c
Label Definition File: CWE256_Plaintext_Storage_of_Password__w32.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 256 Plaintext Storage of Password
 * BadSource:  Read the password from a file
 * GoodSource: Read the password from a file and decrypt it
 * Sinks:
 *    GoodSink: Decrypt the password then authenticate the user using LogonUserA()
 *    BadSink : Authenticate the user using LogonUserA()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32")
#pragma comment(lib, "crypt32.lib")

#define HASH_INPUT "ABCDEFG123456" /* INCIDENTAL: Hardcoded crypto */
#define PASSWORD_BUFFER_SIZE 100
#define PASSWORD_FILE "passwords.txt"
#define DEFAULT_USERNAME "User"
#define DEFAULT_DOMAIN "Domain"

static void readPasswordFromFile(char *buffer, size_t bufferSize)
{
    FILE *pFile = fopen(PASSWORD_FILE, "r");
    buffer[0] = '\0';
    if (pFile != NULL)
    {
        if (fgets(buffer, (int)bufferSize, pFile) == NULL)
        {
            buffer[0] = '\0';
        }
        fclose(pFile);
    }
}

static void decryptHexPassword(char *password, size_t bufferSize)
{
    HCRYPTPROV hCryptProv = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hKey = 0;
    char hashData[PASSWORD_BUFFER_SIZE] = HASH_INPUT;
    BYTE payload[(PASSWORD_BUFFER_SIZE - 1) * sizeof(char)];
    DWORD payloadBytes = 0;

    memset(payload, 0, sizeof(payload));
    payloadBytes = decodeHexChars(payload, sizeof(payload), password);
    SecureZeroMemory(password, bufferSize * sizeof(char));

    do
    {
        if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
        {
            break;
        }
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
        if (!CryptDecrypt(hKey, 0, 1, 0, payload, &payloadBytes))
        {
            break;
        }
        /* Safety fix: ensure decrypted payload fits in password buffer before NUL-termination */
        if (payloadBytes >= bufferSize)
        {
            break;
        }
        memcpy(password, payload, payloadBytes);
        password[payloadBytes / sizeof(char)] = '\0';
    }
    while (0);

    SecureZeroMemory(payload, sizeof(payload));
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
}

static void authenticateUser(const char *username, const char *domain, const char *password)
{
    HANDLE pHandle = NULL;
    if (LogonUserA(
                username,
                domain,
                password,
                LOGON32_LOGON_NETWORK,
                LOGON32_PROVIDER_DEFAULT,
                &pHandle) != 0)
    {
        printLine("User logged in successfully.");
        CloseHandle(pHandle);
    }
    else
    {
        printLine("Unable to login.");
    }
}

#ifndef OMITBAD

void CWE256_Plaintext_Storage_of_Password__w32_char_01_bad()
{
    char dataBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readPasswordFromFile(data, sizeof(dataBuffer));
    /* Safety fix: decrypt stored password before passing to LogonUserA() */
    decryptHexPassword(data, sizeof(dataBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, data);
    SecureZeroMemory(dataBuffer, sizeof(dataBuffer));
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B(void)
{
    char dataBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readPasswordFromFile(data, sizeof(dataBuffer));
    decryptHexPassword(data, sizeof(dataBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, data);
    SecureZeroMemory(dataBuffer, sizeof(dataBuffer));
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G(void)
{
    char dataBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readPasswordFromFile(data, sizeof(dataBuffer));
    decryptHexPassword(data, sizeof(dataBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, data);
    SecureZeroMemory(dataBuffer, sizeof(dataBuffer));
}

void CWE256_Plaintext_Storage_of_Password__w32_char_01_good()
{
    goodG2B();
    goodB2G();
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
    CWE256_Plaintext_Storage_of_Password__w32_char_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE256_Plaintext_Storage_of_Password__w32_char_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
