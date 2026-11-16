/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE194_Unexpected_Sign_Extension__connect_socket_malloc_01.c
Label Definition File: CWE194_Unexpected_Sign_Extension.label.xml
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
#define CHAR_ARRAY_SIZE 8
#define IP_ADDRESS "127.0.0.1"

static void allocateAndPrint(short length)
{
    /* Reject zero/negative lengths before unsigned conversion or length - 1. */
    if (length > 0 && length < 100)
    {
        size_t size = (size_t)length;
        char *buffer = malloc(size);
        if (buffer == NULL) exit(-1);
        memset(buffer, 'A', size - 1);
        buffer[size - 1] = '\0';
        printLine(buffer);
        free(buffer);
    }
}
#ifndef OMITBAD
void CWE194_Unexpected_Sign_Extension__connect_socket_malloc_01_bad(void)
{
    short data = 0;
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
        /* strtol detects out-of-range values instead of atoi's undefined overflow. */
        errno = 0;
        parsed = strtol(input, NULL, 10);
        data = (errno == ERANGE || parsed < SHRT_MIN || parsed > SHRT_MAX)
                   ? -1 : (short)parsed;
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
    allocateAndPrint(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    allocateAndPrint(99);
}
void CWE194_Unexpected_Sign_Extension__connect_socket_malloc_01_good(void)
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
    CWE194_Unexpected_Sign_Extension__connect_socket_malloc_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE194_Unexpected_Sign_Extension__connect_socket_malloc_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
