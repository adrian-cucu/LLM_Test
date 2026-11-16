/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE223_Omission_of_Security_Relevant_Information__w32_01.c
Label Definition File: CWE223_Omission_of_Security_Relevant_Information__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ws2_32")
#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5
#define USERNAME_SZ 15
#define DOMAIN "Domain"
#define PASSWORD "ABCD1234!"

static void handleLogin(int logUsername)
{
    WSADATA wsaData;
    BOOL initialized = FALSE;
    SOCKET listener = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    struct sockaddr_in service;
    char username[USERNAME_SZ + 1];
    do
    {
        HANDLE user;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) break;
        initialized = TRUE;
        listener = socket(PF_INET, SOCK_STREAM, 0);
        if (listener == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(LISTEN_PORT);
        if (bind(listener, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        if (listen(listener, LISTEN_BACKLOG) == SOCKET_ERROR) break;
        client = accept(listener, NULL, NULL);
        if (client == INVALID_SOCKET) break;
        if (recv(client, username, USERNAME_SZ, 0) != USERNAME_SZ) break;
        username[USERNAME_SZ] = '\0';
        if (logUsername)
            fprintf(stderr, "Attempted login by %s\n", username);
        else
            fprintf(stderr, "Attempted login\n");
        if (LogonUserA(username, DOMAIN, PASSWORD, LOGON32_LOGON_NETWORK,
                       LOGON32_PROVIDER_DEFAULT, &user))
        {
            printLine("User logged in successfully.");
            CloseHandle(user);
        }
        else
        {
            printLine("Unable to login.");
        }
    } while (0);
    if (client != INVALID_SOCKET) closesocket(client);
    if (listener != INVALID_SOCKET) closesocket(listener);
    if (initialized) WSACleanup();
}
#ifndef OMITBAD
void CWE223_Omission_of_Security_Relevant_Information__w32_01_bad(void)
{
    handleLogin(0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    handleLogin(1);
}
void CWE223_Omission_of_Security_Relevant_Information__w32_01_good(void)
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
    CWE223_Omission_of_Security_Relevant_Information__w32_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE223_Omission_of_Security_Relevant_Information__w32_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
