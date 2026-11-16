/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE256_Plaintext_Storage_of_Password__w32_char_01.c
Label Definition File: CWE256_Plaintext_Storage_of_Password__w32.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32")
#pragma comment(lib, "crypt32.lib")
#define HASH_INPUT "ABCDEFG123456" /* Original testcase key material. */
enum { PASSWORD_CAPACITY = 100 };

static void readPassword(char *password)
{
    FILE *file = fopen("passwords.txt", "r");
    password[0] = '\0';
    if (file != NULL)
    {
        if (fgets(password, PASSWORD_CAPACITY, file) == NULL) password[0] = '\0';
        fclose(file);
    }
}
static void authenticate(const char *password)
{
    HANDLE user;
    if (LogonUserA("User", "Domain", password, LOGON32_LOGON_NETWORK,
                   LOGON32_PROVIDER_DEFAULT, &user))
    {
        printLine("User logged in successfully.");
        CloseHandle(user);
    }
    else
    {
        printLine("Unable to login.");
    }
}
#ifndef OMITBAD
void CWE256_Plaintext_Storage_of_Password__w32_char_01_bad(void)
{
    char password[PASSWORD_CAPACITY] = "";
    readPassword(password);
    authenticate(password);
    /* Do not leave a plaintext password on the stack after authentication. */
    SecureZeroMemory(password, sizeof(password));
}
#endif
#ifndef OMITGOOD
static void decryptPassword(char *password)
{
    HCRYPTPROV provider = 0;
    HCRYPTHASH hash = 0;
    HCRYPTKEY key = 0;
    char hashData[] = HASH_INPUT;
    BYTE payload[PASSWORD_CAPACITY - 1];
    DWORD length = decodeHexChars(payload, sizeof(payload), password);
    SecureZeroMemory(password, PASSWORD_CAPACITY);
    do
    {
        if (!CryptAcquireContext(&provider, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0)) break;
        if (!CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash)) break;
        if (!CryptHashData(hash, (BYTE *)hashData, (DWORD)strlen(hashData), 0)) break;
        if (!CryptDeriveKey(provider, CALG_AES_256, hash, 0, &key)) break;
        if (!CryptDecrypt(key, 0, 1, 0, payload, &length)) break;
        /* Validate the returned length before copying and terminating. */
        if (length > sizeof(payload)) break;
        memcpy(password, payload, length);
        password[length] = '\0';
    } while (0);
    if (key) CryptDestroyKey(key);
    if (hash) CryptDestroyHash(hash);
    if (provider) CryptReleaseContext(provider, 0);
    SecureZeroMemory(payload, sizeof(payload));
    SecureZeroMemory(hashData, sizeof(hashData));
}
static void encryptedLogin(void)
{
    char password[PASSWORD_CAPACITY] = "";
    readPassword(password);
    decryptPassword(password);
    authenticate(password);
    SecureZeroMemory(password, sizeof(password));
}
static void goodG2B(void)
{
    encryptedLogin();
}
static void goodB2G(void)
{
    encryptedLogin();
}
void CWE256_Plaintext_Storage_of_Password__w32_char_01_good(void)
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE256_Plaintext_Storage_of_Password__w32_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE256_Plaintext_Storage_of_Password__w32_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
