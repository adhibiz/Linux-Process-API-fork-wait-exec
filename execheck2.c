#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process replaces itself with ls command
        printf("Child: Executing 'ls -l'\n");
        execl("/bin/ls", "ls", "-l", NULL);

        // If exec fails
        perror("exec failed");
    } else {
        // Parent waits for child to complete
        wait(&status);
        printf("Parent: Child finished with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
