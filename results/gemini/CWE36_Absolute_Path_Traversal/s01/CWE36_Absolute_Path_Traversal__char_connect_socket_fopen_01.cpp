/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE36_Absolute_Path_Traversal__char_connect_socket_fopen_01.cpp
Label Definition File: CWE36_Absolute_Path_Traversal.label.xml
Template File: sources-sink-01.tmpl.cpp
*/
/*
 * @description
 * CWE: 36 Absolute Path Traversal
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Full path and file name
 * Sink: fopen
 *    BadSink : Open the file named in data using fopen()
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#pragma comment(lib, "ws2_32") /* include ws2_32.lib when linking */
#define CLOSE_SOCKET closesocket
#define ALLOWED_BASE_DIR "c:\\temp\\"
#define FIXED_FULL_PATH "c:\\temp\\file.txt"
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
#define ALLOWED_BASE_DIR "/tmp/"
#define FIXED_FULL_PATH "/tmp/file.txt"
#endif

#define TCP_PORT 27015
#define IP_ADDRESS "127.0.0.1"
#define FOPEN fopen

namespace CWE36_Absolute_Path_Traversal__char_connect_socket_fopen_01
{

static void stripTrailingCrlf(char *str)
{
    char *replace = strchr(str, '\r');
    if (replace != NULL)
    {
        *replace = '\0';
    }
    replace = strchr(str, '\n');
    if (replace != NULL)
    {
        *replace = '\0';
    }
}

static void readPathFromSocket(char *data, size_t bufferSize)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    SOCKET connectSocket = INVALID_SOCKET;
    size_t dataLen = strlen(data);

    if (dataLen + 1 >= bufferSize)
    {
        return;
    }

    do
    {
        struct sockaddr_in service;
        int recvResult = 0;
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
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connectSocket, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
        {
            break;
        }
        recvResult = recv(connectSocket, data + dataLen, (int)(bufferSize - dataLen - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }
        data[dataLen + (size_t)recvResult] = '\0';
        stripTrailingCrlf(data);
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

static int isAllowedAbsolutePath(const char *path)
{
    size_t baseLen = strlen(ALLOWED_BASE_DIR);
    const char *relPart = NULL;

    if (strncmp(path, ALLOWED_BASE_DIR, baseLen) != 0)
    {
        return 0;
    }
    relPart = path + baseLen;
    if (relPart[0] == '\0')
    {
        return 0;
    }
    if (strstr(relPart, "..") != NULL)
    {
        return 0;
    }
    return 1;
}

static void openAndCloseFile(const char *path)
{
    FILE *pFile = NULL;
    /* Safety fix: validate path is within ALLOWED_BASE_DIR and contains no '..' traversal */
    if (!isAllowedAbsolutePath(path))
    {
        return;
    }
    pFile = FOPEN(path, "wb+");
    if (pFile != NULL)
    {
        fclose(pFile);
    }
}

#ifndef OMITBAD

void bad()
{
    char dataBuffer[FILENAME_MAX] = "";
    char *data = dataBuffer;
    readPathFromSocket(data, sizeof(dataBuffer));
    openAndCloseFile(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char dataBuffer[FILENAME_MAX] = "";
    char *data = dataBuffer;
    /* Safety fix: use bounded snprintf instead of unbounded strcat */
    snprintf(data, sizeof(dataBuffer), "%s", FIXED_FULL_PATH);
    openAndCloseFile(data);
}

void good()
{
    goodG2B();
}

#endif /* OMITGOOD */

} /* close namespace */

#ifdef INCLUDEMAIN

using namespace CWE36_Absolute_Path_Traversal__char_connect_socket_fopen_01;

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
