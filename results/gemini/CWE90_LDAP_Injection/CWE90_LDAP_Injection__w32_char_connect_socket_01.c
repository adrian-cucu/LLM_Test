/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE90_LDAP_Injection__w32_char_connect_socket_01.c
Label Definition File: CWE90_LDAP_Injection__w32.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 90 LDAP Injection
 * BadSource: connect_socket Read data using a connect socket (client side)
 * GoodSource: Use a fixed string
 * Sink:
 *    BadSink : data concatenated into LDAP search, which could result in LDAP Injection
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

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
#define DATA_BUFFER_SIZE 256
#define FILTER_BUFFER_SIZE 256
#define GOOD_LDAP_NAME "Doe, XXXXX"

#include <Winldap.h>

#pragma comment(lib, "wldap32")

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

static int escape_ldap_filter_value(const char *src, char *dst, size_t dstSize)
{
    size_t outIdx = 0;
    size_t i = 0;

    if (src == NULL || dst == NULL || dstSize == 0)
    {
        return 0;
    }

    for (i = 0; src[i] != '\0'; i++)
    {
        const char *escaped = NULL;
        switch (src[i])
        {
            case '\\': escaped = "\\5c"; break;
            case '*':  escaped = "\\2a"; break;
            case '(':  escaped = "\\28"; break;
            case ')':  escaped = "\\29"; break;
            default:   break;
        }

        if (escaped != NULL)
        {
            if (outIdx + 3 >= dstSize)
            {
                return 0;
            }
            dst[outIdx++] = escaped[0];
            dst[outIdx++] = escaped[1];
            dst[outIdx++] = escaped[2];
        }
        else
        {
            if (outIdx + 1 >= dstSize)
            {
                return 0;
            }
            dst[outIdx++] = src[i];
        }
    }
    dst[outIdx] = '\0';
    return 1;
}

static void execute_ldap_search(const char *cnValue)
{
    LDAP *pLdapConnection = NULL;
    ULONG connectSuccess = 0L;
    ULONG searchSuccess = 0L;
    LDAPMessage *pMessage = NULL;
    char escapedCn[DATA_BUFFER_SIZE] = "";
    char filter[FILTER_BUFFER_SIZE] = "";

    /* Safety fix: escape RFC 4515 LDAP filter metacharacters to prevent LDAP injection */
    if (!escape_ldap_filter_value(cnValue, escapedCn, sizeof(escapedCn)))
    {
        printLine("Invalid or overly long LDAP filter value");
        return;
    }

    _snprintf(filter, FILTER_BUFFER_SIZE - 1, "(cn=%s)", escapedCn);
    filter[FILTER_BUFFER_SIZE - 1] = '\0';

    pLdapConnection = ldap_initA("localhost", LDAP_PORT);
    if (pLdapConnection == NULL)
    {
        printLine("Initialization failed");
        exit(1);
    }
    connectSuccess = ldap_connect(pLdapConnection, NULL);
    if (connectSuccess != LDAP_SUCCESS)
    {
        printLine("Connection failed");
        ldap_unbind(pLdapConnection);
        exit(1);
    }
    searchSuccess = ldap_search_ext_sA(
                        pLdapConnection,
                        "base",
                        LDAP_SCOPE_SUBTREE,
                        filter,
                        NULL,
                        0,
                        NULL,
                        NULL,
                        LDAP_NO_LIMIT,
                        LDAP_NO_LIMIT,
                        &pMessage);
    if (searchSuccess != LDAP_SUCCESS)
    {
        printLine("Search failed");
        if (pMessage != NULL)
        {
            ldap_msgfree(pMessage);
        }
        ldap_unbind(pLdapConnection);
        exit(1);
    }
    if (pMessage != NULL)
    {
        ldap_msgfree(pMessage);
    }
    ldap_unbind(pLdapConnection);
}

#ifndef OMITBAD

void CWE90_LDAP_Injection__w32_char_connect_socket_01_bad()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;
    read_socket_append(data, DATA_BUFFER_SIZE);
    execute_ldap_search(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char dataBuffer[DATA_BUFFER_SIZE] = "";
    char *data = dataBuffer;
    snprintf(data, DATA_BUFFER_SIZE, "%s", GOOD_LDAP_NAME);
    execute_ldap_search(data);
}

void CWE90_LDAP_Injection__w32_char_connect_socket_01_good()
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
    CWE90_LDAP_Injection__w32_char_connect_socket_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE90_LDAP_Injection__w32_char_connect_socket_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
