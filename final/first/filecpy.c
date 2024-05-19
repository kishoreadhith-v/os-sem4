#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1)
    {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1)
    {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read)
        {
            perror("Error writing to destination file");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1)
    {
        perror("Error reading from source file");
        exit(EXIT_FAILURE);
    }

    if (close(source_fd) == -1 || close(dest_fd) == -1)
    {
        perror("Error closing files");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully.\n");
    return 0;
}
