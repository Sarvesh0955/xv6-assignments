#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *dir_name) {
    struct dirent *entry;
    DIR *dir = opendir(dir_name);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        printf("%s\n", path);

        struct stat entry_stat;
        if (stat(path, &entry_stat) == 0 && S_ISDIR(entry_stat.st_mode)) {
            list_files(path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *start_dir = (argc > 1) ? argv[1] : ".";
    list_files(start_dir);
    return 0;
}
