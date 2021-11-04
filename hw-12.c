#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    char filePath[100];
    //I have to do this because somehow filePath always gets initalized at the worst locations
    int i;
    for (i = 0; i < 100; i++){
        filePath[i] = '\0';
    }
    if (argc > 1)
    {
        strncpy(filePath, argv[1], 100);
    }
    else
    {
        printf("Please provide a directory to look at:\n");
        read(STDIN_FILENO, filePath, sizeof(filePath));
        int filePathLen = strlen(filePath);
        printf("%d", filePathLen);
        filePath[filePathLen - 1] = '\0';
    }
    DIR *directory;
    directory = opendir(filePath);
    if (errno != 0)
    {
        printf("Error: %s", strerror(errno));
        return 0;
    }
    struct dirent *entry;
    struct stat *fileInfo;
    entry = readdir(directory);
    int total = 0;
    printf("STATS FOR DIR: %s\n", filePath);
    while (entry)
    {
        printf("%s ", entry->d_name);
        fileInfo = malloc(sizeof(struct stat));
        stat(entry->d_name, fileInfo);
        if (entry->d_type == DT_REG){
            total += fileInfo->st_size;
            printf("is a regular file\n");
        }else if(entry->d_type == DT_DIR){
            printf("is a directory\n");
        }else{
            printf("is other file\n");
        }
        free(fileInfo);
        entry = readdir(directory);
    }
    printf("Total directory size: %d\n", total);
}