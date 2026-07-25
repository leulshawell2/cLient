#include <stdio.h>
#include <stdlib.h>


#define panic(format, ...) \
        fprintf(stderr, "PANIC at %s:%d in %s(): " format "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        exit(EXIT_FAILURE); 
