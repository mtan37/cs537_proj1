#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "processes.h"

#define BUFSIZE 50

char* stringconcat(char* string1, char* string2) {
    char* newString = (char*) malloc(strlen(string1) + strlen(string2) + 1);
    if (newString == NULL) {
        printf("New string did not have enough memory.\n");
        return NULL;
    }
    strcat(newString, string1);
    strcat(newString, string2);
    return newString;
}

processNode* getProcessList() {
    DIR *processes; // pointer to /proc
    DIR *subdirectory; // current process directory in /proc
    struct dirent *processInfo; // current subdirectory info
    char *proc = "/proc/";
    int uid = getuid();  // uid
    FILE *uidFinder;  // gets uid of the process
    int uidLine;  // the line that holds the uid
    char buf[BUFSIZE]; //line in stat file with uid
    char *fileName;  // the file to open

    processNode *head = (processNode*) malloc(sizeof(processNode));
    processNode *curr = head;

    processes = opendir("/proc/");
    if (processes == NULL) {
        free(curr);
        free(processes);
        return NULL;
    }

    processInfo = readdir(processes);
    while (processInfo != NULL) {
        char *processDirectory = stringconcat(proc, processInfo->d_name);
	if (processDirectory == NULL) {
            free(curr);
	    return NULL;
        }

	if ((atoi(processInfo->d_name) != 0) && (subdirectory = opendir(processDirectory)) != NULL){
            uidLine = 0;
            fileName = (char*) malloc(sizeof(processDirectory) + sizeof(char) * 7 + 1);
            strcpy(fileName, processDirectory);
            strcat(fileName, "/status");

            uidFinder = fopen(fileName, "r");
            if (uidFinder != NULL){
                while (uidLine < 9){
                    fgets(buf, BUFSIZE, uidFinder);
                    uidLine++;
                }
                fclose(uidFinder);

                char *uidStore;
                char *charPtr = buf;
                uidLine = 0;

                uidStore =  strtok_r(charPtr, "\t", &charPtr);
                while (uidStore != NULL && uidLine < 2){
                    if (uid == atoi(uidStore)){
                        curr->pid = malloc(1 + sizeof(processInfo->d_name));
                        strcpy(curr->pid, processInfo->d_name);
                        curr->next = malloc(sizeof(processNode));
                        curr = curr->next;
                        curr->pid = NULL;
                    }
                    uidLine++;
                }
            }

            free(fileName);
            if (closedir(subdirectory) == -1){
                free(curr);
                free(processDirectory);
                return NULL;
            }
        }
    free(processDirectory);
    }
    if(closedir(processes) == -1) {
        free(curr);
        return NULL;
    }
    return head;
}

int getProcess(char* pid){
    DIR *processes;  // pointer to /proc
    DIR *subdirectory;  // current process directory in /proc
    struct dirent *processInfo;  // current subdirectory  info
    char *proc = "/proc/";
    FILE *uidFinder;  // gets uid of the process
    char *fileName;  // the file to open

    processes = opendir("/proc/");
    if (processes == NULL) {
        free(processes);
        return 0;
    }

    processInfo = readdir(processes);
    while (processInfo != NULL) {
        if (atoi(pid) == atoi(processInfo->d_name)) {
            char* processDirectory = stringconcat(proc, processInfo->d_name);
            if (processDirectory == NULL) {
                return 0;
            }

	    subdirectory = opendir(processDirectory);
            if (subdirectory != NULL) {
                fileName = (char*) malloc(sizeof(processDirectory) + sizeof(char) * 7 + 1);
                strcpy(fileName, processDirectory);
                strcat(fileName, "/status");

                uidFinder = fopen(fileName, "r");
                if (uidFinder != NULL) {
                    fclose(uidFinder);
                    free(fileName);
                    if (closedir(subdirectory) == -1) {
                         free(processDirectory);
                         return 0;
                    }
                    free(processDirectory);
                    if(closedir(processes) == -1){
                        return 0;
                    }
                    return 1;
                }
                else {
                    fclose(uidFinder);
                    free(fileName);
                    if (closedir(subdirectory) == -1) {
                        free(processDirectory);
                        return 0;
                    }
                    free(processDirectory);
                    if (closedir(processes) == -1) {
                        return 0;
                    }
                    return 0;
                }
	    
                free(fileName);
                 if(closedir(subdirectory) == -1) {
                    return 0;
                }
            }
            free(processDirectory);
        }
    }
    if (closedir(processes) == -1) {
        return 0;
    }
    return -1;
}
