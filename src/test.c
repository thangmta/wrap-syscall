/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** test.c
** A test application to be used for wrapping glibc function calls
**
**
** Author: Saman Barghi <saman.b@gmail.com>
** -------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



int main()
{

    write(0, "Hello, Kernel!\n", 15);
    printf("Hello, World!\n");

    char *str;
    str = (char*) malloc(20);
    strcpy(str, "FPT HA NOI-VIETNAM");
    printf("%s\n", str);
    free(str);

    return 0;
}



