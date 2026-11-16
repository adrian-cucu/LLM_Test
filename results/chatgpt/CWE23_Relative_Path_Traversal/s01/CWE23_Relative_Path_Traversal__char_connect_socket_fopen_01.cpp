/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE23_Relative_Path_Traversal__char_connect_socket_fopen_01.cpp
Label Definition File: CWE23_Relative_Path_Traversal.label.xml
Template File: sources-sink-01.tmpl.cpp
*/
#include "std_testcase.h"
#ifdef _WIN32
#define BASEPATH "c:\\temp\\"
#else
#include <wchar.h>
#define BASEPATH "/tmp/"
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
namespace CWE23_Relative_Path_Traversal__char_connect_socket_fopen_01
{
static void openAndClose(const char *path)
{
    FILE *file = FOPEN(path, "wb+");
    if (file != NULL) fclose(file);
}
#ifndef OMITBAD
void bad()
{
    char data[FILENAME_MAX] = BASEPATH;
    const size_t length = strlen(data);
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
#ifdef _WIN32
    WSADATA wsaData;
    bool initialized = false;
#endif
    do
    {
        int received;
        if (length + 1 >= sizeof(data)) break;
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
        received = recv(connection, data + length, (int)(sizeof(data) - length - 1), 0);
        if (received <= 0) break;
        data[length + (size_t)received] = '\0';
        data[strcspn(data, "\r\n")] = '\0';
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
    openAndClose(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B()
{
    char data[FILENAME_MAX] = BASEPATH;
    strcat(data, "file.txt");
    openAndClose(data);
}
void good()
{
    goodG2B();
}
#endif
}
#ifdef INCLUDEMAIN
using namespace CWE23_Relative_Path_Traversal__char_connect_socket_fopen_01;
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
