/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE114_Process_Control__w32_char_connect_socket_01.c
Label Definition File: CWE114_Process_Control__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <wchar.h>
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

static void loadAndReleaseLibrary(const char *path)
{
    HMODULE module = LoadLibraryA(path);
    if (module != NULL)
    {
        FreeLibrary(module);
        printLine("Library loaded and freed successfully");
    }
    else
    {
        printLine("Unable to load library");
    }
}

#ifndef OMITBAD
void CWE114_Process_Control__w32_char_connect_socket_01_bad(void)
{
    char data[100] = "";
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
#ifdef _WIN32
    WSADATA wsaData;
    int initialized = 0;
#endif
    do
    {
        int received;
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
        received = recv(connection, data, (int)sizeof(data) - 1, 0);
        if (received <= 0) break;
        data[received] = '\0';
        data[strcspn(data, "\r\n")] = '\0';
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
    /* Preserve the caller-selected library path and platform loader behavior. */
    loadAndReleaseLibrary(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    loadAndReleaseLibrary("C:\\Windows\\System32\\winsrv.dll");
}
void CWE114_Process_Control__w32_char_connect_socket_01_good(void)
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
    CWE114_Process_Control__w32_char_connect_socket_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE114_Process_Control__w32_char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
