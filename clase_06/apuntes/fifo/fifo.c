#include <stdio.h>

int main() {
    int jobCount = 3;
    int jobTimes[3];
    int totalTurnaround = 0;
    int currentTime = 0;

    printf("FIFO Scheduling Simulator\n\n");
    printf("Assumption: Jobs A, B, and C arrive in the order A -> B -> C.\n\n");

    // Get execution times for each job
    for(int i = 0; i < jobCount; i++) {
        printf("Enter execution time for Job %c (in seconds): ", 'A' + i);
        scanf("%d", &jobTimes[i]);

        // Calculate turnaround for current job
        totalTurnaround += (currentTime + jobTimes[i]);

        // Update current time for next job's arrival
        currentTime += jobTimes[i];
    }

    // Display the average turnaround time
    printf("\nThe average turnaround time is: %d seconds\n", totalTurnaround / jobCount);

    return 0;
}