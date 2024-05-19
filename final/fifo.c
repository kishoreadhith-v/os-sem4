#include <stdio.h>
#include <stdlib.h>

int fifo(int frames, int len, int *requests){
    int page_faults = 0;
    int queue[frames];
    int queue_size = 0;
    int replace = 0;
    for(int i = 0; i < len; i++){
        printf("Request: %d - ", requests[i]);
        int found = 0;
        for(int j = 0; j < queue_size; j++){
            if(queue[j] == requests[i]){
                found = 1;
                printf("Page Hit\n");
                break;
            }
        }
        if(!found){
            if(queue_size < frames){
                queue[queue_size++] = requests[i];
            } else {
                queue[replace] = requests[i];
                replace = (replace + 1) % frames;
            }
            printf("Page Fault\n");
            printf("Queue: ");
            for(int j = 0; j < queue_size; j++){
                printf("%d ", queue[j]);
            }
            printf("\n");
            page_faults++;
        }
    }
    return page_faults;
}

int main(){
    int frames = 3;
    int len = 7;
    int requests[] = {1, 3, 0, 3, 5, 6, 3};
    int page_faults = fifo(frames, len, requests);
    printf("Page Faults: %d\n", page_faults);
    return 0;
}