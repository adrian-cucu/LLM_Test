/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE377_Insecure_Temporary_File__char_mktemp_01.c
Label Definition File: CWE377_Insecure_Temporary_File.label.xml
Template File: point-flaw-01.tmpl.c
*/
#ifndef _WIN32
#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include "std_testcase.h"
#include <wchar.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#define OPEN _open
#define CLOSE _close
#define MKTEMP mktemp
#define MKSTEMP _mkstemp
#define O_RDWR _O_RDWR
#define O_CREAT _O_CREAT
#define O_EXCL _O_EXCL
#define S_IREAD _S_IREAD
#define S_IWRITE _S_IWRITE
/* Generate the name in the caller's buffer and supply creation permissions. */
static int _mkstemp(char *name)
{
    size_t capacity = strlen(name) + 1;
    if (_mktemp_s(name, capacity) != 0) { return -1; }
    return _open(name, _O_RDWR | _O_CREAT | _O_EXCL, _S_IREAD | _S_IWRITE);
}
#else
#include <unistd.h>
#define OPEN open
#define CLOSE close
#define MKTEMP mktemp
#define MKSTEMP mkstemp
#ifndef S_IREAD
#define S_IREAD S_IRUSR
#define S_IWRITE S_IWUSR
#endif
#endif

static void closeTemporaryFile(int descriptor)
{
    if (descriptor != -1)
    {
        printLine("Temporary file was opened...now closing file");
        CLOSE(descriptor);
    }
}
#ifndef OMITBAD
void CWE377_Insecure_Temporary_File__char_mktemp_01_bad()
{
    char pattern[] = "fnXXXXXX";
    char *filename = MKTEMP(pattern);
    /* Some implementations signal failure with an empty name. */
    if (filename == NULL || filename[0] == '\0') { exit(1); }
    printLine(filename);
    closeTemporaryFile(OPEN(filename, O_RDWR | O_CREAT, S_IREAD | S_IWRITE));
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    char filename[] = "/tmp/fileXXXXXX";
    int descriptor = MKSTEMP(filename);
    printLine(filename);
    closeTemporaryFile(descriptor);
}
void CWE377_Insecure_Temporary_File__char_mktemp_01_good()
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
    CWE377_Insecure_Temporary_File__char_mktemp_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE377_Insecure_Temporary_File__char_mktemp_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
