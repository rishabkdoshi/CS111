[original src](https://www.thegeekstuff.com/2012/08/gprof-tutorial/)

### PPROF example

Example usage of PPROF. 

1. Create the files `test_gprof.c` and `test_gprof_new.c`

```c
//test_gprof.c
#include<stdio.h>

void new_func1(void);

void func1(void)
{
    printf("\n Inside func1 \n");
    int i = 0;

    for(;i<0xffffffff;i++);
    new_func1();

    return;
}

static void func2(void)
{
    printf("\n Inside func2 \n");
    int i = 0;

    for(;i<0xffffffaa;i++);
    return;
}

int main(void)
{
    printf("\n Inside main()\n");
    int i = 0;

    for(;i<0xffffff;i++);
    func1();
    func2();

    return 0;
}
```

```c
//test_gprof_new.c
#include<stdio.h>

void new_func1(void)
{
    printf("\n Inside new_func1()\n");
    int i = 0;

    for(;i<0xffffffee;i++);

    return;
}
```


2. Compile the program with `-lprofiler` flag, this will help create instrumentation data when your program is run.

```
gcc -Wall -lprofiler test_gprof.c test_gprof_new.c -o test_gprof_lprofiler

```

3. Run the below command, this will run your binary and add profiling information into the file `profileInfo.prof`

```
env CPUPROFILE=profileInfo.prof ./test_gprof_lprofiler
```

4. To analyze the profiling information generated you can use the pprof tool, by running the below command.

```
pprof --text ./test_gprof_lprofiler profileInfo.prof
```

This will output the profiling information.

How to interpret the [information](https://gperftools.github.io/gperftools/cpuprofile.html)?
