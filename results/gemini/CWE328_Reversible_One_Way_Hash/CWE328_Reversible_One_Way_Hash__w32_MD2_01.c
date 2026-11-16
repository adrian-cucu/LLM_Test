/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE328_Reversible_One_Way_Hash__w32_MD2_01.c
Label Definition File: CWE328_Reversible_One_Way_Hash__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 328 Reversible One Way Hash
 * Sinks: MD2
 *    GoodSink: Use SHA-512 as a hashing algorithm
 *    BadSink : Use MD2 as a hashing algorithm
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")

#define PASSWORD_INPUT_SIZE 128
#define SHA512_SUM_SIZE (512 / 8)
#define PASSWORD_FILE "password.txt"

static void loadSavedHash(const char *filename, UCHAR *savedHash, size_t hashSize)
{
    FILE *pFile = fopen(filename, "r");
    size_t i = 0;

    if (pFile == NULL)
    {
        exit(1);
    }

    for (i = 0; i < hashSize; i++)
    {
        unsigned int val = 0;
        if (fscanf(pFile, "%02x", &val) != 1 || val > 0xffU)
        {
            fclose(pFile);
            exit(1);
        }
        savedHash[i] = (UCHAR)val;
    }

    fclose(pFile);
}

static void readPasswordFromStdin(char *password, size_t bufferSize)
{
    char *replace = NULL;

    if (fgets(password, (int)bufferSize, stdin) == NULL)
    {
        exit(1);
    }

    replace = strchr(password, '\r');
    if (replace != NULL)
    {
        *replace = '\0';
    }
    replace = strchr(password, '\n');
    if (replace != NULL)
    {
        *replace = '\0';
    }
}

static void verifyPasswordWithSha512(void)
{
    HCRYPTPROV hCryptProv = 0;
    HCRYPTHASH hHash = 0;
    char password[PASSWORD_INPUT_SIZE] = "";
    UCHAR savedHash[SHA512_SUM_SIZE];
    UCHAR calcHash[SHA512_SUM_SIZE];
    DWORD hashSize = SHA512_SUM_SIZE;
    int failed = 0;

    memset(savedHash, 0, sizeof(savedHash));
    memset(calcHash, 0, sizeof(calcHash));

    loadSavedHash(PASSWORD_FILE, savedHash, SHA512_SUM_SIZE);
    readPasswordFromStdin(password, sizeof(password));

    if (!CryptAcquireContextW(&hCryptProv, 0, 0, PROV_RSA_FULL, 0))
    {
        SecureZeroMemory(password, sizeof(password));
        exit(1);
    }

    do
    {
        /* Safety fix: use SHA-512 instead of broken/reversible MD2 */
        if (!CryptCreateHash(hCryptProv, CALG_SHA_512, 0, 0, &hHash))
        {
            failed = 1;
            break;
        }
        if (!CryptHashData(hHash, (BYTE *)password, (DWORD)strlen(password), 0))
        {
            failed = 1;
            break;
        }
        if (!CryptGetHashParam(hHash, HP_HASHVAL, (BYTE *)calcHash, &hashSize, 0))
        {
            failed = 1;
            break;
        }
    }
    while (0);

    SecureZeroMemory(password, sizeof(password));

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

    if (memcmp(savedHash, calcHash, SHA512_SUM_SIZE * sizeof(UCHAR)) == 0)
    {
        printLine("Access granted");
    }
    else
    {
        printLine("Access denied");
    }
}

#ifndef OMITBAD

void CWE328_Reversible_One_Way_Hash__w32_MD2_01_bad()
{
    verifyPasswordWithSha512();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    verifyPasswordWithSha512();
}

void CWE328_Reversible_One_Way_Hash__w32_MD2_01_good()
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
    CWE328_Reversible_One_Way_Hash__w32_MD2_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE328_Reversible_One_Way_Hash__w32_MD2_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
