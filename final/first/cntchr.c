#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main()
{
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    if (bytes_read == -1)
    {
        perror("Error reading from stdin");
        return 1;
    }

    printf("Bytes read: %ld\n", bytes_read);
    return 0;
}
