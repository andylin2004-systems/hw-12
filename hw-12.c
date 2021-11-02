#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    DIR *directory = opendir("./");
    struct dirent *entry;
    struct stat *fileInfo;
    entry = readdir(directory);
    int total = 0;
    printf("STATS FOR DIR: .\n");
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