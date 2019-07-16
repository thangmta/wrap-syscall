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
#include <string.h>
#include <stdlib.h>
#include <cstring>



/* create pointers for real glibc functions */
extern "C" ssize_t __real_write(int fd, const void *buf, size_t count);
extern "C" int __real_puts(const char* str);
extern "C" void *__real_malloc(size_t size);


/* wrapping write function */


extern "C" ssize_t __wrap_write (int fd, const void *buf, size_t count)
{
    /* printing out the number of characters */
    printf("write:chars#:%lu\n", count);

    /* call the real glibc function and return the result */
    ssize_t result = __real_write(fd, buf, count);
    return result;
}

/* wrapping puts function */
extern "C" int __wrap_puts (const char* str)
{
    /* printing out the number of characters */
    printf("puts:chars#:%lu\n", strlen(str));

    /* call the real glibc function and return the result */
    int result = __real_puts(str);
    return result;
}


extern "C" void *__wrap_malloc (size_t c)
{
  printf ("malloc called with %ld\n", c);
  return __real_malloc (c);
}


int main()
{

    write(0, "Hello, Kernel!\n", 15);
    // printf("Hello, World!\n");

    char *str;
    str = (char*) malloc(20);
    strcpy(str, "FPT HA NOI-VIETNAM");
    // printf("%s\n", str);
    free(str);

    return 0;
}



