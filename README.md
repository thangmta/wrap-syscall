Wrap system calls in Linux
============

Some code to demonstrate how to wrap system calls in Linux. Refer to
http://samanbarghi.com/blog/2014/09/05/how-to-wrap-a-system-call-libc-function-in-linux/
for more information.

    ├── bin
    ├── LICENSE
    ├── Makefile
    ├── README.md
    └── src
        ├── test.c
        ├── wrap-link.c
        └── wrap-preload.c



## case with c++
g++ -Wl,-wrap=malloc -Wl,-wrap=write -Wl,-wrap=puts apex_tc_008.cpp  -o test
and need to use  extern "C" 

#### case useing -wrap
$ gcc -c src/wrap-link.c -o bin/wrap-link.o
$ gcc -c src/test.c -o bin/test-link.o
$ gcc -Wl,-wrap,write -Wl,-wrap=write -Wl,-wrap=puts -Wl,-wrap,malloc bin/test-link.o bin/wrap-link.o -o bin/test-link-bin
$ ./bin/test-link-bin
write:chars#:15
Hello, Kernel!
puts:chars#:13
Hello, World!


//// #### Them vao test case apex_ts_008
Them vao Build.mk cua test case: make CALL_WRAP_FUNCTION=on

##if you want to call wrap glibc function (malloc, write, puts,...),
##   you should type "make CALL_WRAP_FUNCTION=on"
ifeq ($(CALL_WRAP_FUNCTION),on)
        ARM_LDOPTS += -Wl,-wrap=malloc
endif

//// #### code them vao apex_tc_008.cpp

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


void main()
{
	......

    write(0, "Hello, Kernel!\n", 15);
    // printf("Hello, World!\n");

    char *str;
    str = (char*) malloc(20);
    strcpy(str, "FPT HA NOI-VIETNAM");
    // printf("%s\n", str);
    free(str);
    TEST_END
    .......
}