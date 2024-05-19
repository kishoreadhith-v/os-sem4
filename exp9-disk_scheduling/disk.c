#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int scan(int *queue, int len, int disk_size, int head, int direction)
{
    int copy[len];
    memcpy(copy, queue, len * sizeof(int));
    qsort(copy, len, sizeof(int), compare);

    int total_distance = 0;
    if (direction > 0)
    {
        int i;
        for (i = 0; i < len; i++)
        {
            if (copy[i] >= head)
            {
                break;
            }
        }
        for (; i < len; i++)
        {
            printf("%d -> ", copy[i]);
            total_distance += abs(copy[i] - head);
            head = copy[i];
        }
        if (i < len)
        {
            printf("%d -> ", disk_size);
            total_distance += abs(disk_size - head);
            head = disk_size;
        }
        for (i = len - 1; i >= 0; i--)
        {
            if (copy[i] < head)
            {
                printf("%d -> ", copy[i]);
                total_distance += abs(copy[i] - head);
                head = copy[i];
            }
        }
    }
    else
    {
        int i;
        for (i = len - 1; i >= 0; i--)
        {
            if (copy[i] <= head)
            {
                break;
            }
        }
        for (; i >= 0; i--)
        {
            printf("%d -> ", copy[i]);
            total_distance += abs(copy[i] - head);
            head = copy[i];
        }
        if (i >= 0)
        {
            printf("%d -> ", 0);
            total_distance += abs(head);
            head = 0;
        }
        for (i = 0; i < len; i++)
        {
            if (copy[i] > head)
            {
                printf("%d -> ", copy[i]);
                total_distance += abs(copy[i] - head);
                head = copy[i];
            }
        }
    }
    printf("\n");
    return total_distance;
}

// Implement cscan, look, and clook functions in a similar manner

int main()
{
    int disk_size, head, len, direction;
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    printf("Enter the head position: ");
    scanf("%d", &head);
    printf("Enter the number of requests: ");
    scanf("%d", &len);
    int queue[len];
    printf("Enter the requests: ");
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &queue[i]);
    }
    printf("Enter the direction (1 for right, -1 for left): ");
    scanf("%d", &direction);

    printf("Initial Head Position: %d\n", head);
    printf("SCAN: Total head movement = %d\n", scan(queue, len, disk_size, head, direction));
    // Call cscan, look, and clook functions similarly

    return 0;
}
