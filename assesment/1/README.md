# FCFS Scheduling

Implement the FCFS scheduling algorithm and calculate the average waiting time and turnaround time for a set of processes by:
* **Defining a Process Structure**: Create a structure to store the necessary information for each process, such as process ID, burst time, waiting time, and turnaround time.
* **Gathering Input**: Prompt the user to enter the number of processes and their respective burst times.
* **FCFS Implementation**: Implement the FCFS scheduling algorithm to calculate the waiting time and turnaround time for each process.
* **Calculating Averages**: Compute the average waiting time and average turnaround time.
* **Displaying the Results**: Present the calculated averages to the user.

Given the following input:

```
2
5
10
```

We should receive the following output:

```
Process Duration    Waiting Time    Turnaround Time
1   5       0       2
2   10      5       15
Average Waiting Time: 2.50
Average Turnaround Time: 8.50
```

## Solution

The program is designed to simulate the FCFS CPU scheduling algorithm. In this algorithm, the process that arrives first gets executed first. The program calculates and displays the average waiting time and average turnaround time of the given set of processes.

A correct solution to this problem is as follows.

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

# SJF Scheduling

Implement the SJF scheduling algorithm and calculate the average waiting time and turnaround time for a set of processes by:
* **Defining a Process Structure**: Create a structure to store the necessary information for each process, such as process ID, duration, waiting time, and turnaround time.
* **Gathering Input**: Prompt the user to enter the number of processes.
  * For each process, ask the user to input the process ID and its duration.
* **SJF Implementation**: Sort the list of processes based on their duration in ascending order.
* **Calculate the waiting time and turnaround time for each process**. To calculate the waiting time of a process, you can use the formula: `waiting_time[i] = waiting_time[i-1] + duration[i-1]`.
  * To calculate the turnaround time of a process, you can use the formula: `turnaround_time[i] = waiting_time[i] + duration[i]`.
* **Calculating Averages**: Compute the average waiting time and average turnaround time.
* **Displaying the Results**: Present the calculated averages to the user and display the waiting time and turnaround time for each process.

Given the following input:

```
4
6
8
5
3
```

We should receive the following output:


```
Process Execution Time  Waiting Time    Turnaround Time
4   3       0       3
3   5       3       8
1   6       8       14
2   8       14      22

Average Waiting Time: 6.25
Average Turnaround Time: 11.75
```

### Solution

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

**Gathering User Input:**

We prompt the user to specify the number of processes and the execution time for each one.

**Sorting Processes by Execution Time:**

Using the bubble sort algorithm, we arrange the processes in ascending order based on their execution times. This ensures that the process with the shortest execution time is scheduled first.

**Calculating Waiting and Turnaround Times:**

* The first process’s waiting time is always zero because it’s the first to execute.
* The turnaround time for a process is its waiting time plus its execution time.
* For subsequent processes, the waiting time is the sum of the previous process’s waiting time and execution time.

**Calculating Average Waiting and Turnaround Times:**

We sum up the waiting and turnaround times for all processes. Then, we divide by the number of processes to get the averages.

**Displaying Results:**

The program then displays each process’s execution time, waiting time, and turnaround time in a tabular format. It also prints out the average waiting and turnaround times.

# Multi-Level Feedback

Implement the Multi-Level Feedback Queue (MLFQ) scheduling algorithm and calculate the average waiting time and turnaround time for a set of processes by:

1. **Defining `Process` and `Queue` Structures**: 
   * Create a `Process` structure to store necessary information for each process, such as process ID, duration, remaining time, waiting time, and turnaround time.
   * Create a `Queue` structure to represent a queue in the MLFQ, which holds processes, has a front and rear indicator, and a time quantum associated with it.

2. **Initializing Queues**:
   * Implement a function to initialize your queues with appropriate time quanta. For example, a high-priority queue might have a smaller time quantum, and a low-priority queue might have a larger time quantum.

3. **Gathering Input**:
   * Prompt the user to enter the number of processes.
   * For each process, ask the user to input the process ID and its duration.
   * Initialize the remaining time for each process and enqueue them to the high-priority queue.

4. **MLFQ Implementation**:
   * Implement the MLFQ scheduling algorithm. Processes start in the high-priority queue and move to lower-priority queues if they do not finish within their time quantum.
   * Ensure that you update the waiting time, turnaround time, and remaining time for each process as they are scheduled and executed.
   * Print informative messages to show the state of the system, such as when a process is running, when it is moved to a different queue, and when it finishes execution.
  
5. **Calculating Averages and Displaying Results**:
   * After all processes have finished execution, calculate the average waiting time and average turnaround time.
   * Display the waiting time, turnaround time, and other relevant information for each process.
   * Present the calculated averages to the user.

6. **Testing Your Implementation**:
   * Test your implementation with various sets of processes and time quanta to ensure that it behaves as expected.
   * You can use the provided example to verify the correctness of your implementation.

### Example Input:

```
3
10
20
30
```

### Example Output:

```
Process 1 is running in high priority queue
Process 1 finished execution
Process 2 is running in high priority queue
Process 2 is rescheduled with 18 remaining time
Process 3 is running in high priority queue
Process 3 is rescheduled with 28 remaining time
Process 2 is running in medium priority queue
Process 2 is rescheduled with 14 remaining time
Process 3 is running in medium priority queue
Process 3 is rescheduled with 24 remaining time
Process 2 is running in low priority queue
Process 2 is rescheduled with 6 remaining time
Process 3 is running in low priority queue
Process 3 is rescheduled with 16 remaining time
Process 2 is running in low priority queue
Process 2 finished execution
Process 3 is running in low priority queue
Process 3 is rescheduled with 8 remaining time
Process 3 is running in low priority queue
Process 3 finished execution

Process Duration Waiting Time Turnaround Time
1       10      0           10
2       20      10          30
3       30      30          60

Average Waiting Time: 13.33
Average Turnaround Time: 33.33
```



 
