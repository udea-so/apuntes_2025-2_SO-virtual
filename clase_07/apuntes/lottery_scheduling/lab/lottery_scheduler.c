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