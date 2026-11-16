/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE15_External_Control_of_System_or_Configuration_Setting__w32_01.c
Label Definition File: CWE15_External_Control_of_System_or_Configuration_Setting__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#include <windows.h>
#define LISTEN_PORT 999
#define LISTEN_BACKLOG 5

static void setComputerName(const char *name)
{
    if (!SetComputerNameA(name))
    {
        printLine("Failure setting computer name");
        exit(1);
    }
}
#ifndef OMITBAD
void CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_bad(void)
{
    char data[100] = "";
    WSADATA wsaData;
    BOOL initialized = FALSE;
    SOCKET listener = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    struct sockaddr_in service;
    do
    {
        int received;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) break;
        initialized = TRUE;
        listener = socket(PF_INET, SOCK_STREAM, 0);
        if (listener == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = INADDR_ANY;
        service.sin_port = htons(LISTEN_PORT);
        if (bind(listener, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        if (listen(listener, LISTEN_BACKLOG) == SOCKET_ERROR) break;
        client = accept(listener, NULL, NULL);
        if (client == INVALID_SOCKET) break;
        received = recv(client, data, (int)sizeof(data) - 1, 0);
        if (received <= 0) break;
        data[received] = '\0';
    } while (0);
    if (client != INVALID_SOCKET) closesocket(client);
    if (listener != INVALID_SOCKET) closesocket(listener);
    if (initialized) WSACleanup();
    setComputerName(data);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    setComputerName("hostname");
}
void CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_good(void)
{
    goodG2B();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE15_External_Control_of_System_or_Configuration_Setting__w32_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
