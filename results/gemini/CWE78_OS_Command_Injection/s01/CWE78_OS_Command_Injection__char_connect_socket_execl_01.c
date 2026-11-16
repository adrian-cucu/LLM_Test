/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE78_OS_Command_Injection__char_connect_socket_execl_01.c
Label Definition File: CWE78_OS_Command_Injection.strings.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 78 OS Command Injection
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Fixed string
 * Sink: execl
 *    BadSink : execute command with execl
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <wchar.h>
#include <ctype.h>

#ifdef _WIN32
#define COMMAND_INT_PATH "%WINDIR%\\system32\\cmd.exe"
#define COMMAND_INT "cmd.exe"
#define COMMAND_ARG1 "/c"
#define COMMAND_ARG2 "dir "
#define COMMAND_ARG3 data
#else /* NOT _WIN32 */
#include <unistd.h>
#define COMMAND_INT_PATH "/bin/sh"
#define COMMAND_INT "sh"
#define COMMAND_ARG1 "-c"
#define COMMAND_ARG2 "ls "
#define COMMAND_ARG3 data
#endif

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
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define CLOSE_SOCKET close
#define SOCKET int
#endif

#define TCP_PORT 27015
#define IP_ADDRESS "127.0.0.1"
#define DATA_BUFFER_SIZE 100

#ifdef _WIN32
#include <process.h>
#define EXECL _execl
#else /* NOT _WIN32 */
#define EXECL execl
#endif

static void strip_crlf(char *buffer)
{
    char *replace = strchr(buffer, '\r');
    if (replace != NULL)
    {
        *replace = '\0';
    }
    replace = strchr(buffer, '\n');
    if (replace != NULL)
    {
        *replace = '\0';
    }
}

static int read_socket_append(char *buffer, size_t bufferSize)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    int recvResult = 0;
    int success = 0;
    struct sockaddr_in service;
    SOCKET connectSocket = INVALID_SOCKET;
    size_t dataLen = strlen(buffer);

    if (bufferSize <= dataLen + 1)
    {
        return 0;
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
        recvResult = recv(connectSocket, buffer + dataLen, (int)(bufferSize - dataLen - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }
        buffer[dataLen + (size_t)recvResult] = '\0';
        strip_crlf(buffer);
        success = 1;
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
    return success;
}

static int is_safe_path_argument(const char *arg)
{
    size_t i = 0;
    if (arg == NULL || arg[0] == '\0')
    {
        return 0;
    }
    for (i = 0; arg[i] != '\0'; i++)
    {
        unsigned char ch = (unsigned char)arg[i];
        if (!isalnum(ch) && ch != '.' && ch != '_' && ch != '-' && ch != '/' && ch != '\\' && ch != '*')
        {
            return 0;
        }
    }
    return 1;
}

#ifndef OMITBAD

void CWE78_OS_Command_Injection__char_connect_socket_execl_01_bad()
{
    char dataBuffer[DATA_BUFFER_SIZE] = COMMAND_ARG2;
    char *data = dataBuffer;
    size_t prefixLen = strlen(dataBuffer);

    if (!read_socket_append(data, DATA_BUFFER_SIZE))
    {
        printLine("Failed to read command argument from socket.");
        return;
    }

    /* Safety fix: validate socket input against a strict allowlist before passing to execl() */
    if (!is_safe_path_argument(data + prefixLen))
    {
        printLine("Rejected unsafe command argument.");
        return;
    }

    EXECL(COMMAND_INT_PATH, COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG3, NULL);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char dataBuffer[DATA_BUFFER_SIZE] = COMMAND_ARG2;
    char *data = dataBuffer;
    strcat(data, "*.*");
    EXECL(COMMAND_INT_PATH, COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG3, NULL);
}

void CWE78_OS_Command_Injection__char_connect_socket_execl_01_good()
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
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE78_OS_Command_Injection__char_connect_socket_execl_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE78_OS_Command_Injection__char_connect_socket_execl_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
