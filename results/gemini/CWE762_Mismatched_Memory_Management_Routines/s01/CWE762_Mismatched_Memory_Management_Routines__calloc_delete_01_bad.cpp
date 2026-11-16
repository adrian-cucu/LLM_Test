/*
 * @description Mismatched Memory Management Routines
 *
 * */

#include "std_testcase.h"

namespace CWE762_Mismatched_Memory_Management_Routines__calloc_delete_01
{

#ifndef OMITBAD

static char *duplicate_cstr(const char *src)
{
    const char *safeSrc = (src != NULL) ? src : "";
    char *copy = (char *)calloc(strlen(safeSrc) + 1, sizeof(char));
    if (copy == NULL)
    {
        exit(-1);
    }
    strcpy(copy, safeSrc);
    return copy;
}

class BadClass
{
    public:
        explicit BadClass(const char *name)
            : name(duplicate_cstr(name))
        {
        }

        ~BadClass()
        {
            /* Safety fix: use free() to match calloc() allocation instead of delete */
            free(name);
            name = NULL;
        }

        BadClass(const BadClass &badClassObject)
            : name(duplicate_cstr(badClassObject.name))
        {
        }

        BadClass& operator=(const BadClass &badClassObject)
        {
            if (&badClassObject != this)
            {
                /* Safety fix: allocate new copy first and free previous buffer to avoid memory leak */
                char *newName = duplicate_cstr(badClassObject.name);
                free(this->name);
                this->name = newName;
            }
            return *this;
        }

        void printName() const
        {
            printLine(name);
        }

    private:
        char *name;
};

void bad()
{
    BadClass badClassObject("BadClass");
    badClassObject.printName();
}

#endif /* OMITBAD */

} /* close namespace */

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */

#ifdef INCLUDEMAIN

using namespace CWE762_Mismatched_Memory_Management_Routines__calloc_delete_01; /* so that we can use good and bad easily */

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
