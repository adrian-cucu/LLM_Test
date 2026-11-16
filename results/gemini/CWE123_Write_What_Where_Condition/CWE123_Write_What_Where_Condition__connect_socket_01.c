/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE123_Write_What_Where_Condition__connect_socket_01.c
Label Definition File: CWE123_Write_What_Where_Condition.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 123 Write-What-Where Condition
 * BadSource: connect_socket Overwrite linked list pointers using a connect socket (client side)
 * GoodSource: Don't overwrite linked list pointers
 * Sink:
 *    BadSink : Remove element from list
 * Flow Variant: 01 Baseline
 *
 * */

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

static linkedList *linkedListPrev = NULL;
static linkedList *linkedListNext = NULL;

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

static void initLinkedList(linkedList *head, badStruct *data)
{
    head->next = head;
    head->prev = head;
    data->list.next = head->next;
    data->list.prev = head->prev;
    head->next = &data->list;
    head->prev = &data->list;
}

static void unlinkNode(badStruct *data)
{
    /* Safety fix: validate pointers before dereferencing during list removal */
    if (data == NULL || data->list.prev == NULL || data->list.next == NULL)
    {
        return;
    }
    linkedListPrev = data->list.prev;
    linkedListNext = data->list.next;
    linkedListPrev->next = linkedListNext;
    linkedListNext->prev = linkedListPrev;
}

static void readDiscardFromSocket(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    char discardBuffer[sizeof(badStruct)];
    int recvResult = 0;

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
        /* Safety fix: receive into a separate buffer instead of overwriting linked list pointers */
        recvResult = recv(connectSocket, discardBuffer, (int)sizeof(discardBuffer), 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
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

#ifndef OMITBAD

void CWE123_Write_What_Where_Condition__connect_socket_01_bad()
{
    badStruct data;
    linkedList head;

    initLinkedList(&head, &data);
    readDiscardFromSocket();
    unlinkNode(&data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    badStruct data;
    linkedList head;

    initLinkedList(&head, &data);
    unlinkNode(&data);
}

void CWE123_Write_What_Where_Condition__connect_socket_01_good()
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
    CWE123_Write_What_Where_Condition__connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE123_Write_What_Where_Condition__connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
