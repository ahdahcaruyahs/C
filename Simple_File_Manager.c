#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> // For _getcwd on Windows
//#include <unistd.h> // For getcwd on Unix-like systems

#define BUFFER_SIZE 1024

// Global variable
char text[BUFFER_SIZE];

void create_file() {
    char filepath[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    printf("Enter the full path or relative path to create the file: "); //e.g C:\Users\Desktop\filename.txt
    fgets(filepath, BUFFER_SIZE, stdin);
    filepath[strcspn(filepath, "\n")] = '\0'; // Remove newline character if present

    printf("Filepath entered: %s\n", filepath); // Debugging output

    FILE* file;
    errno_t err;

    // Attempt to open file
    if ((err = fopen_s(&file, filepath, "w")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    printf("Enter text (Ctrl+Z to save and exit):\n");
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        if (strcmp(buffer, "Ctrl+Z\n") == 0) {
            break;
        }
        fputs(buffer, file);
    }

    fclose(file);
    printf("File created and saved successfully.\n");
}

void show_status(const char* filename) {
    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename, "r")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    int line_count = 0;
    int char_count = 0;
    char buffer[BUFFER_SIZE];
    long file_size = 0;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        line_count++;
        char_count += strlen(buffer);
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);

    fclose(file);

    const char* size_unit;
    double display_size;

    if (file_size < 1024) {
        size_unit = "bytes";
        display_size = file_size;
    }
    else if (file_size < 1024 * 1024) {
        size_unit = "KB";
        display_size = file_size / 1024.0;
    }
    else if (file_size < 1024 * 1024 * 1024) {
        size_unit = "MB";
        display_size = file_size / (1024.0 * 1024.0);
    }
    else {
        size_unit = "GB";
        display_size = file_size / (1024.0 * 1024.0 * 1024.0);
    }

    printf("File: %s | Lines: %d | Characters: %d | Size: %.2f %s (%ld bytes)\n\n", filename, line_count, char_count, display_size, size_unit, file_size);
}

void open_file() {
    char filepath[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    printf("Enter the full path or relative path of the file to open: ");
    fgets(filepath, BUFFER_SIZE, stdin);
    filepath[strcspn(filepath, "\n")] = '\0'; // Remove newline character if present

    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filepath, "r")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    printf("\nFile content:\n");
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    show_status(filepath);
}

void find_in_file() {
    char filename[BUFFER_SIZE];
    char search_term[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int line_number = 1;
    int found = 0;

    printf("Enter the filename to search in: ");
    fgets(filename, BUFFER_SIZE, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

    printf("Enter the term to search for: ");
    fgets(search_term, BUFFER_SIZE, stdin);
    search_term[strcspn(search_term, "\n")] = '\0'; // Remove newline character if present

    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename, "r")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, search_term) != NULL) {
            printf("Found on line %d: %s", line_number, buffer);
            found = 1;
        }
        line_number++;
    }

    if (!found) {
        printf("Term '%s' not found in the file.\n", search_term);
    }

    fclose(file);
}

void save_as() {
    char old_filename[BUFFER_SIZE];
    char new_filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    printf("Enter the filename to save as: ");
    fgets(old_filename, BUFFER_SIZE, stdin);
    old_filename[strcspn(old_filename, "\n")] = '\0'; // Remove newline character if present

    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, old_filename, "r")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    printf("Enter the new filename: ");
    fgets(new_filename, BUFFER_SIZE, stdin);
    new_filename[strcspn(new_filename, "\n")] = '\0'; // Remove newline character if present

    FILE* new_file;
    if (fopen_s(&new_file, new_filename, "w") != 0) {
        printf("Error creating new file!\n");
        fclose(file);
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        fputs(buffer, new_file);
    }

    fclose(file);
    fclose(new_file);
    printf("File saved as %s.\n", new_filename);
}

void write_to_file() {
    char filename[BUFFER_SIZE];

    printf("Enter the filename to write to: ");
    fgets(filename, BUFFER_SIZE, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename, "w")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    printf("Enter text to write (type 'Ctrl+Z' to save and exit):\n");
    while (fgets(text, BUFFER_SIZE, stdin) != NULL) {
        if (strcmp(text, "Ctrl+Z\n") == 0) {
            break;
        }
        fputs(text, file);
    }

    fclose(file);
    printf("Text written to file '%s' successfully.\n", filename);
}

void append_file() {
    char filename[BUFFER_SIZE];

    printf("Enter the filename to append to: ");
    fgets(filename, BUFFER_SIZE, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename, "a")) != 0) {
        printf("Error %d: ", err);
        switch (err) {
        case EINVAL:
            printf("Invalid mode provided or filename is NULL.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
        return;
    }

    printf("Enter text to append (type 'Ctrl+Z' to save and exit):\n");
    while (fgets(text, BUFFER_SIZE, stdin) != NULL) {
        if (strcmp(text, "Ctrl+Z\n") == 0) {
            break;
        }
        fputs(text, file);
    }

    fclose(file);
    printf("File appended and saved successfully.\n");
}

int main() {
    int choice;

    while (1) {
        printf("Simple File Management Program\n");
        printf("1. Create File\n");
        printf("2. Open File\n");
        printf("3. Append to File\n");
        printf("4. Find in File\n");
        printf("5. Save As\n");
        printf("6. Write to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);
        getchar();  // Consume the newline character left by scanf

        switch (choice) {
        case 1:
            create_file();
            break;
        case 2:
            open_file();
            break;
        case 3:
            append_file();
            break;
        case 4:
            find_in_file();
            break;
        case 5:
            save_as();
            break;
        case 6:
            write_to_file();
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
