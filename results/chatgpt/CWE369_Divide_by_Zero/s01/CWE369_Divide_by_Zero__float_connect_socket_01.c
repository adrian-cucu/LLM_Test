/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE369_Divide_by_Zero__float_connect_socket_01.c
Label Definition File: CWE369_Divide_by_Zero__float.label.xml
Template File: sources-sinks-01.tmpl.c
*/
#include "std_testcase.h"
#include <math.h>
#include <limits.h>
#include <float.h>
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
#define CHAR_ARRAY_SIZE 20
#define IP_ADDRESS "127.0.0.1"

static float readDivisor(void)
{
    float data = 0.0F;
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in service;
    char input[CHAR_ARRAY_SIZE];
    int received;
    double parsed;
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    {
        return data;
    }
#endif
    do
    {
        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connection == INVALID_SOCKET) { break; }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        service.sin_port = htons(TCP_PORT);
        if (connect(connection, (struct sockaddr *)&service, sizeof(service)) == SOCKET_ERROR) { break; }
        received = recv(connection, input, sizeof(input) - 1, 0);
        if (received <= 0) { break; }
        input[received] = '\0';
        parsed = strtod(input, NULL);
        /* Avoid narrowing a finite value outside the float range. */
        if (isfinite(parsed) && (parsed > FLT_MAX || parsed < -FLT_MAX)) { break; }
        data = (float)parsed;
    } while (0);
    if (connection != INVALID_SOCKET) { CLOSE_SOCKET(connection); }
#ifdef _WIN32
    WSACleanup();
#endif
    return data;
}

static void printQuotient(float divisor)
{
    double quotient;
    /* Do not divide by zero or convert a nonrepresentable value to int. */
    if (divisor == 0.0F || isnan(divisor))
    {
        printLine("This would result in a divide by zero");
        return;
    }
    quotient = trunc(100.0 / divisor);
    if (quotient < INT_MIN || quotient > INT_MAX)
    {
        printLine("Result is outside the int range");
        return;
    }
    printIntLine((int)quotient);
}
#ifndef OMITBAD
void CWE369_Divide_by_Zero__float_connect_socket_01_bad()
{
    printQuotient(readDivisor());
}
#endif
#ifndef OMITGOOD
static void goodG2B(void)
{
    printQuotient(2.0F);
}
static void goodB2G(void)
{
    float data = readDivisor();
    if (fabs(data) > 0.000001)
    {
        printQuotient(data);
    }
    else
    {
        printLine("This would result in a divide by zero");
    }
}
void CWE369_Divide_by_Zero__float_connect_socket_01_good()
{
    goodG2B();
    goodB2G();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE369_Divide_by_Zero__float_connect_socket_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE369_Divide_by_Zero__float_connect_socket_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
