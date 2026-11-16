/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE427_Uncontrolled_Search_Path_Element__char_connect_socket_01.c
Label Definition File: CWE427_Uncontrolled_Search_Path_Element.label.xml
Template File: sources-sink-01.tmpl.c
*/
#ifndef _WIN32
#define _XOPEN_SOURCE 700
#endif
#include "std_testcase.h"
#include <wchar.h>
#ifdef _WIN32
#define NEW_PATH "%SystemRoot%\\system32"
#define PUTENV _putenv
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#pragma comment(lib, "ws2_32")
#define CLOSE_SOCKET closesocket
#else
#define NEW_PATH "/bin"
#define PUTENV putenv
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

static void setPath(const char *value)
{
    /* POSIX putenv retains its argument: use storage that outlives this call. */
    static char assignment[250];
    size_t length = strlen(value);
    if (length >= sizeof(assignment)) { return; }
    memcpy(assignment, value, length + 1);
    if (PUTENV(assignment) != 0) { printLine("putenv() failed"); }
}
#ifndef OMITBAD
void CWE427_Uncontrolled_Search_Path_Element__char_connect_socket_01_bad()
{
    char data[250] = "PATH=";
    size_t prefixLength = strlen(data);
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
    int received;
#ifdef _WIN32
    WSADATA wsaData;
    int initialized = 0;
#endif
    do
    {
#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) { break; }
        initialized = 1;
#endif
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) { break; }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) { break; }
        received = recv(connection, data + prefixLength, sizeof(data) - prefixLength - 1, 0);
        if (received <= 0) { break; }
        data[prefixLength + (size_t)received] = '\0';
        data[strcspn(data, "\r\n")] = '\0';
    } while (0);
    if (connection != INVALID_SOCKET) { CLOSE_SOCKET(connection); }
#ifdef _WIN32
    if (initialized) { WSACleanup(); }
#endif
    setPath(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    setPath("PATH=" NEW_PATH);
}
void CWE427_Uncontrolled_Search_Path_Element__char_connect_socket_01_good()
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
    CWE427_Uncontrolled_Search_Path_Element__char_connect_socket_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE427_Uncontrolled_Search_Path_Element__char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
