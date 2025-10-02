# Lab: Swapping

To see swapping in action, we need to use memory. There is a simple program which aggressively writes 0s 1MB at a time in [`zeros.c`](zeros.c) (opened in the top-left).

Go ahead and compile it:

```
gcc -Wall zeros.c -o zeros
```

Start VMStat like before:

```
vmstat 1
```

Carefully watch the terminal where VMStat is running and then press the button below to run the program and pass in the parameter 1000:

```
Allocated 100 MB
Allocated 200 MB
Allocated 300 MB
Allocated 400 MB
Allocated 500 MB
Allocated 600 MB
Allocated 700 MB
Allocated 800 MB
Allocated 900 MB
Allocated 1000 MB
```

**Reminder**: When you want to stop VMStat, press Ctrl and C

> **Reminder of important columns**
> * **`swpd`**: The amount of virtual memory used
> * **`free`**: The amount of idle memory
> * **`si`**: Amount of memory swapped in from disk (/s)
> * **`so`**: Amount of memory swapped to disk (/s)

### Example of Interpreting the Output

Here are three rows of an example run, the first row was reported before starting the program, the second row was reported while the program was running, and the third row was after the program has stopped:

```
procs -----------memory---------- ---swap-- 
 r  b   swpd   free   buff  cache   si   so  
 4  4      8 716468      0  36224   76    0     //before run
 2  0 182320    180      0    352  128 201148   //program running
 2  0  17056 764980      0   6160 1252 106840   //after program ran
```

You can see that the program consumed a lot of `free` space, ballooning the amount of virtual memory used (`swpd`).

Because the program depleted the physical memory, you can also see that the Operating System had to swap out (`so`) the pages that were already in the swap space.

You can also see that the operating system pre-emptively swapped back in (`si`) some of the pages once the program was finished.

#### Questions

**Which of the following statements were true when the program zero was running? There may be more than one.**
- [ ] The amount of free memory went up.
- [ ] The amount of free memory went down.
- [ ] Pages were swapped in.
- [ ] Pages were swapped out.
