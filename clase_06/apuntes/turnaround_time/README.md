# Turnarround Time

Understanding the **performance** and **fairness** of a scheduling algorithm is paramount to assessing its efficiency. To make these evaluations, we need **metrics**. Let’s dive deeper into some of these metrics, beginning with **Turnaround Time**.

Imagine you’re waiting in line to buy a coffee. Your "**turnaround time**" would be the difference between when you first got in line (arrival) and when you finally received your coffee (completion).

The **turnaround time** of a job is the amount of time it takes to complete the task minus the time at which the task arrived. We can think of turnaround time as:

$$T_{turnaround} = T_{completion} - T_{arribal}$$

One of our assumptions is that all jobs arrive at the same time, so we could say that $T_{arribal} = 0$ That would mean that $T_{turnaround} = T_{completion}$

### Let’s explore this with a simulator!

[metrics.c](metrics.c) is a simulator that calculates the turnaround time of processes based on the time of completion. calculates the turnaround time given the assumption `T_arrival=0`, and then displays the result in the terminal

Try entering different values for $T_{completion}$ and observe the resultant turnaround time.

```
gcc metrics.c -o metrics 
./metrics
```

#### Performance vs. Fairness

**Performance** and **fairness** often counterbalance each other in scheduling. Think of it like this: If you were in a queue and someone in urgent need was allowed to move ahead, that’s prioritizing performance over fairness. It might be faster overall, but it’s not equally fair to everyone.

In addition to performance, operating systems need to monitor **fairness metrics** as well. Performance and fairness can be at odds when it comes to scheduling. We can enhance performance by forgoing fairness.
