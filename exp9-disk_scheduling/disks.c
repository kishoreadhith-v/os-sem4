#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CYLINDERS 1000

// Function to sort the requests in ascending order
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to simulate SCAN disk scheduling algorithm
void SCAN(int head, int requests[], int n, int cylinders)
{
    int total_movement = 0;
    int direction = 1; // 1 for moving towards higher cylinders, -1 for moving towards lower cylinders

    printf("SCAN Disk Scheduling Algorithm:\n");
    printf("Head Movement: %d", head);

    sort(requests, n);

    int current = head;
    while (true)
    {
        if (current == cylinders - 1 || current == 0)
        {
            direction = -direction; // Change direction when reaching either end
            printf(" -> %d", direction > 0 ? cylinders - 1 : 0);
        }

        current += direction;
        total_movement++;

        for (int i = 0; i < n; i++)
        {
            if (requests[i] == current)
            {
                printf(" -> %d", current);
                requests[i] = -1; // Mark the request as serviced
            }
        }

        bool all_served = true;
        for (int i = 0; i < n; i++)
        {
            if (requests[i] != -1)
            {
                all_served = false;
                break;
            }
        }

        if (all_served)
            break;
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
}

// Function to simulate CSCAN disk scheduling algorithm
void CSCAN(int head, int requests[], int n, int cylinders)
{
    int total_movement = 0;
    printf("\nCSCAN Disk Scheduling Algorithm:\n");
    printf("Head Movement: %d", head);

    sort(requests, n);

    int current = head;
    int index = 0;

    // Move towards higher cylinders
    while (index < n && requests[index] < current)
    {
        index++;
    }

    // Move towards lower cylinders after reaching the end
    if (index == n)
    {
        printf(" -> %d", cylinders - 1);
        current = 0;
        total_movement += cylinders - head - 1;
    }

    while (index < n)
    {
        printf(" -> %d", requests[index]);
        total_movement += abs(requests[index] - current);
        current = requests[index];
        index++;
    }

    printf(" -> 0"); // Move back to the beginning
    total_movement += current;

    printf("\nTotal Head Movement: %d\n", total_movement);
}

// Function to simulate LOOK disk scheduling algorithm
void LOOK(int head, int requests[], int n, int cylinders)
{
    int total_movement = 0;
    printf("\nLOOK Disk Scheduling Algorithm:\n");
    printf("Head Movement: %d", head);

    sort(requests, n);

    int current = head;
    int index = 0;

    // Move towards higher cylinders
    while (index < n && requests[index] < current)
    {
        index++;
    }

    while (index < n)
    {
        printf(" -> %d", requests[index]);
        total_movement += abs(requests[index] - current);
        current = requests[index];
        index++;
    }

    // Move towards lower cylinders
    index--;
    while (index >= 0)
    {
        printf(" -> %d", requests[index]);
        total_movement += abs(requests[index] - current);
        current = requests[index];
        index--;
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
}

// Function to simulate CLOOK disk scheduling algorithm
void CLOOK(int head, int requests[], int n, int cylinders)
{
    int total_movement = 0;
    printf("\nCLOOK Disk Scheduling Algorithm:\n");
    printf("Head Movement: %d", head);

    sort(requests, n);

    int current = head;
    int index = 0;

    // Move towards higher cylinders
    while (index < n && requests[index] < current)
    {
        index++;
    }

    while (index < n)
    {
        printf(" -> %d", requests[index]);
        total_movement += abs(requests[index] - current);
        current = requests[index];
        index++;
    }

    // Move back to the beginning
    printf(" -> %d", requests[0]);
    total_movement += cylinders - requests[0];

    printf("\nTotal Head Movement: %d\n", total_movement);
}

int main()
{
    int cylinders, head, n;

    printf("Enter the number of cylinders: ");
    scanf("%d", &cylinders);

    printf("Enter the current head position: ");
    scanf("%d", &head);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    SCAN(head, requests, n, cylinders);
    CSCAN(head, requests, n, cylinders);
    LOOK(head, requests, n, cylinders);
    CLOOK(head, requests, n, cylinders);

    return 0;
}
