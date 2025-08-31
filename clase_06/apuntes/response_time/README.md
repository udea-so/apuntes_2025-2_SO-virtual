# A New Metric: Response Time

STCF is a great policy as long as we know all the completion times for each job, the jobs only used the CPU, and the only metric we value is turnaround time.

Another metric used to evaluate scheduling policies is **response time**. Response time is the time it takes for the job to arrive and then become scheduled for the first time.

$T_{response} = T_{firstrun} - T_{arrival}$

It is important to note that optimizing for turnaround time is detrimental to response time. Assume three jobs arrive at once. The third job will not be scheduled until the first two jobs have been completed. So, how do you create a scheduler that is responsive?


