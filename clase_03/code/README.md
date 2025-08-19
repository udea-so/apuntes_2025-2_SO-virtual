

## fork()

The fork() system call creates a new process. Every process has a process identifier (also called a PID). The PID is used to name the process. This program calls the fork() command and prints three lines of text. Each line has the PID of the process that printed the text.

./p1

Starting the program... (pid:2041)
Hello from the parent process (pid:2041)
Hello from the child process (pid:2042)

## wait()

You may find the need to have the parent wait for a child process to terminate. This can be done with the wait() command or with the waitpid() command.

./p2

Starting the program... (pid:2773)
Hello from the child process (pid:2774)
Hello from the parent process (waiting:2774) (pid:2773)

## exec( )


The exec() system call is another useful feature of the process creation API. If fork() creates a child process of the same program, then exec() runs a completely different program.

In this example, we use execvp() to run a different program, wc. This program will analyze the p3.c program and print out how many lines, words, and bytes are in the file.

./p3

Hello from the child process (pid:3263)
  31  134 1118 p3.c
Hello from the parent process (waiting:3263) (pid:3262)

## Redirection & Pipes

Why bother separating the fork() and exec() system calls? Why not have a single command that can do both tasks? By separating the two system calls, you can you can run code after calling fork() but before calling exec().

### Redirection

Let’s start with a basic example. Copy and paste the command into the terminal. You should see the lines, words, and bytes from the p3.c file (from the previous page).

wc p3.c

Now let’s add the redirection operator (>) to the program so that the output is redirected to the file ouput.txt.

wc p3.c > output.txt

We don’t see any output because the redirection happened after the fork() but before the exec(). Run the following command to see the contents of output.txt.

cat output.txt

¿Como hacerlo usando C?

The output should be the same. Using redirection demonstrates the flexibility you gain by separating the fork() and exec() system calls.

### Pipes

The pipe operator (|) works similarly to redirection in that it takes advantage of the separation of fork() and exec(). Pipes allow for the output from one command to be used as input for another. Let’s say we want to count all instances of the characters an in the file words.txt. This is a two-step process. First, use grep to return all instances of an and then use the wc program to count them. The pipe operator allows you to chain these two commands together.
Run the following command in the terminal. You should see 17 as the output.

grep -o an words.txt | wc -l


## Process Control

### Kill()

The fork(), exec(), and wait() commands are not the only way to interact with processes. You may find your need to stop a process. The kill() system call can send pause, terminate, or other commands to a process. The control-c key combination is commonly used to send a SIGINT (interrupt) signal to a process. The control-z key combination sends a SIGTSTP stop signal to a process. This pauses a process. You can resume the process later if need be.
The button below runs a Python script that is an infinite loop. Launch the script by clicking the button. Then, in the terminal, use control-c on the keyboard to interrupt the process.


## Users & Tools

### Who can send signals and who can’t?

The fundamental job of the operating system is to allocate resources like the CPU, memory, and disk space to each user with the goal of maintaining a productive environment.

### Tools

#### PS

This command shows you who are running commands. Enter the following command in the terminal.


ps

This just shows you what your user is runing. We know that there is a root user that is also running processes in the background.
ps -A

#### Top

The top command displays the processes running on the system as well as how many resources (CPU and memory) each process consumes. As you are not running many program, the top output will not change much. Every so often you should see a change on the first line of the output.

top

#### Kill

The kill and killall commands can terminate a process. Be careful with these commands. You can easily kill things like the window manager, which makes using the computer much harder.
Let’s run the infinite loop script from earlier. This time, however, we are going to use the kill command to terminate the process. Start by clicking the button below. Notice how there is a spinning icon.

## Summary

Summary
In this section, we explored fork(), exec(), and wait() system calls for the Process API related to UNIX process creation.
Typically, each process has a Process ID (PID) which is used to identify each process.
The fork() system call is used to start a new process.
The newly created process is called the child processes, while the creator process is called the parent process. A child process is nearly identical to the parent.
A parent process can wait for its child process to finish its execution with the wait() system call.
The exec() system call lets the parent process start a completely different process as the child.
Signals can control a process by stopping, continuing, or terminating the process.
An operating system can have multiple users and makes sure that each user controls only their own processes.
A superuser (also called root) can control all processes running on the system, but you should use caution when doing so.

