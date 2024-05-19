#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("Error forking");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("First Child process with PID: %d\n", getpid());
        printf("Executing first child...\n");
        sleep(2);
        printf("First Child process terminating...\n");
        exit(0);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("Error forking");
        return 1;
    }

    if (pid2 == 0)
    {
        printf("Second Child process with PID: %d\n", getpid());
        printf("Executing second child...\n");
        sleep(2);
        printf("Second Child process terminating...\n");
        exit(0);
    }

    printf("Parent process waiting for children to terminate...\n");
    wait(NULL);
    printf("All children executed.\n");
    printf("Parent process terminating...\n");

    return 0;
}
