# GNU Debugger - Learning By Doing

## Example 1 - Debugging using GDB

Extended from this file [here](https://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html)

create a file `broken.cpp`

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int ComputeFactorial(int number) {
  int fact = 0;

  for (int j = 1; j <= number; j++) {
    fact = fact * j;
  }

  return fact;
}

double ComputeSeriesValue(double x, int n) {
  double seriesValue = 0.0;
  double xpow = 1;

  for (int k = 0; k <= n; k++) {
    seriesValue += xpow / ComputeFactorial(k);
    xpow = xpow * x;
  }

  return seriesValue;
}

int main() {
  cout << "This program is used to compute the value of the following series : " << endl;

  cout << "(x^0)/0! + (x^1)/1! + (x^2)/2! + (x^3)/3! + (x^4)/4! + ........ + (x^n)/n! " << endl;

  cout << "Please enter the value of x : " ;
  
  double x;
  cin >> x;

  int n;
  cout << endl << "Please enter an integer value for n : " ;
  cin >> n;
  cout << endl;

  double seriesValue = ComputeSeriesValue(x, n);
  cout << "The value of the series for the values entered is " 
	<< seriesValue << endl;

  return 0;
}

```
* Compile and run the file, inspect the output of the file. Something wrong?

#### Debugging broken.cpp

* Compile the file with the -g flag 
`g++ -g broken.cpp -o broken`

* Start the debugger with this executable (broken) as below:

`gdb broken`

* Try out the below commands

  1. `info files`
  2. `info functions`

* Lets start debugging from main(). Set a breakpoint at the main function.
This can be done in any of the below ways:

  1. `b main`
  2. `b 28`
  3. `breakpoint broken.cpp:28`
  
* Inspect the available breakpoints : `info break`

* Start execution by typing in `r` or `run`. You should see an output like

```
29	  cout << "This program is used to compute the value of the following series : " << endl;
```

* The execution has paused at line no. 29. We can look at the code near this point by typing in `l` or `list`

* Now lets go to the next line of the code, by pressing `n` or `next`. You will see the below output:

```
This program is used to compute the value of the following series : 
31	  cout << "(x^0)/0! + (x^1)/1! + (x^2)/2! + (x^3)/3! + (x^4)/4! + ........ + (x^n)/n! " << endl;
```
The first line is the result of execution of line. 29 and the execution has now paused at line 31.

* Set a breakpoint on line 43 now : `b 43`

* See all the breakpoints that are available now: `info breakpoints`

* Now gdb lets you <b>continue</b> to the next breakpoint by typing : `c` or `continue`. 
When you do this, the execution will continue till line 43. Enter the values of x as (2) and n as (3).

* Now you are at a line where a function is being invoked. You can step into the function by typing in `s` or `step`.

* Now, you have stepped into the function. You want to look at where you are, Remember that the `l` command does that.

* Lets set a breakpoint at the line inside the for loop as that is where the execution occurs. : `b 21`

* How do I continue to this breakpoint? `c`

* Lets print out the value of the variable 'seriesValue'. This can be done by `print seriesValue`.

* You can print out all the local variables by typing `info locals`.

* All values seem to be right. Maybe the issue stems from the `ComputeFactorial` function.

* Lets set a breakpoint at the `ComputeFactorial` function : `b ComputeFactorial`

* See all the breakpoints that are available now: `info breakpoints`

* Continue execution to `ComputeFactorial`. 

* Look at the code by typing in `l`

* Check that the passed in argument values are exactly what are expected : `print number`

* All looks good, Now, we want to see, what this function is returning. Set a breakpoint near the return statement.
`b 13`

* Lets continue execution to this point `c`.

* Print out the value of the fact value `print fact`.

* Continue execution, where will the debugger go? 

* print out local values at this point `info locals`. Can you identify what went wrong?

* Delete one of the breakpoints which maynot be useful now : `delete <breakpoint_num>`

* Now that we have understood the issue (fact is returning 0 instead 1), we can disable all breakpoints, by typing in `disable`.
If you like, you can also specify which particular breakpoint to disable: `disable <breakpoint_num>`

* Continue execution till the program exits.

* Fix the program, compile and run it , inspect the output.

* There you have learnt debugging using GDB. 

## Example 2 - Backtrace

Extended from this file [here](https://www.thegeekstuff.com/2014/01/gdb-backtrace/)

```cpp
#include<stdio.h>	 	 
void func1();	 	 
void func2();	 	 

int main() {	 	 
 int i=10;	 	 
 func1();	 	 
 printf("In Main(): %d\n",i);	 	 
 i = 100;
 printf("In Main(): %d\n",i);	 	 
}

void func1() {	 	 
 int n=20;	 	 
 printf("In func1(): %d\n",n);	 	 
 func2();	 	 
 n = 400;
 printf("In func1(): %d\n",n); 
}

void func2() {	 	 
 int n = 30;	 	 
 printf("In func2() : %d\n",n);	 	 
 n = 900;
 printf("In func2() : %d\n",n);	 	 
}
```

* Set breakpoints at line 23, 18, 10 
* Start the run of the program: `r`
* Look at the local variables available : `info locals`

* Type the backtrace command : `backtrace` or `bt`. This will result in below output:

```
#0  func2 () at bt.c:23
#1  0x000000000040055e in func1 () at bt.c:16
#2  0x00000000004004fb in main () at bt.c:7
```

This just shows you the current program stack. You can switch between frames by using the command `frame <frame_num>`

* Switch to frame 1: `frame 1`. Inspect the local variables here .
* Try printing value of `i` here: `print i`. Did it work? Why?
* Switch to frame 2: `frame 2`. Inspect the local variables here. 
* Try printing value of `n` here: `print i`. Did it work? Why?
* Switch back to frame 0: `frame 0`
* Continue execution: `c`
* Backtrace again
* Switch across frames and look at the variables here
