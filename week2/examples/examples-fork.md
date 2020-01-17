## Example-1
 
 ```c
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() { 
   // make two process which run same program after this instruction 
   fork(); 
   printf("Hello world!\n"); 
   return 0;
}
 ```
 
## Example-2

```c
#include <stdio.h> 
#include <sys/types.h> 
int main() { 
    fork(); 
    fork(); 
    fork(); 
    printf("hello\n"); 
    return 0; 
}
```

## Example-3

```c
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
void forkexample() { 
    // child process because return value zero 
         if (fork() == 0) 
                 printf("Hello from Child!\n"); 
                   
    // parent process because return value non-zero. 
          else
                 printf("Hello from Parent!\n"); 
} 
 
int main() { 
	forkexample(); 
        return 0; 
} 
```

## Example-4

```c

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
void forkexample() { 
    int x = 1; 
  
    if (fork() == 0) 
        printf("Child has x = %d\n", ++x); 
    else
        printf("Parent has x = %d\n", --x); 
} 
int main() { 
    forkexample(); 
    return 0; 
} 

```
