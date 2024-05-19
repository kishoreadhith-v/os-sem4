#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

int *p; // Shared variable

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <goal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int goal = atoi(argv[1]); // Get the goal from command line argument

    // Initialize player turn and random seed
    int playerTurn = 0; // 0 for John, 1 for Michael
    srand(time(NULL) + playerTurn); // Seed for the current player

    // Create shared memory
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    p = (int *)shmat(shmid, NULL, 0);
    if (p == (int *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    *p = 1; // Initialize p to 1

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) { // Error occurred
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process (Michael)
        srand(time(NULL) + 1); // Seed for Michael

        while (*p < goal) {
            int randomNumber = rand() % 8 + 2; // Generate random number from 2 to 9
            *p *= randomNumber; // Multiply p by the random number

            printf("Michael multiplied the number by %d. p = %d\n", randomNumber, *p);
            usleep(500000); // Sleep for 0.5 seconds
        }
    } else { // Parent process (John)
        srand(time(NULL)); // Seed for John

        while (*p < goal) {
            int randomNumber = rand() % 8 + 2; // Generate random number from 2 to 9
            *p *= randomNumber; // Multiply p by the random number

            printf("John multiplied the number by %d. p = %d\n", randomNumber, *p);
            usleep(500000); // Sleep for 0.5 seconds
        }
    }

    // Determine the winner based on player turn after the game ends
    int winner = (playerTurn == 0 && *p >= goal) ? 0 : 1;

    // Print winner
    if (winner == 0) {
        printf("John wins with p = %d!\n", *p);
    } else {
        printf("Michael wins with p = %d!\n", *p);
    }

    // Detach shared memory
    if (shmdt(p) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove shared memory in the parent process only
    if (pid != 0) {
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
