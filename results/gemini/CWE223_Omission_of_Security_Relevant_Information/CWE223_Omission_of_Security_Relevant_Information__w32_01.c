/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE223_Omission_of_Security_Relevant_Information__w32_01.c
Label Definition File: CWE223_Omission_of_Security_Relevant_Information__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 223 Omission of Security Relevant Information
 * Sinks:
 *    GoodSink: Log the username
 *    BadSink : Username is not logged
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <winsock2.h>
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ws2_32")

#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5
#define USERNAME_SZ 15
#define DOMAIN "Domain"
#define PASSWORD "ABCD1234!"

static void receiveLogAndLogonUser(void)
{
    WSADATA wsaData;
    BOOL wsaDataInit = FALSE;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    char username[USERNAME_SZ + 1] = "";
    HANDLE pHandle = NULL;
    int recvResult = 0;

    do
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            break;
        }
        wsaDataInit = TRUE;
        listenSocket = socket(PF_INET, SOCK_STREAM, 0);
        if (listenSocket == INVALID_SOCKET)
        {
            break;
        }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(LISTEN_PORT);
        if (SOCKET_ERROR == bind(listenSocket, (struct sockaddr *)&service, sizeof(service)))
        {
            break;
        }
        if (SOCKET_ERROR == listen(listenSocket, LISTEN_BACKLOG))
        {
            break;
        }
        acceptSocket = accept(listenSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET)
        {
            break;
        }
        recvResult = recv(acceptSocket, username, USERNAME_SZ, 0);
        if (recvResult != USERNAME_SZ)
        {
            break;
        }
        username[USERNAME_SZ] = '\0';

        /* Safety fix: include the username in the security-relevant log entry */
        fprintf(stderr, "Attempted login by %s\n", username);

        if (LogonUserA(
                username,
                DOMAIN,
                PASSWORD,
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
    while (0);

    if (acceptSocket != INVALID_SOCKET)
    {
        closesocket(acceptSocket);
    }
    if (listenSocket != INVALID_SOCKET)
    {
        closesocket(listenSocket);
    }
    if (wsaDataInit)
    {
        WSACleanup();
    }
}

#ifndef OMITBAD

void CWE223_Omission_of_Security_Relevant_Information__w32_01_bad()
{
    receiveLogAndLogonUser();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    receiveLogAndLogonUser();
}

void CWE223_Omission_of_Security_Relevant_Information__w32_01_good()
{
    good1();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE223_Omission_of_Security_Relevant_Information__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE223_Omission_of_Security_Relevant_Information__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
