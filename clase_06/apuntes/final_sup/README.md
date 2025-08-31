# The Final Assumption

## Relaxing Assumption #5

The last assumption to revisit is that the **scheduler knows the length of every job**. The operating system knows very little about the length of a job, so this could be the worst assumption to make about workload.

Without this information, how can you know if you should use SJF or STCF to operate efficiently? How can we use RR and time slices to improve response time?

In the next lesson, we will talk about the **multi-level feedback queue**, which tries to make predictions about duration using information from the recent past.

