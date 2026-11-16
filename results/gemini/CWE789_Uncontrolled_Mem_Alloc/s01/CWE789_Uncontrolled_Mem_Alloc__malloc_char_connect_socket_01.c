/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE789_Uncontrolled_Mem_Alloc__malloc_char_connect_socket_01.c
Label Definition File: CWE789_Uncontrolled_Mem_Alloc__malloc.label.xml
Template File: sources-sinks-01.tmpl.c
*/
/*
 * @description
 * CWE: 789 Uncontrolled Memory Allocation
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Small number greater than zero
 * Sinks:
 *    GoodSink: Allocate memory with malloc() and check the size of the memory to be allocated
 *    BadSink : Allocate memory with malloc(), but incorrectly check the size of the memory to be allocated
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
#define CHAR_ARRAY_SIZE (3 * sizeof(size_t) + 2)

#define HELLO_STRING "hello"
#define GOOD_ALLOC_SIZE 20
#define MAX_ALLOC_SIZE 100

static size_t read_size_from_socket(void)
{
    size_t result = 0;
#ifdef _WIN32
    WSADATA wsaData;
    int wsaDataInit = 0;
#endif
    int recvResult = 0;
    struct sockaddr_in service;
    SOCKET connectSocket = INVALID_SOCKET;
    char inputBuffer[CHAR_ARRAY_SIZE] = "";

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
        recvResult = recv(connectSocket, inputBuffer, CHAR_ARRAY_SIZE - 1, 0);
        if (recvResult == SOCKET_ERROR || recvResult <= 0)
        {
            break;
        }
        inputBuffer[recvResult] = '\0';
        result = strtoul(inputBuffer, NULL, 0);
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
    return result;
}

static void allocate_and_print_hello(size_t allocSize)
{
    char *myString = NULL;

    /* Safety fix: enforce both lower and upper bounds on allocation size before malloc() */
    if (allocSize > strlen(HELLO_STRING) && allocSize < MAX_ALLOC_SIZE)
    {
        myString = (char *)malloc(allocSize * sizeof(char));
        if (myString == NULL)
        {
            exit(-1);
        }
        snprintf(myString, allocSize, "%s", HELLO_STRING);
        printLine(myString);
        free(myString);
    }
    else
    {
        printLine("Input is less than the length of the source string or too large");
    }
}

#ifndef OMITBAD

void CWE789_Uncontrolled_Mem_Alloc__malloc_char_connect_socket_01_bad()
{
    size_t data = read_size_from_socket();
    allocate_and_print_hello(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    size_t data = GOOD_ALLOC_SIZE;
    allocate_and_print_hello(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    size_t data = read_size_from_socket();
    allocate_and_print_hello(data);
}

void CWE789_Uncontrolled_Mem_Alloc__malloc_char_connect_socket_01_good()
{
    goodG2B();
    goodB2G();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE789_Uncontrolled_Mem_Alloc__malloc_char_connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE789_Uncontrolled_Mem_Alloc__malloc_char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
