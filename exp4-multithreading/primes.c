#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int limit;

void *print_primes(void *arg)
{
    for(int i = 2; i <= limit; i++)
    {
        int is_prime = 1;
        for(int j = 2; j < i/2 + 1; j++)
        {
            if(i % j == 0)
            {
                is_prime = 0;
                break;
            }
        }
        if(is_prime)
        {
            printf("%d\n", i);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <limit>\n", argv[0]);
        return 1;
    }

    limit = atoi(argv[1]);

    pthread_t tid;
    pthread_create(&tid, NULL, print_primes, NULL);
    pthread_join(tid, NULL);

    return 0;
}