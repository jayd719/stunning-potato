/*
-------------------------------------
File:    file_directory.c
Project: Assignment 1
Performs various operations on files, directories, and associated system functions
-------------------------------------
Author:  Jashandeep Singh
ID:      169018282
Email:   sing8282@mylaurier.ca
Version  2024-02-12
-------------------------------------
*/

// IMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

// CONSTANTS
int NUMBER_OF_OPTIONS = 5;
int EXIT_OPTION = 99;
#define BUFFER_LIMIT 125

// FUNCTION DECLARTIONS
void print_menu();
void runner_function();
void clear_buffer();
void create_directory(const char *dir_name, mode_t mode);
void create_directory_aux();
void create_write_file(const char *file_name, const char *content);
void create_write_file_aux();
void read_proc_mem_info_to_file(const char *file_name);
void read_proc_mem_info_to_file_aux();
void directory_listing(const char *start_dir);
void directory_listing_aux();
void remove_directory(const char *dir_name);
void remove_directory_aux();

/**
 * Main Function
 *
 */
int main(int argc, char *aa[])
{
    runner_function();
    return 0;
}

/**
 * Displays a menu of options for file and directory operations.
 *
 * @return void
 */
void print_menu()
{
    printf("-----Menu-----\n");
    printf("1:  Create a directory\n");
    printf("2:  Create and write to a file\n");
    printf("3:  Write contents of /proc/meminfo to a file\n");
    printf("4:  List directory contents\n");
    printf("5:  Remove a directory\n");
    printf("99.  Quit\n");
    printf("Enter you choice: ");
}

/**
 * Main runner function to handle user input and execute the corresponding functionality.
 *
 *
 * @param void - This function does not accept any parameters.
 * @return void - This function does not return a value.
 */
void runner_function()
{
    int user_input;

    while (user_input != EXIT_OPTION)
    {
        
        // print menu for user
        print_menu();
        // reads and stores input
        scanf("%d", &user_input);

        switch (user_input)
        {
        case 1:
            clear_buffer();
            create_directory_aux();
            break;
        case 2:
            clear_buffer();
            create_write_file_aux();
            break;
        case 3:
            clear_buffer();
            read_proc_mem_info_to_file_aux();
            break;
        case 4:
            clear_buffer();
            directory_listing_aux();
            break;

        case 5:
            clear_buffer();
            remove_directory_aux();
            break;

        default:
            clear_buffer();
            printf("Enter Numbers Between 1 to %d\n\n", NUMBER_OF_OPTIONS);
            continue;
        }
    }
}
/**
 *  Clear invalid input from buffer
 *
 * @return void
 */
void clear_buffer()
{
    while (getchar() != '\n')
    {
    };
}

/**
 * Auxiliary function to create a directory by prompting the user for input.
 *
 * @param void - This function does not accept any parameters.
 * @return void - This function does not return a value.
 */
void create_directory_aux()
{
    char dir_name[BUFFER_LIMIT];
    int mode;
    // User Prompt for Directory Name
    printf("Enter the directory name you want to create:\n");
    scanf("%[^\n]%*c", dir_name);

    // User Prompt for permissions for the new directory
    printf("Enter mode of the created directory(in octal, e.g., 0775):\n");
    scanf("%d", &mode);

    // Call function to create the directory, pass directory and permission as parameter
    create_directory(dir_name, mode);
}
/**
 * Creates a directory with the specified name and mode.
 *
 * @param const char *dir_name - The name of the directory to be created.
 * @param mode_t mode - The file permissions for the new directory
 *
 * @return void - This function does not return a value.
 */
void create_directory(const char *dir_name, mode_t mode)
{
    // C function to create new Directory
    if (mkdir(dir_name, mode) == -1)
    {
        // log error number if failed to create new directory
        printf("Failed to create given directory Error: %d\n", errno);
    }
    else
    {
        // success message
        printf("The directory %s is created successfully with mode %d\n", dir_name, mode);
    }
}

/**
 * Auxiliary function to create and write to a file by prompting the user for input.
 *
 * @param void - This function does not accept any parameters.
 * @return void - This function does not return a value.
 */
void create_write_file_aux()
{
    // User prompt for file name
    char filename[BUFFER_LIMIT];
    printf("Enter the file name you want to create:\n");
    scanf("%[^\n]%*c", filename);

    // User prompt for file content
    char content[BUFFER_LIMIT * 4];
    printf("Enter the contents that you want to write you file:\n");
    scanf("%[^\n]%*c", content);

    // using the main file create function write to file
    create_write_file(filename, content);
}
/**
 * Creates a file and writes the specified content to it.
 *
 * @param const char *file_name - The name of the file to be created or written.
 * @param const char *content - The content to be written to the file.
 *
 * @return void - This function does not return a value.
 */
void create_write_file(const char *file_name, const char *content)
{
    // Create or open the file with write-only permissions
    int file = creat(file_name, O_WRONLY | O_CREAT);
    if (file == -1)
    {
        // Print error if file creation failed
        printf("Failed to create file '%s', Error: %d\n", file_name, errno);
        return;
    }

    // Write content to the file
    ssize_t written = write(file, content, strlen(content));
    if (written == -1)
    {
        // Print error if writing to the file failed
        printf("Failed to write to file '%s', Error: %d\n", file_name, errno);
    }
    else
    {
        printf("File %s is created and written successfully.\n", file_name);
    }

    // Close the file descriptor
    close(file);
}
/**
 * Auxiliary function to read memory information from /proc/meminfo and store it in a file.
 *
 *
 * @param void - This function does not accept any parameters.
 * @return void - This function does not return a value.
 */
void read_proc_mem_info_to_file_aux()
{
    // User prompt for file name
    char filename[BUFFER_LIMIT];
    printf("Enter the file you want to store memory information to:\n");
    scanf("%[^\n]%*c", filename);

    // using the main write to file
    read_proc_mem_info_to_file(filename);
}

/**
 * Reads memory information from /proc/meminfo and writes it to a specified file.
 *
 * @param const char *file_name - The name of the file to write the memory information to.
 *
 * @return void - This function does not return a value.
 */
void read_proc_mem_info_to_file(const char *file_name)
{

    // open proc file
    int file_source = open("/proc/meminfo", O_RDONLY);
    if (file_source == -1)
    {
        printf("Failed to open /proc/meminfo, Error No. %d\n", errno);
        return;
    }

    // Open the destination file to write
    int file_dest = open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
    if (file_dest == -1)
    {
        printf("Failed to create Destination file, Error No. %d\n", errno);
        return;
    }

    char buffer[BUFFER_LIMIT];
    ssize_t size_read;
    while ((size_read = read(file_source, buffer, BUFFER_LIMIT)) > 0)
    {
        if (write(file_dest, buffer, size_read) == -1)
        {
            printf("Failed to write to the destination file, Error No. %d\n", errno);
            break;
        }
    }
    if (size_read == -1)
    {
        printf("Failed to read /proc/meminfo, Error No. %d\n", errno);
    }
    // Close the files
    close(file_source);
    close(file_dest);

    printf("Proc info written to %s successfully.\n", file_name);
}

/**
 * Auxiliary function to list the contents of a specified directory by prompting the user for input.
 *
 * @param void - This function does not accept any parameters.
 * @return void - This function does not return a value.
 */
void directory_listing_aux()
{
    char filename[BUFFER_LIMIT];
    printf("Enter the directory name you want to list the contents for (if you want to list the current directory, then pass  '.'):\n");
    scanf("%[^\n]%*c", filename);
    directory_listing(filename);
}
/**
 * Recursively lists the contents of a specified directory.
 *
 * @param const char *start_dir - The name or path of the directory to list.
 *
 * @return void - This function does not return a value.
 */
void directory_listing(const char *start_dir)
{
    DIR *dir = opendir(start_dir);

    if (dir == NULL)
    {
        printf("Failed to open the directory: %s\n", start_dir);
        return;
    }

    struct dirent *dir_content;
    char path[BUFFER_LIMIT] = {0};
    // Read directory contents
    while ((dir_content = readdir(dir)) != NULL)
    {
        printf("%s\n", dir_content->d_name);
        if ((dir_content->d_type == DT_DIR) && (strcmp(dir_content->d_name, "..") != 0) && (strcmp(dir_content->d_name, ".")))
        {

            // Construct the full path
            strcat(path, start_dir);
            strcat(path, "/");
            strcat(path, dir_content->d_name);
            directory_listing(path);
        }
    }

    closedir(dir);
}

/**
 * Auxiliary function to remove a directory by prompting the user for input.
 *
 * @param void - This function does not accept any parameters.
 * @return void - This function does not return a value.
 */
void remove_directory_aux()
{
    // User prompt for getting the directory name to be removed
    char filename[BUFFER_LIMIT];
    printf("Enter the directory name you want to remove:\n");
    scanf("%[^\n]%*c", filename);

    char confirmation;
    printf("You are about to delete the directory and it's content recursively. Proceed? (y/n) ");
    confirmation = getchar();

    if (confirmation != 'y')
    {
        return;
    }
    remove_directory(filename);
}
/**
 * Recursively removes a directory and its contents.
 *
 * @param const char *dir_name - The name or path of the directory to be removed.
 *
 * @return void - This function does not return a value.
 */
void remove_directory(const char *dir_name)
{
    DIR *dir = opendir(dir_name);

    if (dir == NULL)
    {
        printf("Failed to open directory: %s\n", dir_name);
        return;
    }

    struct dirent *dir_content;
    char path[BUFFER_LIMIT];

    // Loop through directory contents
    while ((dir_content = readdir(dir)) != NULL)
    {
        // Skip current directory and parent directory
        if (strcmp(dir_content->d_name, ".") == 0 || strcmp(dir_content->d_name, "..") == 0)
        {
            continue;
        }

        // Construct the full path of the file/directory
        // snprintf(path, BUFFER_LIMIT, "%s/%s", dir_name, dir_content->d_name);
        strcpy(path, dir_name);
        strcat(path, "/");
        strcat(path, dir_content->d_name);

        if (dir_content->d_type == DT_DIR)
        {
            remove_directory(path);
        }
        else // If it's a file, remove it
        {
            if (unlink(path) != 0)
            {
                printf("Failed to remove file: %s\n", path);
            }
        }
    }

    closedir(dir);

    // Finally, remove the directory itself
    if (rmdir(dir_name) != 0)
    {
        printf("Failed to remove directory: %s\n", dir_name);
    }
}