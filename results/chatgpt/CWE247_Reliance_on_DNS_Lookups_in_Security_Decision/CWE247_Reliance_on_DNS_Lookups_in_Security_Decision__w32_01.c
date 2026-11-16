/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01.c
Label Definition File: CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5
#define SECRET_HOSTNAME "www.domain.nonexistanttld"

static void handleClient(int logOnly)
{
    WSADATA wsaData;
    BOOL initialized = FALSE;
    SOCKET listener = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    struct sockaddr_in service;
    struct sockaddr_in peer;
    int peerLength = sizeof(peer);
    do
    {
        struct hostent *host;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) break;
        initialized = TRUE;
        listener = socket(PF_INET, SOCK_STREAM, 0);
        if (listener == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(LISTEN_PORT);
        if (bind(listener, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        if (listen(listener, LISTEN_BACKLOG) == SOCKET_ERROR) break;
        memset(&peer, 0, sizeof(peer));
        client = accept(listener, (struct sockaddr *)&peer, &peerLength);
        if (client == INVALID_SOCKET || peer.sin_family != AF_INET) break;
        host = gethostbyaddr((char *)&peer.sin_addr, sizeof(peer.sin_addr), AF_INET);
        if (host == NULL || host->h_name == NULL) break;
        printLine(host->h_name);
        if (logOnly)
        {
            FILE *log = fopen("log.txt", "a+");
            /* A failed open must not be passed to fprintf or fclose. */
            if (log != NULL)
            {
                fprintf(log, "Host name: %s\n", host->h_name);
                fclose(log);
            }
        }
        else if (strcmp(host->h_name, SECRET_HOSTNAME) == 0)
        {
            printLine("Access granted.");
        }
    } while (0);
    if (client != INVALID_SOCKET) closesocket(client);
    if (listener != INVALID_SOCKET) closesocket(listener);
    if (initialized) WSACleanup();
}
#ifndef OMITBAD
void CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_bad(void)
{
    handleClient(0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    handleClient(1);
}
void CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_good(void)
{
    good1();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE247_Reliance_on_DNS_Lookups_in_Security_Decision__w32_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
