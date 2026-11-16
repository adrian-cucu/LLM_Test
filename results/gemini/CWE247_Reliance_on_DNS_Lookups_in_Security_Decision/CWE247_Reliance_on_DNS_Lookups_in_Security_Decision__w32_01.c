/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01.c
Label Definition File: CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
/*
 * @description
 * CWE: 247 Reliance on DNS Lookups in a Security Decision
 * Sinks:
 *    GoodSink: Log host name without using it in a security decision
 *    BadSink : Use the reverse DNS of the client to determine whether to allow the connection
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#include <winsock2.h>
#pragma comment(lib, "ws2_32")

#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5
#define LOG_FILENAME "log.txt"
#define HOSTNAME_BUF_SIZE 256

static int acceptAndResolveClientHost(char *hostNameOut, size_t hostNameOutSize)
{
    WSADATA wsaData;
    BOOL wsaDataInit = FALSE;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    int success = 0;

    do
    {
        struct sockaddr_in service;
        struct sockaddr_in serviceClient;
        int serviceClientLen = (int)sizeof(serviceClient);
        struct hostent *hostInfo = NULL;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
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

        if (bind(listenSocket, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
        {
            break;
        }
        if (listen(listenSocket, LISTEN_BACKLOG) == SOCKET_ERROR)
        {
            break;
        }

        client = accept(listenSocket, (struct sockaddr *)&serviceClient, &serviceClientLen);
        if (client == INVALID_SOCKET || serviceClient.sin_family != AF_INET)
        {
            break;
        }

        hostInfo = gethostbyaddr((char *)&serviceClient.sin_addr, sizeof(serviceClient.sin_addr), AF_INET);
        if (hostInfo == NULL || hostInfo->h_name == NULL)
        {
            break;
        }

        snprintf(hostNameOut, hostNameOutSize, "%s", hostInfo->h_name);
        success = 1;
    }
    while (0);

    if (client != INVALID_SOCKET)
    {
        closesocket(client);
    }
    if (listenSocket != INVALID_SOCKET)
    {
        closesocket(listenSocket);
    }
    if (wsaDataInit)
    {
        WSACleanup();
    }

    return success;
}

static void logClientHostname(void)
{
    char hostName[HOSTNAME_BUF_SIZE] = "";
    FILE *pFile = NULL;

    if (!acceptAndResolveClientHost(hostName, sizeof(hostName)))
    {
        return;
    }

    printLine(hostName);

    /* Safety fix: do not use spoofable reverse DNS for access control; log hostname and check fopen() result */
    pFile = fopen(LOG_FILENAME, "a+");
    if (pFile != NULL)
    {
        fprintf(pFile, "Host name: %s\n", hostName);
        fclose(pFile);
    }
}

#ifndef OMITBAD

void CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_bad()
{
    logClientHostname();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1(void)
{
    logClientHostname();
}

void CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_good()
{
    good1();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
