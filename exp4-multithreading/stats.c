#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMS 1000

int nums[MAX_NUMS];
int num_count;
double average;
int minimum;
int maximum;

void *calculate_average(void *arg)
{
    int sum = 0;
    for (int i = 0; i < num_count; i++)
    {
        sum += nums[i];
    }
    average = (double)sum / num_count;
    pthread_exit(0);
}

void *calculate_minimum(void *arg)
{
    minimum = nums[0];
    for (int i = 1; i < num_count; i++)
    {
        if (nums[i] < minimum)
        {
            minimum = nums[i];
        }
    }
    pthread_exit(0);
}

void *calculate_maximum(void *arg)
{
    maximum = nums[0];
    for (int i = 1; i < num_count; i++)
    {
        if (nums[i] > maximum)
        {
            maximum = nums[i];
        }
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    num_count = argc - 1;
    for (int i = 0; i < num_count; i++)
    {
        nums[i] = atoi(argv[i + 1]);
    }

    pthread_t threads[3];
    pthread_create(&threads[0], NULL, calculate_average, NULL);
    pthread_create(&threads[1], NULL, calculate_minimum, NULL);
    pthread_create(&threads[2], NULL, calculate_maximum, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Average: %.2f\n", average);
    printf("Minimum: %d\n", minimum);
    printf("Maximum: %d\n", maximum);

    return 0;
}