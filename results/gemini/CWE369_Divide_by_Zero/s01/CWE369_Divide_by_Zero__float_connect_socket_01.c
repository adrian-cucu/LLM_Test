/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE369_Divide_by_Zero__float_connect_socket_01.c
Label Definition File: CWE369_Divide_by_Zero__float.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 369 Divide by Zero
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: A hardcoded non-zero number (two)
 * Sinks:
 *    GoodSink: Check value of or near zero before dividing
 *    BadSink : Divide a constant by data
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <math.h>

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
#define CHAR_ARRAY_SIZE 20
#define IP_ADDRESS "127.0.0.1"
#define NUMERATOR 100.0
#define GOOD_DIVISOR 2.0F
#define ZERO_EPSILON 0.000001

static float readFloatFromSocket(float defaultValue)
{
    float data = defaultValue;
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

        recvResult = recv(connectSocket, inputBuffer, CHAR_ARRAY_SIZE - 1, 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }

        inputBuffer[recvResult] = '\0';
        data = (float)atof(inputBuffer);
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

static void divideAndPrintSafe(float divisor)
{
    /* Safety fix: Check for zero or near-zero divisor before dividing to prevent divide-by-zero */
    if (fabs((double)divisor) > ZERO_EPSILON)
    {
        int result = (int)(NUMERATOR / divisor);
        printIntLine(result);
    }
    else
    {
        printLine("This would result in a divide by zero");
    }
}

#ifndef OMITBAD

void CWE369_Divide_by_Zero__float_connect_socket_01_bad()
{
    float data = 0.0F;

    data = readFloatFromSocket(data);
    divideAndPrintSafe(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    float data = GOOD_DIVISOR;

    divideAndPrintSafe(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    float data = 0.0F;

    data = readFloatFromSocket(data);
    divideAndPrintSafe(data);
}

void CWE369_Divide_by_Zero__float_connect_socket_01_good()
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
    CWE369_Divide_by_Zero__float_connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE369_Divide_by_Zero__float_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
