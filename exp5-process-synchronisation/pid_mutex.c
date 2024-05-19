#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 10

int pid_bitmap[MAX_PID - MIN_PID + 1];
pthread_mutex_t mutex;

void init_pid_manager()
{
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++)
    {
        pid_bitmap[i] = 0;
    }
    pthread_mutex_init(&mutex, NULL);
}

int allocate_pid()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_PID - MIN_PID + 1; i++)
    {
        if (!pid_bitmap[i])
        {
            pid_bitmap[i] = 1;
            pthread_mutex_unlock(&mutex);
            return i + MIN_PID;
        }
    }
    pthread_mutex_unlock(&mutex);
    return -1;
}

void release_pid(int pid)
{
    if (pid < MIN_PID || pid > MAX_PID)
    {
        printf("Invalid PID\n");
        return;
    }
    pthread_mutex_lock(&mutex);
    pid_bitmap[pid - MIN_PID] = 0;
    pthread_mutex_unlock(&mutex);
}

void *thread_func(void *arg)
{
    int thread_id = *((int *)arg);
    int pid = allocate_pid();
    if (pid != -1)
    {
        printf("Thread %d: Allocated PID %d\n", thread_id, pid);
        usleep(rand() % 1000000);
        release_pid(pid);
        printf("Thread %d: Released PID %d\n", thread_id, pid);
    }
    else
    {
        printf("Thread %d: Unable to allocate PID\n", thread_id);
    }
    pthread_exit(NULL);
}

int main()
{
    init_pid_manager();

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
