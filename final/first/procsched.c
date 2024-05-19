#include <stdio.h>
#include <stdlib.h>

struct PCB
{
    int pid;
    int arrivalTime;
    int cpuBurst;
    int priority;
    int waitingTime;
    struct PCB *next;
    struct PCB *prev;
};

struct PCB *createPCB(int pid, int arrivalTime, int cpuBurst, int priority)
{
    struct PCB *newPCB = (struct PCB *)malloc(sizeof(struct PCB));
    newPCB->pid = pid;
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
        while (current != NULL && current->arrivalTime < newPCB->arrivalTime)
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