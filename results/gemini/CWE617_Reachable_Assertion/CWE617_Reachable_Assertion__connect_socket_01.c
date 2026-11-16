/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE617_Reachable_Assertion__connect_socket_01.c
Label Definition File: CWE617_Reachable_Assertion.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 617 Reachable Assertion
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Number greater than ASSERT_VALUE
 * Sink:
 *    BadSink : Assert if n is less than or equal to ASSERT_VALUE
 * Flow Variant: 01 Baseline
 *
 */

#include "std_testcase.h"

#include <assert.h>

#define ASSERT_VALUE 5

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
#define CHAR_ARRAY_SIZE (3 * sizeof(int) + 2)

static int readIntFromConnectSocket(int defaultValue)
{
    int data = defaultValue;
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    int recvResult = 0;
    struct sockaddr_in service;
    SOCKET connectSocket = INVALID_SOCKET;
    char inputBuffer[CHAR_ARRAY_SIZE] = "";

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

        recvResult = recv(connectSocket, inputBuffer, (int)(CHAR_ARRAY_SIZE - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }

        if ((size_t)recvResult < CHAR_ARRAY_SIZE)
        {
            inputBuffer[recvResult] = '\0';
        }
        else
        {
            inputBuffer[CHAR_ARRAY_SIZE - 1] = '\0';
        }
        data = atoi(inputBuffer);
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
    return data;
}

#ifndef OMITBAD

void CWE617_Reachable_Assertion__connect_socket_01_bad()
{
    int data = readIntFromConnectSocket(-1);

    /* Safety fix: validate data > ASSERT_VALUE instead of triggering a reachable assert() on untrusted/default input. */
    if (data <= ASSERT_VALUE)
    {
        printLine("Invalid input: value must exceed ASSERT_VALUE");
        return;
    }
    assert(data > ASSERT_VALUE);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B(void)
{
    int data = ASSERT_VALUE + 1;
    assert(data > ASSERT_VALUE);
}

void CWE617_Reachable_Assertion__connect_socket_01_good()
{
    goodG2B();
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
    CWE617_Reachable_Assertion__connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */

#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE617_Reachable_Assertion__connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */

    return 0;
}

#endif
