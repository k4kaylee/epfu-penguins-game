#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include "dirent.h"
#else
    #include <dirent.h>
#endif



char** dirList = 0;
int amountOfFiles = 0;

void getFiles() {

    DIR* directory;
    struct dirent* dir;
    directory = opendir("programs");
    dir = 0;
    if (directory)
    {
        while ((dir = readdir(directory)) != NULL)
        {
            if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
                amountOfFiles++;
            }
        }
    }
    else {
        printf("ERROR: directory is not found. Make sure you have 'programs' directory and it is not empty.\n");
        return;
    }

    rewinddir(directory);
    dirList = malloc(sizeof(char[20]) * amountOfFiles);

    int i = 0;
    while ((dir = readdir(directory)) != NULL) {
        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
        {
        }
        else {
            dirList[i] = (char*)malloc(strlen(dir->d_name) + 1);
            strcpy(dirList[i], dir->d_name);
            i++;
        }
    }
    closedir(directory);

}

void printFiles() {
    for (int i = 0; i < amountOfFiles; i++) {
        printf("%d: %s\n", i + 1, dirList[i]);
    }
}