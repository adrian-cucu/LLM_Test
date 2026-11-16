/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE367_TOC_TOU__access_01.c
Label Definition File: CWE367_TOC_TOU.label.xml
Template File: point-flaw-01.tmpl.c
*/
#include "std_testcase.h"
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#define OPEN _open
#define WRITE _write
#define CLOSE _close
#define ACCESS _access
#define O_RDWR _O_RDWR
#define W_OK 02
#else
#include <unistd.h>
#define OPEN open
#define WRITE write
#define CLOSE close
#define ACCESS access
#endif

#define BAD_SINK_STRING "Bad Sink..."
#define GOOD_SINK_STRING "Good Sink..."

static void writeFile(const char *text, int checkAccess)
{
    char filename[100] = "";
    size_t length;
    int fileDesc;
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        printLine("fgets() failed");
        filename[0] = '\0';
    }
    length = strlen(filename);
    if (length > 0)
    {
        filename[length - 1] = '\0';
    }
    /* Preserve the access-check variant; open() must still be checked. */
    if (checkAccess && ACCESS(filename, W_OK) == -1)
    {
        exit(1);
    }
    fileDesc = OPEN(filename, O_RDWR);
    if (fileDesc == -1)
    {
        exit(1);
    }
    if (WRITE(fileDesc, text, (unsigned int)strlen(text)) == -1)
    {
        /* Release the descriptor on the write-error path as well. */
        CLOSE(fileDesc);
        exit(1);
    }
    CLOSE(fileDesc);
}

#ifndef OMITBAD
void CWE367_TOC_TOU__access_01_bad()
{
    writeFile(BAD_SINK_STRING, 1);
}
#endif
#ifndef OMITGOOD
static void good1(void)
{
    writeFile(GOOD_SINK_STRING, 0);
}
void CWE367_TOC_TOU__access_01_good()
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
    CWE367_TOC_TOU__access_01_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE367_TOC_TOU__access_01_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
