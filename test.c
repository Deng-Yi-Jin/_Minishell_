#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status1, status2;
    char *argv2[] = {"expr", "1", "+", "1", NULL};
//    char *argv2[] = {"nonexistent_command", NULL};
    char *envp[] = {NULL};
/*
    // Create the first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child process 1: Execute a valid command
        execve("/bin/ls", argv1, envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
*/
    // Create the second child process
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child process 2: Execute an invalid command
        if (execve("/usr/bin/expr", argv2, envp) == -1)
			;/*{
			printf("invalid args\n");
        	perror("execve failed");
        	exit(EXIT_FAILURE);
		}*/
    }

    // Parent process: Wait for child processes to finish
	//waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    // Print the exit statuses of the child processes
    //printf("Exit status of child 1: %d\n", WEXITSTATUS(status1));
    printf("Exit status of child 2: %d\n", WEXITSTATUS(status2));

    return 0;
}
