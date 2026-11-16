/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01.c
Label Definition File: CWE325_Missing_Required_Cryptographic_Step__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32")
#define HASH_INPUT "ABCDEFG123456" /* Original testcase key material. */
#define PAYLOAD "plaintext"
static void processPayload(int createHash)
{
    /* Zero unused capacity so an error cannot expose uninitialized bytes. */
    BYTE payload[100] = {0};
    DWORD length = (DWORD)strlen(PAYLOAD);
    HCRYPTPROV provider = 0;
    HCRYPTHASH hash = 0;
    HCRYPTKEY key = 0;
    char hashData[] = HASH_INPUT;
    memcpy(payload, PAYLOAD, length);
    do
    {
        if (!CryptAcquireContext(&provider, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0)) break;
        /* The bad variant intentionally retains its missing hash-creation step. */
        if (createHash && !CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash)) break;
        if (!CryptHashData(hash, (BYTE *)hashData, (DWORD)strlen(hashData), 0)) break;
        if (!CryptDeriveKey(provider, CALG_AES_256, hash, 0, &key)) break;
        if (!CryptEncrypt(key, 0, 1, 0, payload, &length, sizeof(payload)))
        {
            break;
        }
    } while (0);
    if (key) CryptDestroyKey(key);
    if (hash) CryptDestroyHash(hash);
    if (provider) CryptReleaseContext(provider, 0);
    /* Failed APIs can report the required size instead of bytes actually held. */
    if (length <= sizeof(payload)) printBytesLine(payload, length);
}
#ifndef OMITBAD
void CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_bad(void)
{
    processPayload(0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    processPayload(1);
}
void CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_good(void)
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
    CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE325_Missing_Required_Cryptographic_Step__w32_CryptCreateHash_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
