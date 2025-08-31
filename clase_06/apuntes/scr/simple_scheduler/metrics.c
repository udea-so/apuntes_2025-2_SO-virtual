#include <stdio.h>

int main() {
    int T_completion;
    int T_turnaround;
    int T_arrival = 0; // Assumption: T_arrival is always 0 for each job

    // Explain the assumption
    printf("Assumption: All jobs arrive at the same time, T_arrival = 0.\n\n");

    // Get the completion time from the user
    printf("Enter the completion time (T_completion) for the job: ");
    scanf("%d", &T_completion);

    // Calculate the turnaround time
    T_turnaround = T_completion - T_arrival; 

    // Display the result
    printf("\nGiven T_completion = %d and T_arrival = %d (assumed),\n", T_completion, T_arrival);
    printf("The turnaround time (T_turnaround) is: %d\n", T_turnaround);

    return 0;
}