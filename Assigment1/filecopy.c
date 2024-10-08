#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Function declarations
int get_input_file(const char *filename);
int get_output_file(const char *filename);
int process_files(int input_file, int output_file);

/**
 * Main function for copying contents from an input file to an output file.
 *
 * @param int argc - The number of command-line arguments.
 * @param char *argv[] - Array of command-line arguments.
 *                       argv[1] is the input file, argv[2] is the output file.
 *
 * @return int - Returns 0 on successful execution.
 */
int main(int argc, char *argv[])

{
    // if not enough arguments are entered by the user.
    if (argc < 3)
    {
        printf("Insufficient parameters passed\n");
        return 0;
    }
    // Catch the arguments passed by user in variables
    char *input_file = argv[1];
    char *output_file = argv[2];

    process_files(get_input_file(input_file), get_output_file(output_file));

    // print success message
    printf("The contents of file %s have been successfully copied into the %s file.\n", input_file, output_file);
    return 0;
}
/**
 * Creates and opens the output file for writing.
 *
 * @param const char *file_name - The name or path of the file to create and open for writing.
 *
 * @return int - The file descriptor of the opened output file.
 */
int get_output_file(const char *file_name)
{
    int fd;
    fd = creat(file_name, O_CREAT);
    if (fd == -1)
    {
        perror("Failed to create output file");
        exit(-1);
    }
    return open(file_name, O_WRONLY);
}

/**
 * Opens the input file for reading.
 *
 * @param const char *file_name - The name or path of the file to open for reading.
 *
 * @return int - The file descriptor of the opened input file.
 */
int get_input_file(const char *file_name)
{
    int fd;
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open input file");
        exit(-1);
    }

    return fd;
}

/**
 * Processes the input and output files by copying the contents from the input file to the output file.
 *
 * @param const int input_file - The file descriptor of the input file.
 * @param const int output_file - The file descriptor of the output file.
 *
 * @return int - status
 */
int process_files(const int input_file, const int output_file)
{
    char buffer[BUFFER_SIZE];

    size_t bytes_read;
    while ((bytes_read = read(input_file, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(output_file, buffer, bytes_read) == -1)
        {
            perror("Failed to write to output file");
            exit(-1);
        }
    }

    if (bytes_read == -1)
    {
        perror("Failed to read from input file");
        exit(-1);
    }

    close(input_file);
    close(output_file);

    return 0;
}