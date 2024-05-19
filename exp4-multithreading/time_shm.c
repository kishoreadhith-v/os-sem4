#include <stdio.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int shmid = shmget(IPC_PRIVATE, sizeof(struct timeval), IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
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
        struct timeval *tv = (struct timeval *)shmat(shmid, NULL, 0);
        if (tv == (void *)-1)
        {
            perror("shmat");
            return 1;
        }

        gettimeofday(tv, NULL);
        shmdt(tv);

        if (execvp(argv[1], &argv[1]) == -1) {
            perror("exec");
            return 1;
        }
    }
    else
    {
        wait(NULL);
        struct timeval end;
        gettimeofday(&end, NULL);
        struct timeval *start = (struct timeval *)shmat(shmid, NULL, 0);
        if (start == (void *)-1)
        {
            perror("shmat");
            return 1;
        }
        printf("Time taken: %ld microseconds\n", (end.tv_sec - start->tv_sec) * 1000000 + (end.tv_usec - start->tv_usec));
        shmdt(start);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}