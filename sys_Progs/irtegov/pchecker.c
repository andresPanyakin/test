#include <stdio.h>

int main() { 
 #if defined(_LIBC_REENTRANT) 
   printf("_LIBC_REENTRANT defined as %d\n", _LIBC_REENTRANT); 
 #endif 

 #if defined(_REENTRANT) 
   printf("_REENTRANT defined as %d\n", _REENTRANT); 
 #endif 

 #if defined(_TS_ERRNO) 
   printf("_TS_ERRNO defined as %d\n", _TS_ERRNO); 
 #endif 

 #if defined(_POSIX_C_SOURCE)
   printf("_POSIX_C_SOURCE defined as %d\n", _POSIX_C_SOURCE); 
 #endif 
}
