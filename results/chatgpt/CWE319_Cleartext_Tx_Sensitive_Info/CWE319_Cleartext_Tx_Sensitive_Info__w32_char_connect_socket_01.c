/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01.c
Label Definition File: CWE319_Cleartext_Tx_Sensitive_Info__w32.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <winsock2.h>
#include <windows.h>
#include <wincrypt.h>
#include <direct.h>
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "advapi32.lib")
#define TCP_PORT 27015
#define IP_ADDRESS "127.0.0.1"
#define HASH_INPUT "ABCDEFG123456" /* Original testcase key material. */
enum { PASSWORD_CAPACITY = 100 };

static void receivePassword(char *password)
{
    WSADATA wsaData;
    int initialized = 0;
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
    do
    {
        int received;
        size_t length = strlen(password);
        if (length + 1 >= PASSWORD_CAPACITY) break;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) break;
        initialized = 1;
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        received = recv(connection, password + length, (int)(PASSWORD_CAPACITY - length - 1), 0);
        if (received <= 0) break;
        password[length + (size_t)received] = '\0';
        password[strcspn(password, "\r\n")] = '\0';
    } while (0);
    if (connection != INVALID_SOCKET) closesocket(connection);
    if (initialized) WSACleanup();
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
void CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_bad(void)
{
    char password[PASSWORD_CAPACITY] = "";
    receivePassword(password);
    authenticate(password);
    /* Clear sensitive stack storage after its last use. */
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
        /* Do not trust a returned length beyond the payload allocation. */
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
static void goodG2B(void)
{
    char password[PASSWORD_CAPACITY] = "Password1234!";
    authenticate(password);
    SecureZeroMemory(password, sizeof(password));
}
static void goodB2G(void)
{
    char password[PASSWORD_CAPACITY] = "";
    receivePassword(password);
    decryptPassword(password);
    authenticate(password);
    SecureZeroMemory(password, sizeof(password));
}
void CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_good(void)
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
    CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE319_Cleartext_Tx_Sensitive_Info__w32_char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
