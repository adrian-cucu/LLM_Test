/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE510_Trapdoor__hostname_based_logic_01.c
Label Definition File: CWE510_Trapdoor.label.xml
Template File: point-flaw-01.tmpl.c
*/
#ifndef _WIN32
#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include "std_testcase.h"
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32")
#define CLOSE_SOCKET closesocket
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define CLOSE_SOCKET close
#define SOCKET int
#endif
#define ADMIN_MESSAGE "Welcome, admin!"
#define DEFAULT_MESSAGE "Welcome!"

static void serveConnection(int useHostname)
{
    SOCKET listener = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    struct sockaddr_in service;
    const char *message = DEFAULT_MESSAGE;
    int admin = 0;
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) { return; }
#endif
    do
    {
        listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listener == INVALID_SOCKET) { break; }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(20000);
        if (bind(listener, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) { break; }
        if (listen(listener, 5) == SOCKET_ERROR) { break; }
        client = accept(listener, NULL, NULL);
        if (client == INVALID_SOCKET) { break; }
        if (useHostname)
        {
            struct sockaddr_in localAddress;
#ifdef _WIN32
            int addressLength = sizeof(localAddress);
#else
            /* POSIX socket APIs require socklen_t, not an int pointer. */
            socklen_t addressLength = sizeof(localAddress);
#endif
            char hostname[NI_MAXHOST];
            char serviceName[NI_MAXSERV];
            if (getsockname(client, (struct sockaddr *)&localAddress, &addressLength) == SOCKET_ERROR) { break; }
            if (getnameinfo((struct sockaddr *)&localAddress, sizeof(struct sockaddr),
                            hostname, sizeof(hostname), serviceName, sizeof(serviceName),
                            NI_NUMERICSERV) != 0) { break; }
            admin = strcmp("admin.google.com", hostname) == 0;
            if (admin) { message = ADMIN_MESSAGE; }
        }
        if (send(client, message, (int)strlen(message), 0) == SOCKET_ERROR)
        {
            if (!admin) { printLine("Send failed!"); }
        }
    } while (0);
    if (listener != INVALID_SOCKET) { CLOSE_SOCKET(listener); }
    if (client != INVALID_SOCKET) { CLOSE_SOCKET(client); }
#ifdef _WIN32
    WSACleanup();
#endif
}
#ifndef OMITBAD
void CWE510_Trapdoor__hostname_based_logic_01_bad()
{
    serveConnection(1);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    serveConnection(0);
}
void CWE510_Trapdoor__hostname_based_logic_01_good()
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
    CWE510_Trapdoor__hostname_based_logic_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE510_Trapdoor__hostname_based_logic_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
