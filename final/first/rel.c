#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_file()
{
    FILE *file = fopen("Relation.txt", "w");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void write_to_file()
{
    char content[256];
    printf("Enter the content to write into the file: ");
    fgets(content, sizeof(content), stdin);

    FILE *file = fopen("Relation.txt", "a");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    fclose(file);
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // This is the child process
        create_file();
        exit(EXIT_SUCCESS);
    }
    else
    {
        // This is the parent process
        wait(NULL); // Wait for the child process to complete
        write_to_file();
    }

    return 0;
}
