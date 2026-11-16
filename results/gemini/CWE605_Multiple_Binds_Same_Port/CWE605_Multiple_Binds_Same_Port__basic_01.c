/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE605_Multiple_Binds_Same_Port__basic_01.c
Label Definition File: CWE605_Multiple_Binds_Same_Port__basic.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 605 Multiple Binds to the Same Port
 * Sinks:
 *    GoodSink: Do not allow multiple binds to the same port
 *    BadSink : Set the SO_REUSEADDR socket option allowing multiple binds to the same port
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <wchar.h>
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#define PATH_SZ 100
#pragma comment(lib, "ws2_32") /* include ws2_32.lib when linking */
#define CLOSE_SOCKET closesocket
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PATH_SZ PATH_MAX
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define CLOSE_SOCKET close
#define SOCKET int
#endif

#define TCP_PORT 27015
#define LISTEN_BACKLOG 5
#define DATA_BUFFER_SIZE 100

static void stripCrLf(char *str)
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

static void runTcpServer(void)
{
    char data[DATA_BUFFER_SIZE] = "";
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    int recvResult = 0;
    struct sockaddr_in service;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptSocket = INVALID_SOCKET;
    size_t dataLen = strlen(data);

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
        if (acceptSocket == INVALID_SOCKET)
        {
            break;
        }

        recvResult = recv(acceptSocket, data + dataLen, (int)(DATA_BUFFER_SIZE - dataLen - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }

        if (dataLen + (size_t)recvResult < DATA_BUFFER_SIZE)
        {
            data[dataLen + (size_t)recvResult] = '\0';
        }
        else
        {
            data[DATA_BUFFER_SIZE - 1] = '\0';
        }
        stripCrLf(data);
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
    printLine(data);
}

#ifndef OMITBAD

void CWE605_Multiple_Binds_Same_Port__basic_01_bad()
{
    /* Safety fix: do not set SO_REUSEADDR to prevent multiple binds to the same port. */
    runTcpServer();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    runTcpServer();
}

void CWE605_Multiple_Binds_Same_Port__basic_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));

#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE605_Multiple_Binds_Same_Port__basic_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE605_Multiple_Binds_Same_Port__basic_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
