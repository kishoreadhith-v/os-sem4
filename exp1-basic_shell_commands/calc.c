#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 4) {
        // Arithmetic operation with command-line arguments
        int result;
        char *endptr;
        int num1 = strtol(argv[1], &endptr, 10);
        char *op = argv[2];
        int num2 = strtol(argv[3], &endptr, 10);
        
        if (strcmp(op, "+") == 0)
            result = num1 + num2;
        else if (strcmp(op, "-") == 0)
            result = num1 - num2;
        else if (strcmp(op, "*") == 0)
            result = num1 * num2;
        else if (strcmp(op, "/") == 0) {
            if (num2 != 0)
                result = num1 / num2;
            else {
                printf("cannot divide by 0\n");
                return 1;
            }
        } else {
            printf("Invalid operator\n");
            return 1;
        }
        
        printf("%s = %d\n", argv[0], result);
    } else if (argc == 2 && strcmp(argv[1], "start") == 0) {
        // Continuous calculator prompt
        printf("Starting calc ... Enter \"exit\" to exit\n");
        char expression[100];
        int a, b, result;
        char op;
        
        while (1) {
            printf("Enter the expression: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = '\0'; // remove newline character
            
            if (strcmp(expression, "exit") == 0)
                break;
                
            if (sscanf(expression, "%d %c %d", &a, &op, &b) == 3) {
                switch (op) {
                    case '+':
                        result = a + b;
                        break;
                    case '-':
                        result = a - b;
                        break;
                    case '*':
                        result = a * b;
                        break;
                    case '/':
                        if (b != 0)
                            result = a / b;
                        else {
                            printf("cannot divide by 0\n");
                            continue;
                        }
                        break;
                    default:
                        printf("Invalid operator\n");
                        continue;
                }
                printf("%s = %d\n", expression, result);
            } else {
                printf("Invalid expression format\n");
            }
        }
    } else {
        printf("Invalid usage, enter a simple expression separated by whitespaces or \"start\" to open in endless mode\n");
        return 1;
    }
    return 0;
}
