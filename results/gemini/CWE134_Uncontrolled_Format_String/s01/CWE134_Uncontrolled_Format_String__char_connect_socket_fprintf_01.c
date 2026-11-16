/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01.c
Label Definition File: CWE134_Uncontrolled_Format_String.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 134 Uncontrolled Format String
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Copy a fixed string into data
 * Sinks: fprintf
 *    GoodSink: fprintf with "%s" as the second argument and data as the third
 *    BadSink : fprintf with data as the second argument
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

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
#define DATA_BUFFER_SIZE 100
#define FIXED_TEST_STRING "fixedstringtest"

static void stripCrlf(char *str)
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

static void readDataFromConnectSocket(char *data, size_t bufferSize)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    int recvResult = 0;
    size_t dataLen = strlen(data);

    if (dataLen + 1 >= bufferSize)
    {
        return;
    }

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
        data[dataLen + (size_t)recvResult] = '\0';
        stripCrlf(data);
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

#ifndef OMITBAD

void CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_bad()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readDataFromConnectSocket(data, sizeof(dataBuffer));
    /* Safety fix: use "%s" format specifier to prevent format string vulnerability */
    fprintf(stdout, "%s", data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    /* Safety fix: use bounded copy into dataBuffer */
    snprintf(data, sizeof(dataBuffer), "%s", FIXED_TEST_STRING);
    /* Safety fix: use "%s" format specifier to prevent format string vulnerability */
    fprintf(stdout, "%s", data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readDataFromConnectSocket(data, sizeof(dataBuffer));
    fprintf(stdout, "%s\n", data);
}

void CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_good()
{
    goodG2B();
    goodB2G();
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
    CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
