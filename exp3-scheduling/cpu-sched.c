#include <stdio.h>
#include <stdlib.h>

struct PCB {
    int procId;
    int cpuBurst;
    int waitingTime;
    struct PCB *next;
    struct PCB *prev;
};

struct PCB *createPCB(int procId, int cpuBurst) {
    struct PCB *newPCB = (struct PCB *)malloc(sizeof(struct PCB));
    newPCB->procId = procId;
    newPCB->cpuBurst = cpuBurst;
    newPCB->waitingTime = 0;
    newPCB->next = NULL;
    newPCB->prev = NULL;
    return newPCB;
}

void insertFCFS(struct PCB **head, struct PCB **tail, struct PCB *newPCB) {
    if (*head == NULL) {
        *head = newPCB;
        *tail = newPCB;
    } else {
        (*tail)->next = newPCB;
        newPCB->prev = *tail;
        *tail = newPCB;
    }
}

void insertRR(struct PCB **head, struct PCB **tail, struct PCB *newPCB) {
    if (*head == NULL) {
        *head = newPCB;
        *tail = newPCB;
        newPCB->next = newPCB;
        newPCB->prev = newPCB;
    } else {
        (*tail)->next = newPCB;
        newPCB->prev = *tail;
        newPCB->next = *head;
        (*head)->prev = newPCB;
        *tail = newPCB;
    }
}



void executeFCFS(struct PCB **head, struct PCB **tail) {
    int time = 0;
    int waitingTime = 0;
    int count = 0;
    struct PCB *completedProcesses[10];
    struct PCB *current = *head;
    while (current != NULL) {
        printf("Executing process %d with CPU burst %d\n", current->procId, current->cpuBurst);
        time += current->cpuBurst;
        current->waitingTime = time - current->cpuBurst;
        waitingTime += current->waitingTime;
        completedProcesses[count] = current;
        count++;
        current = current->next;
    }
    printf("\nAverage waiting time: %.2f\n", (float)waitingTime / count);
    printf("Order of completion: \n");
    for (int i = 0; i < count; i++) {
        printf("%d ", completedProcesses[i]->procId);
        printf(" - waiting time: %d\n", completedProcesses[i]->waitingTime);
    }
}

void executeRR(struct PCB **head, struct PCB **tail, int timeQuantum) {
    int originalBurst[10] = {0};
    struct PCB *temp = *head;
    for (int i = 0; i < 10; i++) {
        if (temp == NULL) {
            break;
        }
        originalBurst[temp->procId] = temp->cpuBurst;
        temp = temp->next;
    }
    int time = 0;
    int waitingTime = 0;
    int count = 0;
    struct PCB *completedProcesses[10];
    struct PCB *current = *head;
    while (current != NULL) {
        printf("Executing process %d with CPU burst %d\n", current->procId, current->cpuBurst);
        if (current->cpuBurst > timeQuantum) {
            current->cpuBurst -= timeQuantum;
            time += timeQuantum;
            current = current->next;
        } else {
            time += current->cpuBurst;
            current->waitingTime = time - originalBurst[current->procId];
            waitingTime += current->waitingTime;
            completedProcesses[count] = current;
            count++;
            if (current->prev == current) {
                *head = NULL;
                *tail = NULL;
                break;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
        }
    }
    printf("\nAverage waiting time: %.2f\n", (float)waitingTime / count);
    printf("Order of completion: \n");
    for (int i = 0; i < count; i++) {
        printf("%d ", completedProcesses[i]->procId);
        printf(" - waiting time: %d\n", completedProcesses[i]->waitingTime);
    }
}

int main() {
    struct PCB *headFCFS = NULL;
    struct PCB *tailFCFS = NULL;
    struct PCB *headRR = NULL;
    struct PCB *tailRR = NULL;
    insertFCFS(&headFCFS, &tailFCFS, createPCB(1, 10));
    insertFCFS(&headFCFS, &tailFCFS, createPCB(2, 5));
    insertFCFS(&headFCFS, &tailFCFS, createPCB(3, 8));
    insertRR(&headRR, &tailRR, createPCB(1, 10));
    insertRR(&headRR, &tailRR, createPCB(2, 5));
    insertRR(&headRR, &tailRR, createPCB(3, 8));
    printf("Processes added to the queue:\n");
    struct PCB *temp = headFCFS;
    while (temp != NULL) {
        printf("Process %d with CPU burst %d\n", temp->procId, temp->cpuBurst);
        temp = temp->next;
    }
    printf("---\n");
    printf("First Come First Serve\n");
    executeFCFS(&headFCFS, &tailFCFS);
    int timeQuantum = 3;
    printf("\nRound Robin with time quantum = %d\n", timeQuantum);
    executeRR(&headRR, &tailRR, timeQuantum);
    return 0;
}