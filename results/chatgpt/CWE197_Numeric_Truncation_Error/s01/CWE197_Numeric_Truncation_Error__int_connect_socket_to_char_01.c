/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE197_Numeric_Truncation_Error__int_connect_socket_to_char_01.c
Label Definition File: CWE197_Numeric_Truncation_Error__int.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <errno.h>
#include <limits.h>
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#pragma comment(lib, "ws2_32")
#define CLOSE_SOCKET closesocket
#else
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
#ifndef OMITBAD
static int receiveInteger(void)
{
    int data = -1;
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
#ifdef _WIN32
    WSADATA wsaData;
    int initialized = 0;
#endif
    do
    {
        char input[CHAR_ARRAY_SIZE];
        int received;
        long parsed;
#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) break;
        initialized = 1;
#endif
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        received = recv(connection, input, (int)sizeof(input) - 1, 0);
        if (received <= 0) break;
        input[received] = '\0';
        /* Avoid atoi overflow without changing representable numeric prefixes. */
        errno = 0;
        parsed = strtol(input, NULL, 10);
        if (errno != ERANGE && parsed >= INT_MIN && parsed <= INT_MAX)
            data = (int)parsed;
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
    return data;
}
void CWE197_Numeric_Truncation_Error__int_connect_socket_to_char_01_bad(void)
{
    printHexCharLine((char)receiveInteger());
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    int data = CHAR_MAX - 5;
    printHexCharLine((char)data);
}
void CWE197_Numeric_Truncation_Error__int_connect_socket_to_char_01_good(void)
{
    goodG2B();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE197_Numeric_Truncation_Error__int_connect_socket_to_char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE197_Numeric_Truncation_Error__int_connect_socket_to_char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
