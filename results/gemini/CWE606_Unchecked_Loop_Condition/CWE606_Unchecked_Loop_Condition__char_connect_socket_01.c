/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE606_Unchecked_Loop_Condition__char_connect_socket_01.c
Label Definition File: CWE606_Unchecked_Loop_Condition.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 606 Unchecked Input For Loop Condition
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Input a number less than MAX_LOOP
 * Sinks:
 *    GoodSink: Use data as the for loop variant after checking to see if it is less than MAX_LOOP
 *    BadSink : Use data as the for loop variant without checking its size
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#define MAX_LOOP 10000
#define DATA_BUFFER_SIZE 100
#define GOOD_LOOP_COUNT_STR "15"

#ifndef _WIN32
#include <wchar.h>
#endif

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

#define TCP_PORT 27015
#define IP_ADDRESS "127.0.0.1"

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

static void readFromConnectSocket(char *data, size_t bufferSize)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    int recvResult = 0;
    struct sockaddr_in service;
    SOCKET connectSocket = INVALID_SOCKET;
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

        recvResult = recv(connectSocket, data + dataLen, (int)(bufferSize - dataLen - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }

        if (dataLen + (size_t)recvResult < bufferSize)
        {
            data[dataLen + (size_t)recvResult] = '\0';
        }
        else
        {
            data[bufferSize - 1] = '\0';
        }
        stripCrLf(data);
    }
    while (0);

    if (connectSocket != INVALID_SOCKET)
    {
        CLOSE_SOCKET(connectSocket);
    }
#ifdef _WIN32
    if (wsaDataInit)
    {
        WSACleanup();
    }
#endif
}

static void runBoundedLoop(const char *data)
{
    int i = 0;
    int n = 0;
    int intVariable = 0;

    /* Safety fix: validate that loop count n is within [0, MAX_LOOP) before iterating. */
    if (sscanf(data, "%d", &n) == 1 && n >= 0 && n < MAX_LOOP)
    {
        for (i = 0; i < n; i++)
        {
            intVariable++;
        }
        printIntLine(intVariable);
    }
}

#ifndef OMITBAD

void CWE606_Unchecked_Loop_Condition__char_connect_socket_01_bad()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    readFromConnectSocket(dataBuffer, DATA_BUFFER_SIZE);
    runBoundedLoop(dataBuffer);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    snprintf(dataBuffer, DATA_BUFFER_SIZE, "%s", GOOD_LOOP_COUNT_STR);
    runBoundedLoop(dataBuffer);
}

static void goodB2G(void)
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    readFromConnectSocket(dataBuffer, DATA_BUFFER_SIZE);
    runBoundedLoop(dataBuffer);
}

void CWE606_Unchecked_Loop_Condition__char_connect_socket_01_good()
{
    goodG2B();
    goodB2G();
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
    CWE606_Unchecked_Loop_Condition__char_connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE606_Unchecked_Loop_Condition__char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
