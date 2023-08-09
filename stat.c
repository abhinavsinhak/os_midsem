#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "sample_file.txt"; // Replace with the actual file path

    struct stat fileStat;

    if (stat(filename, &fileStat) == 0) {
        printf("File: %s\n", filename);
        printf("Size: %lld bytes\n", (long long)fileStat.st_size);
        printf("Owner UID: %u\n", fileStat.st_uid);
        printf("Group GID: %u\n", fileStat.st_gid);
        printf("Permissions: %o\n", fileStat.st_mode & 0777);
    } else {
        perror("stat");
        return 1;
    }

    return 0;
}
