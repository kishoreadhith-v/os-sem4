#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

bool isPrime(int n){
    if (n <= 1) return false;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

void *printPrimes(void *args){
    int *n = (int *)args;
    for(int i = 0; i <= *n; i++){
        if(isPrime(i)){
            printf("%d ", i);
        }
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <number>\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    pthread_t tid;
    pthread_create(&tid, NULL, printPrimes, &n);
    pthread_join(tid, NULL);
    return 0;
    
}