/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE114_Process_Control__w32_char_connect_socket_01.c
Label Definition File: CWE114_Process_Control__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 114 Process Control
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Hard code the full pathname to the library
 * Sink:
 *    BadSink : Load a dynamic link library
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <ctype.h>
#include <wchar.h>

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
#define IP_ADDRESS "127.0.0.1"
#define DATA_BUFFER_SIZE 100
#define SAFE_LIBRARY_PATH "C:\\Windows\\System32\\winsrv.dll"

static void stripCrlf(char *str)
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

static int isAbsoluteLibraryPath(const char *path)
{
    if (path == NULL || path[0] == '\0')
    {
        return 0;
    }
    if (isalpha((unsigned char)path[0]) && path[1] == ':' && (path[2] == '\\' || path[2] == '/'))
    {
        return 1;
    }
    if (path[0] == '\\' && path[1] == '\\')
    {
        return 1;
    }
    return 0;
}

static void readLibraryPathFromSocket(char *data, size_t bufferSize)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    int recvResult = 0;
    size_t dataLen = strlen(data);

    if (dataLen + 1 >= bufferSize)
    {
        return;
    }

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
        stripCrlf(data);
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

static void loadAndFreeLibrary(const char *libraryPath)
{
    HMODULE hModule = NULL;

    /* Safety fix: require a non-empty absolute path before calling LoadLibraryA */
    if (!isAbsoluteLibraryPath(libraryPath))
    {
        printLine("Unable to load library");
        return;
    }

    hModule = LoadLibraryA(libraryPath);
    if (hModule != NULL)
    {
        FreeLibrary(hModule);
        printLine("Library loaded and freed successfully");
    }
    else
    {
        printLine("Unable to load library");
    }
}

#ifndef OMITBAD

void CWE114_Process_Control__w32_char_connect_socket_01_bad()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readLibraryPathFromSocket(data, sizeof(dataBuffer));
    loadAndFreeLibrary(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    /* Safety fix: use bounded copy into dataBuffer */
    snprintf(data, sizeof(dataBuffer), "%s", SAFE_LIBRARY_PATH);
    loadAndFreeLibrary(data);
}

void CWE114_Process_Control__w32_char_connect_socket_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE114_Process_Control__w32_char_connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE114_Process_Control__w32_char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
