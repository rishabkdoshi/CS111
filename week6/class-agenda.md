
* TA howards [slides](https://docs.google.com/presentation/d/11VwDmTVMjL0zejMXSgd96GYEyyP43uNmw6F2HQIgW10/edit?usp=sharing)

* project 2b [overview](http://web.cs.ucla.edu/~harryxu/courses/111/winter20/ProjectGuide/P2B.html)

```
QUESTION 2.3.1 - Cycles in the basic list implementation:
Where do you believe most of the cycles are spent in the 1 and 2-thread list tests ?

Why do you believe these to be the most expensive parts of the code?

Where do you believe most of the time/cycles are being spent in the high-thread spin-lock tests?

Where do you believe most of the time/cycles are being spent in the high-thread mutex tests?

It should be clear why the spin-lock implementation performs so badly with a large number of threads. But the mutex implementation should not have this problem. You may have some theories about why these algorithms scale so poorly. But theories are only theories, and the prime directive of performance analysis is that theoretical conclusions must be confirmed by hard data.

QUESTION 2.3.2 - Execution Profiling:
Where (what lines of code) are consuming most of the cycles when the spin-lock version of the list exerciser is run with a large number of threads?

Why does this operation become so expensive with large numbers of threads?

QUESTION 2.3.3 - Mutex Wait Time:
Look at the average time per operation (vs. # threads) and the average wait-for-mutex time (vs. #threads).
Why does the average lock-wait time rise so dramatically with the number of contending threads?
Why does the completion time per operation rise (less dramatically) with the number of contending threads?
How is it possible for the wait time per operation to go up faster (or higher) than the completion time per operation?

QUESTION 2.3.4 - Performance of Partitioned Lists
Explain the change in performance of the synchronized methods as a function of the number of lists.
Should the throughput continue increasing as the number of lists is further increased? If not, explain why not.
It seems reasonable to suggest the throughput of an N-way partitioned list should be equivalent to the throughput of a single list with fewer (1/N) threads. Does this appear to be true in the above curves? If not, explain why not.
```

### Building blocks
Performance instrumentation tools.

We need a performance instrumentation tool to understand which parts of the program take the longest.

example of performance instrumentation - 
How to Profile a C program in Linux using GNU gprof - https://www.thegeekstuff.com/2012/08/gprof-tutorial/

Doesn't work for multithreaded environment, lets install googles performance tool

install steps:
https://github.com/gperftools/gperftools/blob/master/INSTALL#L375

```
git clone https://github.com/gperftools/gperftools
./configure --prefix=PATH
make
make install
```

pprof example:
```
gcc -Wall -lprofiler test_gprof.c test_gprof_new.c -o test_gprof_lprofiler
pprof --text ./test_gprof_lprofiler gprof.prof
```
