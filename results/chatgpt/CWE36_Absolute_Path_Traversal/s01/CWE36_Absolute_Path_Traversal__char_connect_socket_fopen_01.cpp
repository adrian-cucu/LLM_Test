/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE36_Absolute_Path_Traversal__char_connect_socket_fopen_01.cpp
Label Definition File: CWE36_Absolute_Path_Traversal.label.xml
Template File: sources-sink-01.tmpl.cpp
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
#define FOPEN fopen
namespace CWE36_Absolute_Path_Traversal__char_connect_socket_fopen_01
{
static void openAndClose(const char *path)
{
    FILE *file = FOPEN(path, "wb+");
    if (file != NULL) fclose(file);
}
#ifndef OMITBAD
static void receivePath(char *path, size_t capacity)
{
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
#ifdef _WIN32
    WSADATA wsaData;
    bool initialized = false;
#endif
    do
    {
        int received;
        if (capacity <= 1) break;
#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) break;
        initialized = true;
#endif
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        received = recv(connection, path, (int)(capacity - 1), 0);
        if (received <= 0) break;
        path[received] = '\0';
        path[strcspn(path, "\r\n")] = '\0';
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
}
void bad()
{
    char path[FILENAME_MAX] = "";
    receivePath(path, sizeof(path));
    openAndClose(path);
}
#endif
#ifndef OMITGOOD
static void goodG2B()
{
#ifdef _WIN32
    char path[FILENAME_MAX] = "c:\\temp\\file.txt";
#else
    char path[FILENAME_MAX] = "/tmp/file.txt";
#endif
    openAndClose(path);
}
void good()
{
    goodG2B();
}
#endif
}
#ifdef INCLUDEMAIN
using namespace CWE36_Absolute_Path_Traversal__char_connect_socket_fopen_01;
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
