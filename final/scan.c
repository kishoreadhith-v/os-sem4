#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}


int scan(int disk_size, int len, int *requests, int head, int direction){
    int seek_time = 0;
    int left = 0;
    int prev = head;
    int req_sorted[len];
    for(int i = 0; i < len; i++){
        req_sorted[i] = requests[i];
    }
    qsort(req_sorted, len, sizeof(int), compare);

    for (int i = 0; i < len; i++)
    {
        if (req_sorted[i] < head){
            left = i;
        } else {
            break;
        }
    }
    if (direction == 0){
        printf("Seek Sequence is: %d", head);
        for (int i = left; i >= 0; i--){
            printf(" -> %d", req_sorted[i]);
            seek_time += abs(req_sorted[i] - prev);
            prev = req_sorted[i];
        }
        seek_time += abs(prev - 0);
        printf(" -> 0");
        prev = 0;
        for (int i = left + 1; i < len; i++){
            printf(" -> %d", req_sorted[i]);
            seek_time += abs(req_sorted[i] - prev);
            prev = req_sorted[i];
        }
    } else {
        printf("Seek Sequence is: %d", head);
        for(int i = left + 1; i < len; i++){
            printf(" -> %d", req_sorted[i]);
            seek_time += abs(req_sorted[i] - prev);
            prev = req_sorted[i];
        }
        seek_time += abs(prev - disk_size);
        printf(" -> %d", disk_size);
        prev = disk_size;
        for(int i = left; i >= 0; i--){
            printf(" -> %d", req_sorted[i]);
            seek_time += abs(req_sorted[i] - prev);
            prev = req_sorted[i];
        }
    }
    printf("\n");
    return seek_time;
}

int sstf(int disk_size, int len, int *requests, int head){
    int seek_time = 0;
    int prev = head;
    int min, min_index;
    printf("Seek Sequence is: %d", head);
    for (int i = 0; i < len; i++)
    {
        min = disk_size + 1;
        for (int j = 0; j < len; j++)
        {
            if (requests[j] != -1 && abs(requests[j] - prev) < min){
                min = abs(requests[j] - prev);
                min_index = j;
            }
        }
        printf(" -> %d", requests[min_index]);
        seek_time += min;
        prev = requests[min_index];
        requests[min_index] = -1;
    }    
    printf("\n");
    return seek_time;
}

int main(){
    int disk_size, len, head, direction;
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    printf("Enter the number of requests: ");
    scanf("%d", &len);
    int requests[len];
    printf("Enter the requests: ");
    for (int i = 0; i < len; i++){
        scanf("%d", &requests[i]);
    }
    printf("Enter the head position: ");
    scanf("%d", &head);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);
    printf("SCAN:\n");
    int seek_time = scan(disk_size, len, requests, head, direction);
    printf("Total seek time: %d\n", seek_time);
    printf("SSTF:\n");
    seek_time = sstf(disk_size, len, requests, head);
    printf("Total seek time: %d\n", seek_time);
    return 0;
}