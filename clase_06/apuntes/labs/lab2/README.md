# Implementing Shortest Job First (SJF) Scheduling Algorithm

The **Shortest Job First (SJF)** scheduling algorithm, also known as the Shortest Process Next (SPN), prioritizes processes based on their execution time. The process with the shortest execution time is chosen next. For this lesson, we’ll focus on the non-preemptive version of SJF.

We’ll use the file `sjf_lab.c` to implement the SJF scheduling algorithm and calculate the average waiting time and turnaround time for a set of processes.

Certainly! Let’s walk through the SJF scheduling algorithm with the provided code, step by step:

## Setting Up

Before we dive into the logic, we need to set up our environment. This involves including necessary header files and initializing our main function.

```c
#include <stdio.h>
```

## Declaring Variables

We’ll declare variables to store the number of processes, their execution times, waiting times, turnaround times, and process IDs.

```c
int n; // number of processes
int execution_time[100], waiting_time[100], turnaround_time[100], process_id[100];
float total_waiting_time = 0, total_turnaround_time = 0;
```

## Gathering User Input

Our program will prompt the user to enter the number of processes and the execution time for each process.


```c
printf("Enter the number of processes: ");
scanf("%d", &n);

for(int i = 0; i < n; i++) {
    printf("Enter execution time for process %d: ", i+1);
    scanf("%d", &execution_time[i]);
    process_id[i] = i+1;
}
```

## Sorting Processes

We’ll use the bubble sort algorithm to arrange the processes based on their execution times. This ensures that the process with the shortest execution time is scheduled first.


```c
for(int i = 0; i < n-1; i++) {
    for(int j = 0; j < n-i-1; j++) {
        if(execution_time[j] > execution_time[j+1]) {
             // Swap execution times
            int temp = execution_time[j];
            execution_time[j] = execution_time[j+1];
            execution_time[j+1] = temp;

                // Swap process IDs to keep them in sync with execution times
            int temp_id = process_id[j];
            process_id[j] = process_id[j+1];
            process_id[j+1] = temp_id;
        }
    }
}
```

## Calculating Waiting and Turnaround Times

Once sorted, we’ll calculate the waiting and turnaround times for each process. The waiting time for the first process is always zero, and its turnaround time is its execution time.


```c
waiting_time[0] = 0;
turnaround_time[0] = execution_time[0];
for(int i = 1; i < n; i++) {
    waiting_time[i] = execution_time[i-1] + waiting_time[i-1];
    turnaround_time[i] = execution_time[i] + waiting_time[i];
}
```

## Calculating Averages

We’ll sum up the waiting and turnaround times for all processes to later calculate the averages.


```c
for(int i = 0; i < n; i++) {
total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
}
```

## Displaying Results

Finally, we’ll display the sorted processes, their waiting times, turnaround times, and the averages.


```c
printf("Process\tExecution Time\tWaiting Time\tTurnaround Time\n");
for(int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", process_id[i], execution_time[i], waiting_time[i], turnaround_time[i]);
}

printf("\nAverage Waiting Time: %.2f\n", total_waiting_time/n);
printf("Average Turnaround Time: %.2f\n", total_turnaround_time/n);
```

## Wrapping Up

Close the main function to signify the end of our program.

```c
return 0;
}
```


By following this lesson, you’ve successfully implemented the Shortest Job First (SJF) scheduling algorithm. This method is essential in understanding priority-based scheduling in operating systems. Experiment with different input values to see the algorithm in action and understand its behavior!

## Compile and Run:

Use the buttons below to compile and run your SJF Scheduler.

#### Compile

```bash
gcc sjf_lab.c -o sjf_lab
```

#### Run

```bash
./sjf_lab
```

## Experimentation:
Play around with different numbers of processes and execution times. Observe how the SJF algorithm prioritizes processes with shorter execution times.

For example, for the input:

```bash
Enter the number of processes: 3
Enter execution time for process 1: 10
Enter execution time for process 2: 5
Enter execution time for process 3: 8
```

The expected output would be:

```bash
Process     Execution Time     Waiting Time     Turnaround Time
2           5                  0                5
3           8                  5                13
1           10                 13               23

Average Waiting Time: 6.00
Average Turnaround Time: 13.67
```

**Congratulations!** You’ve now implemented the **Shortest Job First (SJF)** scheduling algorithm. This method is a cornerstone in understanding priority-based scheduling in operating systems.

# Solution

The Shortest Job First (SJF) scheduling algorithm is a priority-based algorithm. The idea is simple: the process with the shortest execution time is the next to execute. This approach minimizes the average waiting time for other processes in the queue.

```c
#include <stdio.h>

int main() {
    int n; // number of processes
    int execution_time[100], waiting_time[100], turnaround_time[100], process_id[100];
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Gather input from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter execution time for process %d: ", i+1);
        scanf("%d", &execution_time[i]);
        process_id[i] = i+1;
    }

    // Bubble sort to arrange processes based on their execution time
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(execution_time[j] > execution_time[j+1]) {
                // Swap execution times
                int temp = execution_time[j];
                execution_time[j] = execution_time[j+1];
                execution_time[j+1] = temp;

                // Swap process IDs to keep them in sync with execution times
                int temp_id = process_id[j];
                process_id[j] = process_id[j+1];
                process_id[j+1] = temp_id;
            }
        }
    }

    // Calculate waiting and turnaround times
    waiting_time[0] = 0;
    turnaround_time[0] = execution_time[0];
    for(int i = 1; i < n; i++) {
        waiting_time[i] = execution_time[i-1] + waiting_time[i-1];
        turnaround_time[i] = execution_time[i] + waiting_time[i];
    }

    // Calculate total waiting and turnaround times
    for(int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display the results
    printf("Process\tExecution Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", process_id[i], execution_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time/n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time/n);

    return 0;
}
```

Here, we declare variables and arrays:
* `n`: Number of processes.
* `execution_time[]`: Stores the execution time for each process.
* `waiting_time[]` and `turnaround_time[]`: Store the waiting and turnaround times for each process.
* `process_id[]`: Helps us keep track of the original order of processes.
* `total_waiting_time` and `total_turnaround_time`: Used to calculate average waiting and turnaround times.

### Gathering User Input:

We prompt the user to specify the number of processes and the execution time for each one.

### Sorting Processes by Execution Time:

Using the bubble sort algorithm, we arrange the processes in ascending order based on their execution times. This ensures that the process with the shortest execution time is scheduled first.

### Calculating Waiting and Turnaround Times:
* The first process’s waiting time is always zero because it’s the first to execute.
* The turnaround time for a process is its waiting time plus its execution time.
* For subsequent processes, the waiting time is the sum of the previous process’s waiting time and execution time.

### Calculating Average Waiting and Turnaround Times:

We sum up the waiting and turnaround times for all processes. Then, we divide by the number of processes to get the averages.

### Displaying Results:

The program then displays each process’s execution time, waiting time, and turnaround time in a tabular format. It also prints out the average waiting and turnaround times.