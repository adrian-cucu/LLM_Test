/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE15_External_Control_of_System_or_Configuration_Setting__w32_01.c
Label Definition File: CWE15_External_Control_of_System_or_Configuration_Setting__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 15 External Control of System or Configuration Setting
 * BadSource:  Get the hostname from a network socket
 * GoodSource: Get the hostname from a string literal
 * Sink:
 *    BadSink : Set the hostname
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <ctype.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5
#define HOSTNAME_BUFFER_SIZE 100
#define DEFAULT_HOSTNAME "hostname"

#include <windows.h>

static int isValidHostname(const char *hostname)
{
    size_t i = 0;

    if (hostname == NULL || hostname[0] == '\0')
    {
        return 0;
    }
    for (i = 0; hostname[i] != '\0'; i++)
    {
        unsigned char ch = (unsigned char)hostname[i];
        if (!isalnum(ch) && ch != '-')
        {
            return 0;
        }
    }
    return 1;
}

static void readHostnameFromListenSocket(char *data, size_t bufferSize)
{
    WSADATA wsaData;
    BOOL wsaDataInit = FALSE;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    int recvResult = 0;

    if (bufferSize <= 1)
    {
        return;
    }

    do
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
        {
            break;
        }
        wsaDataInit = TRUE;
        listenSocket = socket(PF_INET, SOCK_STREAM, 0);
        if (listenSocket == INVALID_SOCKET)
        {
            break;
        }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(LISTEN_PORT);
        if (SOCKET_ERROR == bind(listenSocket, (struct sockaddr *)&service, sizeof(service)))
        {
            break;
        }
        if (SOCKET_ERROR == listen(listenSocket, LISTEN_BACKLOG))
        {
            break;
        }
        acceptSocket = accept(listenSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET)
        {
            break;
        }
        recvResult = recv(acceptSocket, data, (int)(bufferSize - 1), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }
        data[recvResult] = '\0';
    }
    while (0);

    if (acceptSocket != INVALID_SOCKET)
    {
        closesocket(acceptSocket);
    }
    if (listenSocket != INVALID_SOCKET)
    {
        closesocket(listenSocket);
    }
    if (wsaDataInit)
    {
        WSACleanup();
    }
}

static void applyComputerName(const char *hostname)
{
    /* Safety fix: validate hostname characters and non-empty length before calling SetComputerNameA */
    if (!isValidHostname(hostname))
    {
        printLine("Failure setting computer name");
        return;
    }

    if (!SetComputerNameA(hostname))
    {
        printLine("Failure setting computer name");
        exit(1);
    }
}

#ifndef OMITBAD

void CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_bad()
{
    char dataBuffer[HOSTNAME_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    readHostnameFromListenSocket(data, sizeof(dataBuffer));
    applyComputerName(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char dataBuffer[HOSTNAME_BUFFER_SIZE] = "";
    char *data = dataBuffer;

    /* Safety fix: use bounded copy into dataBuffer */
    snprintf(data, sizeof(dataBuffer), "%s", DEFAULT_HOSTNAME);
    applyComputerName(data);
}

void CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_good()
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
    CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
