/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE123_Write_What_Where_Condition__connect_socket_01.c
Label Definition File: CWE123_Write_What_Where_Condition.label.xml
Template File: sources-sink-01.tmpl.c
*/
#include "std_testcase.h"
typedef struct _linkedList
{
    struct _linkedList *next;
    struct _linkedList *prev;
} linkedList;
typedef struct _badStruct
{
    linkedList list;
} badStruct;
static linkedList *linkedListPrev, *linkedListNext;
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
#define IP_ADDRESS "127.0.0.1"

static void insertNode(linkedList *head, linkedList *node)
{
    node->next = head->next;
    node->prev = head->prev;
    head->next = node;
    head->prev = node;
}
static void removeNode(linkedList *node)
{
    linkedListPrev = node->prev;
    linkedListNext = node->next;
    linkedListPrev->next = linkedListNext;
    linkedListNext->prev = linkedListPrev;
}
#ifndef OMITBAD
void CWE123_Write_What_Where_Condition__connect_socket_01_bad(void)
{
    badStruct data;
    linkedList head = {&head, &head};
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
#ifdef _WIN32
    WSADATA wsaData;
    int initialized = 0;
#endif
    insertNode(&head, &data.list);
    do
    {
        unsigned char receivedData[sizeof(data)];
        int received;
#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) break;
        initialized = 1;
#endif
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) break;
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) break;
        received = recv(connection, (char *)receivedData, (int)sizeof(receivedData), 0);
        if (received <= 0) break;
        /* Network bytes must not become native pointers. Only the original
         * single-node links are valid for this list, including partial reads. */
        if (memcmp(receivedData, &data, (size_t)received) != 0) break;
    } while (0);
    if (connection != INVALID_SOCKET) CLOSE_SOCKET(connection);
#ifdef _WIN32
    if (initialized) WSACleanup();
#endif
    removeNode(&data.list);
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    badStruct data;
    linkedList head = {&head, &head};
    insertNode(&head, &data.list);
    removeNode(&data.list);
}
void CWE123_Write_What_Where_Condition__connect_socket_01_good(void)
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
    CWE123_Write_What_Where_Condition__connect_socket_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE123_Write_What_Where_Condition__connect_socket_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
