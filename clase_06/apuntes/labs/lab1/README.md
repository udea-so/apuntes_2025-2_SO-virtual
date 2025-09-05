# Implementing First-Come-First-Serve (FCFS) Scheduling

The **First-Come-First-Serve (FCFS)** scheduling algorithm is the simplest scheduling algorithm based on the "first come, first serve" principle. Processes are executed in the order they arrive in the ready queue.

We’ll use the file to the left, `fcfs_lab.c`, to implement the **FCFS scheduling algorithm** and calculate the average waiting time and turnaround time for a set of processes.



Our program will request the following input from the user:
* Number of processes (`n`).
* Duration of each process (`duration[]`).

After implementing a simple FCFS algorithm, our program will return.
* Waiting time for each process (`waiting_time[]`).
* Turnaround time for each process (`turnaround_time[]`).
* Average waiting time.
* Average turnaround time.


We’ll start by declaring our necessary header files for receiving input.

```c
#include <stdio.h>
```

Declare our variable and array to hold the Number of processes, `n`, and process durations,(`duration[]`), from the user.

```c
int n; // number of processes
int duration[100], waiting_time[100], turnaround_time[100];
```

Request and assign the input from our user.

```c
printf("Enter the number of processes: ");
scanf("%d", &n);

for(int i = 0; i < n; i++) {
    printf("Enter duration for process %d: ", i+1);
    scanf("%d", &duration[i]);
}
```

Now, we’ll initialize a waiting time counter for our processes.

```c
waiting_time[0] = 0;
```

Using a for loop, we can calculate the wait time and turnaround time for each process entered.

```c
for(int i = 1; i < n; i++) {
    waiting_time[i] = duration[i-1] + waiting_time[i-1];
    turnaround_time[i] = duration[i] + waiting_time[i];
}
```

We can also calculate the total wait time and turnaround time for the entire set of processes using a for loop.

```c
for(int i = 0; i < n; i++) {
    total_waiting_time += waiting_time[i];
    total_turnaround_time += turnaround_time[i];
}
```

We’ll display the scheduling results of the set of processes as well as the average waiting and turnaround time.

```c
printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i+1, duration[i], waiting_time[i], turnaround_time[i]);
    }
```

Finally, we’ll return 0 to mark the successful end of our program.

```c
  return 0;
}
```

Codigo: [(fcfs_lab.c](fcfs_lab.c)

Compilation

```
gcc fcfs_lab.c -o fcfs_lab
```

Run:

```
./fcfs_lab
```

Try out different numbers of processes and durations. Examine the how the waiting and turnaround times are affected.

For example, if we try the following input values:

```
Enter the number of processes: 3
Enter duration for process 1: 10
Enter duration for process 2: 5
Enter duration for process 3: 8
```

We should receive the following result.

```
Process     Duration     Waiting Time     Turnaround Time
1           10           0                10
2           5            10               15
3           8            15               23

Average Waiting Time: 8.33
Average Turnaround Time: 16.00
```

Congratulations on implementing a simple First-Come-First-Serve (FCFS) scheduling algorithm! This algorithm is foundational in understanding process scheduling in operating systems.

By now, we should have a clear understanding of how processes are scheduled based on their arrival time and how to calculate their waiting and turnaround times.

## Solution

```c
#include <stdio.h>

int main() {
    int n; // number of processes
    int duration[100], waiting_time[100], turnaround_time[100];
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Input number of processes and their durations
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter duration for process %d: ", i+1);
        scanf("%d", &duration[i]);
    }

    // Initialize waiting time for the first process
    waiting_time[0] = 0;

    // Calculate waiting time and turnaround time for each process
    for(int i = 1; i < n; i++) {
        waiting_time[i] = duration[i-1] + waiting_time[i-1];
        turnaround_time[i] = duration[i] + waiting_time[i];
    }

    // Calculate total waiting time and total turnaround time
    for(int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display the results
    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i+1, duration[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time/n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time/n);

    return 0;
}
```

The FCFS scheduling algorithm is straightforward. Processes are executed in the order they arrive, without preemption.

**Input Phase**:

We start by taking the number of processes (n) as input.
For each process, we input its duration.

**Initialization**:

The waiting time for the first process is always 0 because it’s the first to execute.

**Calculation Phase**:

For each subsequent process, its waiting time is the sum of the duration of the previous process and the waiting time of the previous process.

The turnaround time for a process is its waiting time plus its duration.

**Output Phase**:

We then display the duration, waiting time, and turnaround time for each process.
Finally, we calculate and display the average waiting time and average turnaround time for all processes.
By following this algorithm, we can effectively simulate the FCFS scheduling mechanism and understand its implications on process waiting times and turnaround times.

