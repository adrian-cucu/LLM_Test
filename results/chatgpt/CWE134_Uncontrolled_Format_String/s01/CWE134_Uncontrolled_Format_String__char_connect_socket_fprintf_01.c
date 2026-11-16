/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01.c
Label Definition File: CWE134_Uncontrolled_Format_String.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#ifndef _WIN32
#include <wchar.h>
#endif
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

static void receiveText(char *data, size_t capacity)
{
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
#ifdef _WIN32
    WSADATA wsaData;
    int initialized = 0;
#endif
    do
    {
        int received;
        size_t length = strlen(data);
        if (length + 1 >= capacity) break;
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
        received = recv(connection, data + length, (int)(capacity - length - 1), 0);
        if (received <= 0) break;
        data[length + (size_t)received] = '\0';
        data[strcspn(data, "\r\n")] = '\0';
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
}
#ifndef OMITBAD
void CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_bad(void)
{
    char data[100] = "";
    receiveText(data, sizeof(data));
    /* Preserve valid zero-argument formats, including %% escapes, but reject
     * conversions requiring arguments that this call cannot supply. */
    for (size_t i = 0; data[i] != '\0'; ++i)
    {
        if (data[i] == '%' && data[++i] != '%') return;
    }
    fprintf(stdout, data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    char data[] = "fixedstringtest";
    fprintf(stdout, data);
}
static void goodB2G(void)
{
    char data[100] = "";
    receiveText(data, sizeof(data));
    fprintf(stdout, "%s\n", data);
}
void CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_good(void)
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
    CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
