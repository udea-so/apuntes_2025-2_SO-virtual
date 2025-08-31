#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main() {
    int jobCount = 3;
    int jobTimes[3], arrivalTimes[3];
    int totalTurnaround = 0;
    int currentTime = 0;

    printf("SJF Scheduling Simulator\n\n");

    // Get arrival times and execution times for each job
    for(int i = 0; i < jobCount; i++) {
        printf("Enter arrival time and execution time for Job %c (separated by a space): ", 'A' + i);
        scanf("%d %d", &arrivalTimes[i], &jobTimes[i]);
    }

    // Simulate SJF
    int shortestTime, shortestJob;
    for(int i = 0; i < jobCount; i++) {
        shortestTime = INT_MAX;
        shortestJob = -1;

        for(int j = 0; j < jobCount; j++) {
            if (arrivalTimes[j] <= currentTime && jobTimes[j] < shortestTime && jobTimes[j] != -1) {
                shortestTime = jobTimes[j];
                shortestJob = j;
            }
        }
        if (shortestJob == -1) {
            currentTime++;
            i--;
            continue;
        }

        // Execute shortest job found
        currentTime += jobTimes[shortestJob];
        totalTurnaround += (currentTime - arrivalTimes[shortestJob]);
        jobTimes[shortestJob] = -1; // Mark job as completed
    }

    // Display the average turnaround time
    printf("\nThe average turnaround time is: %.2f seconds\n", (float)totalTurnaround / jobCount);

    return 0;
}