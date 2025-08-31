# CPU Scheduling

## Objectives

* **Identify and Describe** the primary objectives and purposes of scheduling policies within an operating system.
* **Explain** the key assumptions made when designing and implementing scheduling policies.
* **Measure** and evaluate the performance of different scheduling policies based on essential metrics.
* **Compare and Contrast** the advantages and disadvantages of different scheduling policies in various scenarios.
* **Apply** theoretical knowledge of scheduling to practical situations, ensuring efficient CPU utilization and process execution.

## Introduction to CPU Scheduling

Now that we’re equipped with an understanding of low-level process mechanisms, it’s time to delve into the world of the OS **scheduler**.

The **scheduler** is the brain behind determining which processes run, when, and for how long. We’ll explore various **scheduling policies** or **disciplines** that dictate these decisions.

## Workload Assumptions

Before diving into the specifics, it’s important to set some ground rules. These rules, known as **workload assumptions**, form the basis for our initial exploration. By understanding your workload, you’re better positioned to design an effective scheduling policy.

To start, we’ll introduce some **unrealistic workload assumptions**. While these might seem oversimplified, they’ll help us understand core concepts. As we move forward, we’ll gradually modify these assumptions to mirror real-world scenarios more closely.
* **Assumption 1**: All jobs run for the same duration.
* **Assumption 2**: Jobs arrive at the CPU at the same time.
* **Assumption 3**: All jobs run until they are completed.
* **Assumption 4**: All jobs only use the CPU (no I/O operations).
* **Assumption 5**: The OS knows the duration of each job in advance.
Again, all of these assumptions are completely unrealistic, but they are just starting points for us to build our foundation.

## Simulation

Te file [`scheduler_simulation.c`](scr/simple_scheduler/scheduler_simulation.c) simulates the running of processes based on our above assumptions.
* Explore the code and its comments to get a grasp of how it works.
* In the terminal to the lower left, run compile and run the simulator to see it in action.

```
gcc scheduler_simulation.c -o scheduler_simulation
./scheduler_simulation
```

We can modify process parameters and see the scheduler’s decision in real-time.
1. **Jobs' Duration**: Each job has a set duration (in seconds) that it will run for.
   * Currently, all jobs have a default duration 5 of 
 seconds (as per the `DURATION` macro).
   * By modifying this duration, we can change how long each job takes to execute.
   * For example, changing the value of `DURATION` in the code to `#define DURATION 3` will make each job run 3 for seconds.
2. **Number of Jobs**: The current simulation has **three** jobs.
   * We can increase or decrease the number of jobs to see how the scheduler handles more or fewer tasks.
   * Adjust the `JOB_COUNT` macro and ensure that the `jobs` array in the `main` function matches the new count.
   * For example, to simulate **four** jobs:
     * Change `JOB_COUNT` to 4
     * Add another job, like `{4, DURATION}`, to the `jobs` array.
3. **Individual Job Durations**: While our current assumptions state that **all jobs run for the same duration**, we might want to see how the scheduler behaves if one job has a different duration than the others.
   * Directly adjust the duration in the `jobs` array.
   * If we want the second job to run for 7
 seconds, modify the array entry to `{2, 7}`.
4. **Job Arrival Order**: By changing the order of jobs in the `jobs` array, we can simulate the effect of different job arrival sequences on the scheduler.
   * Rearrange the order of the job structures in the `jobs` array.
   * To have **Job 3** run before **Job 1**, adjust the array to: 

   ```c
   Job jobs[JOB_COUNT] = {
      {3, DURATION}
      {1, DURATION},
      {2, DURATION},  
   };
   ```

After making your modifications, **compile** and **run** the code again in the terminal panel to see the scheduler’s decisions in real-time.

As we progress, keep these assumptions in mind. They’ll serve as our initial guiding light, setting the stage for more complex scheduling disciplines.

## Scheduling Metrics

Understanding the **performance** and **fairness** of a scheduling algorithm is paramount to assessing its efficiency. To make these evaluations, we need **metrics**. Let’s dive deeper into some of these metrics, beginning with **Turnaround Time**.

Imagine you’re waiting in line to buy a coffee. Your "**turnaround time**" would be the difference between when you first got in line (arrival) and when you finally received your coffee (completion).

The **turnaround time** of a job is the amount of time it takes to complete the task minus the time at which the task arrived. We can think of turnaround time as:

$$T_{turnaround} = T_{completion} - T_{arribal}$$

One of our assumptions is that all jobs arrive at the same time, so we could say that $T_{arribal} = 0$ That would mean that $T_{turnaround} = T_{completion}$

### Let’s explore this with a simulator!

In the panel to the left, you’ll find a simulator that calculates the turnaround time of processes based on the time of completion. calculates the turnaround time given the assumption `T_arrival=0`, and then displays the result in the terminal

Try entering different values for $T_{completion}$ and observe the resultant turnaround time.

```
gcc metrics.c -o metrics 
./metrics
```
#### Performance vs. Fairness

**Performance** and **fairness** often counterbalance each other in scheduling. Think of it like this: If you were in a queue and someone in urgent need was allowed to move ahead, that’s prioritizing performance over fairness. It might be faster overall, but it’s not equally fair to everyone.

In addition to performance, operating systems need to monitor **fairness metrics** as well. Performance and fairness can be at odds when it comes to scheduling. We can enhance performance by forgoing fairness.

## FIFO: First In, First Out

This straightforward mechanism, while easy to understand and implement, comes with its own set of challenges.

Imagine a coffee shop where the barista prepares orders strictly based on when they were placed. If someone orders a complex, time-consuming drink, everyone else behind them in line has to wait, even if their orders might take a fraction of the time.

This delay for the smaller, quicker orders is similar to what happens in **FIFO scheduling**, and it’s known as the **convoy effect**.

As an example, let’s assume:
* Three jobs, A, B, and C, arrive in the system simultaneously ($T_{arrival} = 0$)
* While they all arrived "at the same time", A arrived slightly before B, which likewise arrived just before C
* Each of these jobs takes 10 seconds to complete

The animation below demonstrates how FIFO scheduling works.

<p align="center">
  <img src="fifo1.gif" alt="fifo1"/>
</p>

If we were to compute the average turnaround time for these three tasks, we would use this formula:

$$\frac{10 + 20 + 30}{3} = 20$$

### Relaxing Assumption #1

It is more realistic to assume that each of these tasks do not take the same amount of time to execute. Now, job A takes 100 seconds while jobs B and C still take 10 seconds.

How does the FIFO algorithm perform under these circumstances?

Let’s calculate the average turnaround time for these three jobs.

$$\frac{100 + 110 + 120}{3} = 110$$

The average turnaround time jumped dramatically even though two of the jobs still only take 10 seconds to complete. This is the **convoy effect** in action, having small jobs that are stuck waiting behind a heavyweight job.

#### Let’s explore this with a simulator!

In the panels to the left, we’ll find a program that simulates the FIFO scheduling algorithm. This will also allow us to explore the convoy effect, which is a significant concern in FIFO scheduling.

First, let’s explore the first scenario, with all 3 jobs having 10 second execution times.
* **Job A**: 10 seconds
* **Job B**: 10 seconds
* **Job C**: 10 seconds

```
gcc fifo.c -o fifo; ./fifo
```

Now, let’s tweak our scenario. Job A will take a significantly longer time compared to B and C. This will help us witness firsthand how the convoy effect influences the average turnaround time in FIFO.
* **Job A**: 100 seconds
* **Job B**: 10 seconds
* **Job C**: 10 seconds

After running the simulation, notice the average turnaround time.

Even though jobs B and C only take 10 seconds each, they have to wait for the lengthy execution of Job A.

This results in a drastically increased average turnaround time for all jobs combined, a prime example of the convoy effect in action.

While it treats tasks fairly in the order of their arrival, this can lead to inefficiencies, especially when shorter tasks are queued behind a much longer one. Recognizing this limitation is essential when evaluating the appropriateness of **FIFO** for specific use cases.

**Checkpoint**
Drag the code blocks below to to finish the template and write a simple scheduler that schedules jobs using FIFO by:
* Creating a `Job` structure that represents each job with a unique `job_id` and its `duration`.
* Build the fifo_scheduler function that takes in an array of `jobs[]` and the total count of jobs.
* Inside the scheduler, we loop over each job:
* Print the execution message for the job.
* Use `sleep()` to simulate the duration the job runs for.* Print the completion message for the job.

Ensuring each job is executed in the order they’re present in the array, and they run to completion based on our assumptions.

```c
// TEMPLATE CODE

#include <stdio.h>
#include <unistd.h>  // for sleep()

#define JOB_COUNT 3

// COMPLETE THE CODE HERE

int main() {
    Job jobs[JOB_COUNT] = {
        {1, 4},
        {2, 2},
        {3, 6}
    };

    fifo_scheduler(jobs, JOB_COUNT);
    return 0;
}
typedef
```

**Sol:**

```c
typedef struct {
    int job_id;
    int duration;
} Job;

void fifo_scheduler(Job jobs[], int count) {
    for(int i = 0; i < count; i++) {
        printf("Executing Job %d for %d seconds...\n", jobs[i].job_id, jobs[i].duration);
        sleep(jobs[i].duration); 
        printf("Job %d completed!\n", jobs[i].job_id);
    }
}
```

