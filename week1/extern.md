# Extern Variables.

* When we declare a variable X as extern. We are informing the compiler that somewhere in all the included files, there is a variable X.
* This is like declaring a function. You haven’t yet allocated memory or done any preparation for the function. You have only created the function definition.
* You can declare multiple times, however you can define only once.
* extern extends the visibility of X and you can use X in your program - This means some other code can change a variable and you can access that variable in your code.
* This is useful in system calls, where some piece of the kernel code can set some variables and you can access them to verify if operation succeeded.

## Examples:

1.

```c
int var; //var is a global variable here, it can be accessed inside the functions inside these files
int main(void) 
{ 
  var = 10; 
  return 0; 
} 

```

2.

```c

//this is informing the compiler that there is a variable called var somewhere outside
//this doesn't create any memory for the variable
extern int var; 
//this is like declaring a function as shown below
int add(int a,int b); 
int main(void) 
{ 
  var = 10; //this will result in a compiler error. The variable has been declared but not defined hence not available
  return 0;
} 
```

3. Capping it all off

Create a headerfile - `ihavevar.h`

```c
int var=10;
```

Create a file ex3.c

```c

#include"ihavevar.h"
#include<stdio.h>
//this is informing the compiler that there is a variable called var somewhere outside
////this doesn't create any memory for the variable
extern int var;
extern int not_var;
////this is like declaring a function as shown below
int add(int a,int b);
//
int main(void)
{
  printf("var = %d\n", var);//this will try getting the value from all included files
  
  //printf("not_var = %d\n", not_var);//this will try getting not_var from all included files. Try uncommenting this line to see if it works
  return 0;
}


```

### errno

Example of useful extern variable set during system calls.

Wiki - https://en.wikipedia.org/wiki/Errno.h

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno ; //set in errno.h

int main () {
   FILE *fp;

   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      fprintf(stderr, "Value of errno: %d\n", errno); 
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
   } else {
      fclose(fp);
   }
   
   return(0);
}
```
