#include <stdio.h>
#include <stdlib.h>

void priority(int n, int burst[], int priority[]) {
    int time = 0;
    int waiting_time[n];
    int turnaround_time[n];
    int completion_time[n];
    int completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }
    while (1) {
        int min_priority = 1000;
        int min_priority_index = -1;
        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && priority[i] < min_priority) {
                min_priority = priority[i];
                min_priority_index = i;
            }
        }
        if (min_priority_index == -1) {
            break;
        }
        completion_time[min_priority_index] = time + burst[min_priority_index];
        turnaround_time[min_priority_index] = completion_time[min_priority_index];
        waiting_time[min_priority_index] = turnaround_time[min_priority_index] - burst[min_priority_index];
        completed[min_priority_index] = 1;
        time = completion_time[min_priority_index];
    } 
    printf("Process\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, burst[i], priority[i], waiting_time[i], turnaround_time[i]);
    }   
}

int main() {
    int n = 4;
    int burst[] = {10, 5, 8, 12};
    int p[] = {3, 4, 1, 2};
    priority(n, burst, p);
    return 0;
}