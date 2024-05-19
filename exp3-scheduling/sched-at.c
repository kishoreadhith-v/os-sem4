#include <stdio.h>
#include <stdlib.h>

struct PCB
{
    int procId;
    int arrivalTime;
    int cpuBurst;
    int priority;
    int waitingTime;
    struct PCB *next;
    struct PCB *prev;
};

struct PCB *createPCB(int procId, int arrivalTime, int cpuBurst, int priority)
{
    struct PCB *newPCB = (struct PCB *)malloc(sizeof(struct PCB));
    newPCB->procId = procId;
    newPCB->arrivalTime = arrivalTime;
    newPCB->cpuBurst = cpuBurst;
    newPCB->priority = priority;
    newPCB->waitingTime = 0;
    newPCB->next = NULL;
    newPCB->prev = NULL;
    return newPCB;
}

void insertPriority(struct PCB **head, struct PCB **tail, struct PCB *newPCB)
{
    if (*head == NULL)
    {
        *head = newPCB;
        *tail = newPCB;
    }
    else
    {
        struct PCB *current = *head;
        while (current != NULL && current->priority <= newPCB->priority)
        {
            current = current->next;
        }
        if (current == NULL)
        {
            (*tail)->next = newPCB;
            newPCB->prev = *tail;
            *tail = newPCB;
        }
        else if (current == *head)
        {
            newPCB->next = *head;
            (*head)->prev = newPCB;
            *head = newPCB;
        }
        else
        {
            newPCB->next = current;
            newPCB->prev = current->prev;
            current->prev->next = newPCB;
            current->prev = newPCB;
        }
    }
}

void insertRR(struct PCB **head, struct PCB **tail, struct PCB *newPCB)
{
    if (*head == NULL)
    {
        *head = newPCB;
        *tail = newPCB;
        newPCB->next = newPCB;
        newPCB->prev = newPCB;
    }
    else
    {
        (*tail)->next = newPCB;
        newPCB->prev = *tail;
        newPCB->next = *head;
        (*head)->prev = newPCB;
        *tail = newPCB;
    }
}

void executePriority(struct PCB **head, struct PCB **tail)
{
    int time = 0;
    int waitingTime = 0;
    int count = 0;
    struct PCB *completedProcesses[10];
    struct PCB *current = *head;
    while (current != NULL)
    {
        printf("Executing process %d with CPU burst %d\n", current->procId, current->cpuBurst);
        time += current->cpuBurst;
        current->waitingTime = time - current->arrivalTime;
        waitingTime += current->waitingTime;
        completedProcesses[count] = current;
        count++;
        if (current == *head)
        {
            *head = current->next;
            if (*head != NULL)
            {
                (*head)->prev = NULL;
            }
        }
        else if (current == *tail)
        {
            *tail = current->prev;
            (*tail)->next = NULL;
        }
        else
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        current = current->next;
    }
    printf("Average waiting time: %.2f\n", (float)waitingTime / count);
    printf("Processes executed in order: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", completedProcesses[i]->procId);
        printf(" - waiting time: %d\n", completedProcesses[i]->waitingTime);
    }
}
void executeRR(struct PCB **head, struct PCB **tail, int quantum)
{
    int time = 0;
    int waitingTime = 0;
    int count = 0;
    struct PCB *completedProcesses[10];
    struct PCB *current = *head;
    while (current != NULL)
    {
        if (time >= current->arrivalTime)
        {
            printf("Executing process %d with CPU burst %d\n", current->procId, current->cpuBurst);
            if (current->cpuBurst > quantum)
            {
                time += quantum;
                current->cpuBurst -= quantum;
                current->waitingTime = time - current->arrivalTime;
                waitingTime += current->waitingTime;
                struct PCB *temp = current;
                current = current->next;
                insertRR(head, tail, temp);
            }
            else
            {
                time += current->cpuBurst;
                current->waitingTime = time - current->arrivalTime;
                waitingTime += current->waitingTime;
                completedProcesses[count] = current;
                count++;
                if (current == *head)
                {
                    *head = current->next;
                    if (*head != NULL)
                    {
                        (*head)->prev = NULL;
                    }
                }
                else if (current == *tail)
                {
                    *tail = current->prev;
                    (*tail)->next = NULL;
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                current = current->next;
            }
        }
        else
        {
            current = current->next;
        }
    }
    printf("Average waiting time: %.2f\n", (float)waitingTime / count);
    printf("Processes executed in order: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", completedProcesses[i]->procId);
        printf(" - waiting time: %d\n", completedProcesses[i]->waitingTime);
    }
}

int main()
{
    struct PCB *headPriority = NULL;
    struct PCB *tailPriority = NULL;
    struct PCB *headRR = NULL;
    struct PCB *tailRR = NULL;

    struct PCB *p1 = createPCB(1, 0, 5, 2);
    struct PCB *p2 = createPCB(2, 1, 3, 1);
    struct PCB *p3 = createPCB(3, 2, 8, 3);
    struct PCB *p4 = createPCB(4, 3, 6, 2);
    struct PCB *p5 = createPCB(5, 4, 4, 1);

    insertPriority(&headPriority, &tailPriority, p1);
    insertPriority(&headPriority, &tailPriority, p2);
    insertPriority(&headPriority, &tailPriority, p3);
    insertPriority(&headPriority, &tailPriority, p4);
    insertPriority(&headPriority, &tailPriority, p5);

    insertRR(&headRR, &tailRR, p1);
    insertRR(&headRR, &tailRR, p2);
    insertRR(&headRR, &tailRR, p3);
    insertRR(&headRR, &tailRR, p4);
    insertRR(&headRR, &tailRR, p5);

    printf("Priority Scheduling\n");
    executePriority(&headPriority, &tailPriority);

    // printf("\nRound Robin Scheduling\n");
    // executeRR(&headRR, &tailRR, 2);

    return 0;
}