/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE222_Truncation_of_Security_Relevant_Information__w32_01.c
Label Definition File: CWE222_Truncation_of_Security_Relevant_Information__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ws2_32")
#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5
#define USERNAME_SIZE 15
#define TRUNCATED_USERNAME_SIZE 4
#define DOMAIN "Domain"
#define PASSWORD "ABCD1234!"

static void receiveAndAuthenticate(int truncateUsername)
{
    WSADATA wsaData;
    BOOL initialized = FALSE;
    SOCKET listener = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    struct sockaddr_in service;
    char username[USERNAME_SIZE + 1];
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
        if (recv(client, username, USERNAME_SIZE, 0) != USERNAME_SIZE) break;
        username[USERNAME_SIZE] = '\0';
        /* Truncation is part of this variant's authentication behavior. */
        if (truncateUsername) username[TRUNCATED_USERNAME_SIZE] = '\0';
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
void CWE222_Truncation_of_Security_Relevant_Information__w32_01_bad(void)
{
    receiveAndAuthenticate(1);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    receiveAndAuthenticate(0);
}
void CWE222_Truncation_of_Security_Relevant_Information__w32_01_good(void)
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
    CWE222_Truncation_of_Security_Relevant_Information__w32_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE222_Truncation_of_Security_Relevant_Information__w32_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
