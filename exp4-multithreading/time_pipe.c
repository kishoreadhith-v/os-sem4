#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        close(fd[0]);
        struct timeval start;
        gettimeofday(&start, NULL);
        write(fd[1], &start, sizeof(struct timeval));
        close(fd[1]);
        if (execvp(argv[1], &argv[1]) == -1)
        {
            perror("exec");
            return 1;
        }
    }
    else
    {
        wait(NULL);
        struct timeval end;
        gettimeofday(&end, NULL);
        struct timeval start;
        close(fd[1]);
        read(fd[0], &start, sizeof(struct timeval));
        close(fd[0]);
        printf("Time taken: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    }
    return 0;
}