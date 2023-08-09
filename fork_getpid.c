#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Original process: PID=%d, Parent PID=%d\n", getpid(), getppid());

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        sleep(3); // Sleep for 3 seconds
        
        printf("Child process: Executing ls command...\n");
        execl("/bin/ls", "ls", "-l", NULL);
        
        perror("execl"); // This will only be printed if execl fails
        return 1;
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), child_pid);
        wait(NULL); // Wait for the child process to finish
        printf("Parent process: Child has finished\n");
    }

    return 0;
}
