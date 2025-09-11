# Lottery Scheduler Implementation

**Objective**: This lab is designed to guide you through implementing the **Lottery Scheduling** algorithm in C.

Lottery Scheduling is a probabilistic scheduling algorithm where processes are assigned lottery tickets, and the process with the winning ticket gets CPU time. The more tickets a process has, the higher its chances of being scheduled.

Lottery Scheduling ensures that over time, each process receives a share of the CPU proportional to the number of tickets it holds. This method is simple, efficient, and provides statistical fairness.

## Step 1: Setting Up Your Environment

First, include the necessary libraries. We need `stdio.h` for input/output operations, `stdlib.h` for functions involving memory allocation, and `time.h` to seed our random number generator.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```

### Step 2: Defining the Process Structure

Next, define a Process structure to represent a process in our system. Each process has an `id`, `duration` (total CPU time required), `remaining_time` (CPU time remaining), and `tickets` (number of lottery tickets assigned).

```c
typedef struct {
    int id;
    int duration;
    int remaining_time;
    int tickets;
} Process;
```

## Step 3: Implementing the Lottery Scheduling Logic

Now, let’s implement the core of our scheduler: the `lottery_scheduling` function. This function takes an array of processes and the number of processes as arguments.
1. **Calculate Total Tickets**: Sum up all the tickets from all processes.
2. **Random Draw**: In each iteration, draw a random ticket.
3. **Find the Winning Process**: Determine which process holds the winning ticket.
4. **Allocate CPU Time**: Deduct one unit of time from the winning process’s remaining time.
5. **Check for Completion**: If a process finishes execution, announce it.
6. **Repeat**: Continue until all processes are finished.

```c
void lottery_scheduling(Process *processes, int n) {
    int total_tickets = 0;
    for(int i = 0; i < n; i++) {
        total_tickets += processes[i].tickets;  // Calculate total number of tickets
    }

    srand(time(NULL));  // Seed for random number generation

    while(1) {
        int winner_ticket = rand() % total_tickets + 1;  // Draw a random ticket
        int ticket_count = 0;
        for(int i = 0; i < n; i++) {
            ticket_count += processes[i].tickets;
            if(ticket_count >= winner_ticket && processes[i].remaining_time > 0) {
                // Process with the winning ticket found
                printf("Process %d won the lottery\n", processes[i].id);
                printf("Process %d is running\n", processes[i].id);
                processes[i].remaining_time--;  // Run the process for one time unit
                if(processes[i].remaining_time == 0) {
                    printf("Process %d finished execution\n", processes[i].id);
                } else {
                    printf("Process %d is rescheduled with %d remaining time\n", processes[i].id, processes[i].remaining_time);
                }
                break;
            }
        }

        // Check if all processes are finished
        int unfinished_processes = 0;
        for(int i = 0; i < n; i++) {
            if(processes[i].remaining_time > 0) {
                unfinished_processes++;
            }
        }
        if(unfinished_processes == 0) {
            printf("All processes have finished execution\n");
            break;
        }
    }
}
```

## Step 4: Bringing It All Together in `main()`

Finally, let’s implement the `main()` function to bring our scheduler to life.
1. **Input Number of Processes**: Ask the user how many processes will be scheduled.
2. **Allocate Memory for Processes**: Use dynamic memory allocation to store process information.
3. **Input Process Information**: For each process, input its duration and the number of tickets.
4. **Invoke the Scheduler**: Call the lottery_scheduling function to start the scheduling.
5. **Clean Up**: Free the allocated memory.


```c
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Error: Number of processes must be greater than 0\n");
        return 1;
    }

    Process *processes = (Process *)malloc(n * sizeof(Process));
    for(int i = 0; i < n; i++) {
        printf("Enter duration and tickets for process %d: ", i+1);
        scanf("%d %d", &processes[i].duration, &processes[i].tickets);
        if(processes[i].tickets <= 0) {
            printf("Error: Number of tickets must be greater than 0\n");
            free(processes);
            return 1;
        }
        processes[i].id = i+1;
        processes[i].remaining_time = processes[i].duration;
    }

    lottery_scheduling(processes, n);

    free(processes);
    return 0;
}
```

## Compile and Run Your Lottery Scheduler

Now that your program is ready, compile and run it to see Lottery Scheduling in action.

### Compile:

```bash
gcc lottery_scheduler.c -o lottery_scheduler
```

### Run:

```bash
./lottery_scheduler
```

## Conclusion

Congratulations! You’ve successfully implemented a simple Lottery Scheduling algorithm. Feel free to experiment with different numbers of processes and ticket distributions to see how it affects the scheduling!

## Checkpoint

In Lottery Scheduling, each process is assigned a certain number of tickets, and the scheduler draws a random ticket to determine which process will run next. The more tickets a process has, the higher its chances of being selected. This ensures that over time, each process gets a fair share of the CPU.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int duration;
    int remaining_time;
    int tickets;
} Process;

void lottery_scheduling(Process *processes, int n) {
    int total_tickets = 0;
    for(int i = 0; i < n; i++) {
        total_tickets += processes[i].tickets;
    }

    srand(time(NULL));  // Seed for random number generation

    while(1) {
        int winner_ticket = rand() % total_tickets + 1;
        int ticket_count = 0;
        for(int i = 0; i < n; i++) {
            ticket_count += processes[i].tickets;
            if(ticket_count >= winner_ticket && processes[i].remaining_time > 0) {
                printf("Process %d won the lottery\n", processes[i].id);
                printf("Process %d is running\n", processes[i].id);
                processes[i].remaining_time--;
                if(processes[i].remaining_time == 0) {
                    printf("Process %d finished execution\n", processes[i].id);
                } else {
                    printf("Process %d is rescheduled with %d remaining time\n", processes[i].id, processes[i].remaining_time);
                }
                break;
            }
        }

        int unfinished_processes = 0;
        for(int i = 0; i < n; i++) {
            if(processes[i].remaining_time > 0) {
                unfinished_processes++;
            }
        }
        if(unfinished_processes == 0) {
            printf("All processes have finished execution\n");
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Error: Number of processes must be greater than 0\n");
        return 1;
    }

    Process *processes = (Process *)malloc(n * sizeof(Process));
    for(int i = 0; i < n; i++) {
        printf("Enter duration and tickets for process %d: ", i+1);
        scanf("%d %d", &processes[i].duration, &processes[i].tickets);
        if(processes[i].tickets <= 0) {
            printf("Error: Number of tickets must be greater than 0\n");
            free(processes);
            return 1;
        }
        processes[i].id = i+1;
        processes[i].remaining_time = processes[i].duration;
    }

    lottery_scheduling(processes, n);

    free(processes);
    return 0;
}
```

### How Does the Program Work?

1. **Include Necessary Libraries**: We include `stdio.h` for input/output operations, `stdlib.h` for memory allocation, and `time.h` to seed our random number generator.
2. **Define the Process Structure**: We define a `Process` structure to represent a process. Each process has an `id`, `duration` (total CPU time required), `remaining_time` (CPU time remaining), and `tickets` (number of lottery tickets assigned).
3. **Implement the Lottery Scheduling Logic**: In the `lottery_scheduling` function, we:
   * Calculate the total number of tickets.
   * Draw a random ticket.
   * Find the process that holds the winning ticket.
   * Deduct one unit of time from the winning process’s remaining time.
   * Repeat until all processes are finished.
4. **`main()` Function**: In the `main()` function, we:
   * Take user input for the number of processes.
   * Allocate memory to store process information.
   * Take user input for each process’s duration and number of tickets.
   * Call the `lottery_scheduling` function to start the scheduling.
   * Free the allocated memory.