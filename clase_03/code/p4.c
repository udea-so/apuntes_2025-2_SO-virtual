#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("Starting the program... (pid:%d)\n", (int) getpid());
    int child = fork();
    if (child < 0) {
      // child process failed, exit the program
      fprintf(stderr, "Child process was not created\n");
      exit(1);
    } else if (child == 0) {
      // child process successful; standard output directed to a file
      close(STDOUT_FILENO); 
      open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

      // now call the wc program
      char *exampleargs[3];
      exampleargs[0] = strdup("wc");   // calls the word count program
      exampleargs[1] = strdup("p4.c"); // file for the word count program
      exampleargs[2] = NULL;           // signifies the end of array
      execvp(exampleargs[0], exampleargs);  // exec call for word count
    } else {
      // parent process runs this branch
      int waiting = wait(NULL);
      assert(waiting >= 0);
    }
    return 0;
}