/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE400_Resource_Exhaustion__connect_socket_for_loop_01.c
Label Definition File: CWE400_Resource_Exhaustion.label.xml
Template File: sources-sinks-01.tmpl.c
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

static int readCount(void)
{
    int count = -1;
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
    char input[CHAR_ARRAY_SIZE];
    int received;
    long parsed;
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) { return count; }
#endif
    do
    {
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) { break; }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) { break; }
        received = recv(connection, input, sizeof(input) - 1, 0);
        if (received <= 0) { break; }
        input[received] = '\0';
        errno = 0;
        parsed = strtol(input, NULL, 10);
        /* atoi has undefined behavior for values outside the int range. */
        if (errno != ERANGE && parsed >= INT_MIN && parsed <= INT_MAX)
        {
            count = (int)parsed;
        }
    } while (0);
    if (connection != INVALID_SOCKET) { CLOSE_SOCKET(connection); }
#ifdef _WIN32
    WSACleanup();
#endif
    return count;
}

static void printGreetings(int count)
{
    size_t i;
    /* Reject negative/error counts before converting to an unsigned bound. */
    if (count < 0) { return; }
    for (i = 0; i < (size_t)count; ++i)
    {
        printLine("Hello");
    }
}
#ifndef OMITBAD
void CWE400_Resource_Exhaustion__connect_socket_for_loop_01_bad()
{
    printGreetings(readCount());
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    printGreetings(20);
}
static void goodB2G(void)
{
    int count = readCount();
    if (count > 0 && count <= 20)
    {
        printGreetings(count);
    }
}
void CWE400_Resource_Exhaustion__connect_socket_for_loop_01_good()
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE400_Resource_Exhaustion__connect_socket_for_loop_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE400_Resource_Exhaustion__connect_socket_for_loop_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
