#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void listDirectoryContents(const char *dirname) {
    printf("Contents of '%s':\n", dirname);
    DIR *dir = opendir(dirname);
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
    }
    printf("\n");
}

int main() {
    // List directory contents before creating the directory
    listDirectoryContents(".");

    // Create a new directory
    if (mkdir("my_directory", 0777) == 0) {
        printf("Directory 'my_directory' created successfully.\n");
    } else {
        perror("mkdir");
        return 1;
    }

    // List directory contents after creating the directory
    listDirectoryContents(".");

    // Remove the directory
    if (rmdir("my_directory") == 0) {
        printf("Directory 'my_directory' deleted successfully.\n");
    } else {
        perror("rmdir");
        return 1;
    }

    // List directory contents after deleting the directory
    listDirectoryContents(".");

    return 0;
}
