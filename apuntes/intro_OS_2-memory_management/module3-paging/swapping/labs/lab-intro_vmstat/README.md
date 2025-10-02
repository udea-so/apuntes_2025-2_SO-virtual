# Lab Introduction: vmstat

The `free` command is great for a snapshot, but we want to see page swapping in action so we will use the vmstat tool which allows you to continuously monitor virtual memory statistics.

Let’s start by reading the `vmstat` manual pages:

```
man vmstat
```

*Reminder*: Use `q` to exit the manual.

1. Read through the pages and make sure you understand what the following columns mean:
   * memory > swpd
   * memory > free
   * swap > si
   * swap > so

2. In the terminal, run `vmstat 1`. This shows stats about machine usage every second.
   * Notice the small fluctuations in the columns
   * This will run forever – when you want to stop it, press Ctrl and C at the same time.
