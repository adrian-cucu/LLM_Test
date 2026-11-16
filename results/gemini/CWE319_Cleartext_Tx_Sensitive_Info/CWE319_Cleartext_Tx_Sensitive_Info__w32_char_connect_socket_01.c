/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01.c
Label Definition File: CWE319_Cleartext_Tx_Sensitive_Info__w32.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 319 Cleartext Transmission of Sensitive Information
 * BadSource: connect_socket Read the password using a connect socket (client side)
 * GoodSource: Use a hardcoded password (one that was not sent over the network)
 * Sinks:
 *    GoodSink: Decrypt the password before using it in an authentication API call to show that it was transferred as ciphertext
 *    BadSink : Use the password directly from the source in an authentication API call to show that it was transferred as plaintext
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#pragma comment(lib, "ws2_32") /* include ws2_32.lib when linking */

#define TCP_PORT 27015
#define IP_ADDRESS "127.0.0.1"

#pragma comment(lib, "advapi32.lib")

#define HASH_INPUT "ABCDEFG123456" /* INCIDENTAL: Hardcoded crypto */
#define PASSWORD_BUFFER_SIZE 100
#define DEFAULT_USERNAME "User"
#define DEFAULT_DOMAIN "Domain"
#define LOCAL_PASSWORD "Password1234!"

static void stripTrailingCrlf(char *str)
{
    char *replace = strchr(str, '\r');
    if (replace != NULL)
    {
        *replace = '\0';
    }
    replace = strchr(str, '\n');
    if (replace != NULL)
    {
        *replace = '\0';
    }
}

static void readPasswordFromSocket(char *password, size_t bufferSize)
{
    WSADATA wsaData;
    int wsaDataInit = 0;
    SOCKET connectSocket = INVALID_SOCKET;
    size_t passwordLen = strlen(password);

    if (passwordLen + 1 >= bufferSize)
    {
        return;
    }

    do
    {
        struct sockaddr_in service;
        int recvResult = 0;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
        {
            break;
        }
        wsaDataInit = 1;

        connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connectSocket == INVALID_SOCKET)
        {
            break;
        }

        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);

        if (connect(connectSocket, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
        {
            break;
        }

        recvResult = recv(connectSocket, password + passwordLen, (int)(bufferSize - passwordLen - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }

        password[passwordLen + (size_t)recvResult] = '\0';
        stripTrailingCrlf(password);
    }
    while (0);

    if (connectSocket != INVALID_SOCKET)
    {
        closesocket(connectSocket);
    }
    if (wsaDataInit)
    {
        WSACleanup();
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
        /* Safety fix: verify decrypted byte count fits in destination buffer */
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

void CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_bad()
{
    char passwordBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *password = passwordBuffer;

    readPasswordFromSocket(password, sizeof(passwordBuffer));
    /* Safety fix: decrypt password received over network before authenticating */
    decryptHexPassword(password, sizeof(passwordBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, password);
    SecureZeroMemory(passwordBuffer, sizeof(passwordBuffer));
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B(void)
{
    char passwordBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *password = passwordBuffer;

    /* Safety fix: use bounded snprintf instead of strcpy */
    snprintf(password, sizeof(passwordBuffer), "%s", LOCAL_PASSWORD);
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, password);
    SecureZeroMemory(passwordBuffer, sizeof(passwordBuffer));
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G(void)
{
    char passwordBuffer[PASSWORD_BUFFER_SIZE] = "";
    char *password = passwordBuffer;

    readPasswordFromSocket(password, sizeof(passwordBuffer));
    decryptHexPassword(password, sizeof(passwordBuffer));
    authenticateUser(DEFAULT_USERNAME, DEFAULT_DOMAIN, password);
    SecureZeroMemory(passwordBuffer, sizeof(passwordBuffer));
}

void CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_good()
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
    CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
