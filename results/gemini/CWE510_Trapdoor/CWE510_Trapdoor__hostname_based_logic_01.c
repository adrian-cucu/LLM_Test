/*
 * @description
 * CWE: 510 Trapdoor
 * Sinks: hostname_based_logic
 *    GoodSink: No host-based logic
 *    BadSink : Different logic if a connection is made from a specific host name
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#pragma comment(lib, "ws2_32") /* include ws2_32.lib when linking */
#define CLOSE_SOCKET closesocket
#else /* NOT _WIN32 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define CLOSE_SOCKET close
#define SOCKET int
#endif

#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <netdb.h>
#endif

#define TCP_PORT 20000
#define LISTEN_BACKLOG 5
#define DEFAULT_MESSAGE "Welcome!"

static void serveGreetingOnce(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    struct sockaddr_in service;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptSocket = INVALID_SOCKET;

    do
    {
#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
        {
            break;
        }
        wsaDataInit = 1;
#endif
        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET)
        {
            break;
        }

        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(TCP_PORT);

        if (bind(listenSocket, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
        {
            break;
        }
        if (listen(listenSocket, LISTEN_BACKLOG) == SOCKET_ERROR)
        {
            break;
        }

        acceptSocket = accept(listenSocket, NULL, NULL);
        /* Safety fix: check against INVALID_SOCKET instead of SOCKET_ERROR */
        if (acceptSocket == INVALID_SOCKET)
        {
            break;
        }

        /* Safety fix: remove hostname-based trapdoor logic and always send default message */
        if (send(acceptSocket, DEFAULT_MESSAGE, (int)strlen(DEFAULT_MESSAGE), 0) == SOCKET_ERROR)
        {
            printLine("Send failed!");
        }
    }
    while (0);

    if (listenSocket != INVALID_SOCKET)
    {
        CLOSE_SOCKET(listenSocket);
    }
    if (acceptSocket != INVALID_SOCKET)
    {
        CLOSE_SOCKET(acceptSocket);
    }
#ifdef _WIN32
    if (wsaDataInit)
    {
        WSACleanup();
    }
#endif
}

#ifndef OMITBAD

void CWE510_Trapdoor__hostname_based_logic_01_bad()
{
    serveGreetingOnce();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    serveGreetingOnce();
}

void CWE510_Trapdoor__hostname_based_logic_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE510_Trapdoor__hostname_based_logic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE510_Trapdoor__hostname_based_logic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
