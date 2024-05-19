#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    if (num < 0) {
        printf("Armstrong numbers are defined only for non-negative integers.\n");
        return 1;
    }

    int original_num = num;
    int sum = 0;
    int num_digits = 0;

    // Counting the number of digits in the given number
    while (num != 0) {
        num_digits++;
        num /= 10;
    }

    num = original_num;

    // Calculating the sum of the power of digits
    while (num != 0) {
        int digit = num % 10;
        sum += pow(digit, num_digits);
        num /= 10;
    }

    if (sum == original_num) {
        printf("%d is an Armstrong number.\n", original_num);
    } else {
        printf("%d is not an Armstrong number.\n", original_num);
    }

    return 0;
}
