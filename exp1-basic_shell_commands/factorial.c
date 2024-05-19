#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    
    int num = atoi(argv[1]);
    int result = 1;
    
    if (num < 0) {
        printf("Factorial is not defined for negative numbers\n");
        return 1;
    }
    
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    
    printf("Factorial of %d is %d\n", num, result);
    
    return 0;
}
