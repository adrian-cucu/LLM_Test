/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE459_Incomplete_Cleanup__char_01.c
Label Definition File: CWE459_Incomplete_Cleanup.label.xml
Template File: point-flaw-01.tmpl.c
*/
#ifndef _WIN32
#define _XOPEN_SOURCE 700
#endif
#include "std_testcase.h"
#include <fcntl.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#define UNLINK _unlink
#define FDOPEN fdopen
#define CLOSE _close
#define MKSTEMP _mkstemp
/* Mutate the caller's template; do not copy it into a fixed local buffer. */
static int _mkstemp(char *name)
{
    if (_mktemp_s(name, strlen(name) + 1) != 0) { return -1; }
    return _open(name, _O_RDWR | _O_CREAT | _O_EXCL, _S_IREAD | _S_IWRITE);
}
#else
#include <unistd.h>
#define UNLINK unlink
#define FDOPEN fdopen
#define CLOSE close
#define MKSTEMP mkstemp
#endif

static void writeTemporaryFile(char *filename, int removeFile)
{
    int descriptor = MKSTEMP(filename);
    FILE *stream;
    if (descriptor == -1) { return; }
    stream = FDOPEN(descriptor, "w");
    if (stream != NULL)
    {
        fprintf(stream, "Temporary file");
        fclose(stream);
    }
    else
    {
        /* fdopen transfers ownership only when it succeeds. */
        CLOSE(descriptor);
    }
    if (removeFile)
    {
        /* Also remove the created file if conversion to a stream failed. */
        UNLINK(filename);
    }
}
#ifndef OMITBAD
void CWE459_Incomplete_Cleanup__char_01_bad()
{
    char filename[] = "badXXXXXX";
    writeTemporaryFile(filename, 0);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    char filename[] = "goodXXXXXX";
    writeTemporaryFile(filename, 1);
}
void CWE459_Incomplete_Cleanup__char_01_good()
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
    CWE459_Incomplete_Cleanup__char_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE459_Incomplete_Cleanup__char_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
