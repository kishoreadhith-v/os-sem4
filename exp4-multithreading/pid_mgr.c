#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MIN_PID 300
#define MAX_PID 5000
#define PID_SIZE ((MAX_PID - MIN_PID + 1) / 8 + 1)

// define an array of bits for the pidmap
int pid_map[PID_SIZE];

int allocate_map(void)
{
    for (int i = 0; i < PID_SIZE; i++)
    {
        pid_map[i] = 0;
    }
}

int allocate_pid(void)
{
    for (int i = 0; i < PID_SIZE; i++)
    {
        if (pid_map[i] == 0)
        {
            pid_map[i] = 1;
            return i + MIN_PID;
        }
    }
    return -1;
}

void release_pid(int pid)
{
    if (pid < MIN_PID || pid > MAX_PID)
    {
        printf("Invalid PID\n");
        return;
    }
    pid_map[pid - MIN_PID] = 0;
}

int main()
{
    allocate_map();
    int pid1 = allocate_pid();
    int pid2 = allocate_pid();
    int pid3 = allocate_pid();
    printf("Allocated PIDs: %d, %d, %d\n", pid1, pid2, pid3);
    release_pid(pid2);
    printf("Released PID: %d\n", pid2);
    int pid4 = allocate_pid();
    printf("Allocated PID: %d\n", pid4);
    return 0;
}