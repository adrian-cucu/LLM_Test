/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE328_Reversible_One_Way_Hash__w32_MD2_01.c
Label Definition File: CWE328_Reversible_One_Way_Hash__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")
#define PASSWORD_INPUT_SIZE 128
#define SHA512_SUM_SIZE (512 / 8)
#define MD2_SUM_SIZE (128 / 8)

static void verifyPassword(ALG_ID algorithm, DWORD digestLength)
{
    HCRYPTPROV provider = 0;
    HCRYPTHASH hash = 0;
    FILE *file = fopen("password.txt", "r");
    char password[PASSWORD_INPUT_SIZE] = "";
    UCHAR savedHash[SHA512_SUM_SIZE];
    UCHAR calculatedHash[SHA512_SUM_SIZE];
    DWORD hashSize = digestLength;
    int succeeded = 0;
    do
    {
        size_t i;
        if (file == NULL) break;
        for (i = 0; i < digestLength; ++i)
        {
            /* %x requires unsigned int *, not ULONG * even on 32-bit Windows. */
            unsigned int value;
            if (fscanf(file, "%02x", &value) != 1 || value > 0xff) break;
            savedHash[i] = (UCHAR)value;
        }
        if (i != digestLength) break;
        fclose(file);
        file = NULL;
        if (fgets(password, sizeof(password), stdin) == NULL) break;
        password[strcspn(password, "\r\n")] = '\0';
        if (!CryptAcquireContextW(&provider, 0, 0, PROV_RSA_FULL, 0)) break;
        if (!CryptCreateHash(provider, algorithm, 0, 0, &hash)) break;
        if (!CryptHashData(hash, (BYTE *)password, (DWORD)strlen(password), 0)) break;
        if (!CryptGetHashParam(hash, HP_HASHVAL, calculatedHash, &hashSize, 0)) break;
        /* Only compare initialized bytes of the requested digest. */
        if (hashSize != digestLength) break;
        if (memcmp(savedHash, calculatedHash, digestLength) == 0)
            printLine("Access granted");
        else
            printLine("Access denied");
        succeeded = 1;
    } while (0);
    if (file != NULL) fclose(file);
    if (hash) CryptDestroyHash(hash);
    if (provider) CryptReleaseContext(provider, 0);
    SecureZeroMemory(password, sizeof(password));
    if (!succeeded) exit(1);
}
#ifndef OMITBAD
void CWE328_Reversible_One_Way_Hash__w32_MD2_01_bad(void)
{
    verifyPassword(CALG_MD2, MD2_SUM_SIZE);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    verifyPassword(CALG_SHA_512, SHA512_SUM_SIZE);
}
void CWE328_Reversible_One_Way_Hash__w32_MD2_01_good(void)
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
    CWE328_Reversible_One_Way_Hash__w32_MD2_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE328_Reversible_One_Way_Hash__w32_MD2_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
