/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE327_Use_Broken_Crypto__w32_3DES_01.c
Label Definition File: CWE327_Use_Broken_Crypto__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "Advapi32")
static void decryptAndPrint(ALG_ID algorithm)
{
    FILE *file = NULL;
    HCRYPTPROV provider = 0;
    HCRYPTKEY key = 0;
    HCRYPTHASH hash = 0;
    char password[100];
    size_t passwordLength;
    char payload[100];
    DWORD length = sizeof(payload) - 1;
    const char *error = NULL;
    int succeeded = 0;
    printLine("Enter the password: ");
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        printLine("fgets() failed");
        password[0] = '\0';
    }
    passwordLength = strlen(password);
    /* Preserve both the original trimming and the original hashed byte count. */
    if (passwordLength > 0) password[passwordLength - 1] = '\0';
    do
    {
        file = fopen("encrypted.txt", "rb");
        if (file == NULL) break;
        if (fread(payload, sizeof(char), sizeof(payload), file) != sizeof(payload)) break;
        payload[sizeof(payload) - 1] = '\0';
        if (!CryptAcquireContext(&provider, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0) &&
            !CryptAcquireContext(&provider, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
        {
            error = "Error in acquiring cryptographic context";
            break;
        }
        if (!CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash))
        {
            error = "Error in creating hash";
            break;
        }
        if (!CryptHashData(hash, (BYTE *)password, (DWORD)passwordLength, 0))
        {
            error = "Error in hashing password";
            break;
        }
        if (!CryptDeriveKey(provider, algorithm, hash, 0, &key))
        {
            error = "Error in CryptDeriveKey";
            break;
        }
        if (!CryptDecrypt(key, 0, 1, 0, (BYTE *)payload, &length) ||
            length >= sizeof(payload))
        {
            error = "Error in decryption";
            break;
        }
        payload[length] = '\0';
        printLine(payload);
        succeeded = 1;
    } while (0);
    /* All error paths release any resources already acquired. */
    if (key) CryptDestroyKey(key);
    if (hash) CryptDestroyHash(hash);
    if (provider) CryptReleaseContext(provider, 0);
    if (file != NULL) fclose(file);
    SecureZeroMemory(password, sizeof(password));
    SecureZeroMemory(payload, sizeof(payload));
    if (!succeeded)
    {
        if (error != NULL) printLine(error);
        exit(1);
    }
}
#ifndef OMITBAD
void CWE327_Use_Broken_Crypto__w32_3DES_01_bad(void)
{
    decryptAndPrint(CALG_3DES);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    decryptAndPrint(CALG_AES_256);
}
void CWE327_Use_Broken_Crypto__w32_3DES_01_good(void)
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
    CWE327_Use_Broken_Crypto__w32_3DES_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE327_Use_Broken_Crypto__w32_3DES_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
