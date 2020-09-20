#include "userProcUtil.h"

int BUFSIZE = 50;

/*
 * Return a string that is a deep copy of the contatination of the string1+srting2
 */
char* stringConcat(const char* string1, const char* string2) {
    char* newString = (char*) calloc(1,strlen(string1) + strlen(string2) + 1);
    if (NULL == newString) {
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(-1);
    }
    strcat(newString, string1);
    strcat(newString, string2);
    return newString;
}

/*
 *  open a file under the /proc/<pid>/ directory. The file opened is based on the  *  flag given
 *  flag = 1: /proc/<pid>/stat
 *  flag = 2: /proc/<pid>/statm
 *  flag = 3: /proc/<pid>/cmdline
 *
 */
FILE *fileOpener(const char *pid, int flag){
    char *path_tmp = calloc(1,BUFSIZE);
    //TODO: handling error for calloc
    strncpy(path_tmp,"/proc/\0",BUFSIZE);
    printf("file path - checkpoint #1111: %s\n",path_tmp);
    char *path = stringConcat(path_tmp, pid);
    printf("file path - checkpoint #2222: %s\n",path);
    free(path_tmp);
    path_tmp = path;//point path_tmp to path to use in later free function
    //flag = 1 is for opening stat file
    if(1 == flag){
        path = stringConcat(path,"/stat");
        printf("stat file path: %s\n", path);	
    }
    //flag = 2 is for opening statm file
    else if(2 == flag){
        path = stringConcat(path,"/statm");
        printf("statm file path: %s\n", path);	
    }
    //flag = 3 is for opening cmdline file 
    else if(3 == flag){
        path = stringConcat(path,"/cmdline");
        printf("cmdline file path: %s\n", path);	
    }
    else{
        printf("Error: Invalid filer opener flag: %d", flag);
        exit(1);
    }
        
    printf("file path - checkpoint #3333\n");
    free(path_tmp);//re-free path_tmp that is currently pointing at the old path var
    //open and read file
	FILE *file = fopen(path,"r");
    if(file == NULL){
        printf("Error: File is not opened properly with pid: %s",pid);
        free(path);
        exit(1);
    }
    printf("file path - checkpoint #4444\n");
    free(path);
    return file;
}

/*
 * Return the head of a linked list of all the processes owned by the uid
 */
ProcessNode* getProcessesList(unsigned int uid) {
    printf("Enters function getProcessesList\n");
    DIR *processes; // pointer to /proc
    DIR *subdirectory; // current process directory in /proc
    struct dirent *processInfo; // current subdirectory info
    char *proc = "/proc/";
    FILE *uidFinder;  // gets uid of the process
    int uidLine;  // the line that holds the uid
    char buf[BUFSIZE]; //line in stat file with uid
    char *fileName;  // the file to open

    ProcessNode *head = (ProcessNode*) malloc(sizeof(ProcessNode));
    ProcessNode *curr = head;

    processes = opendir("/proc/");
    if (processes == NULL) {
        free(curr);
        free(processes);
        return NULL;
    }

    processInfo = readdir(processes);
    while (processInfo != NULL) {
        char *processDirectory = stringConcat(proc, processInfo->d_name);
	if (processDirectory == NULL) {
            free(curr);
	    return NULL;
        }

	if ((0 != atoi(processInfo->d_name)) && NULL != (subdirectory = opendir(processDirectory))){
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
                        curr->next = malloc(sizeof(ProcessNode));
                        curr = curr->next;
                        curr->pid = NULL;
                    }
                    uidLine++;
                }
            }

            free(fileName);
            if (-1 == closedir(subdirectory)){
                free(curr);
                free(processDirectory);
                return NULL;
            }
        }
    free(processDirectory);
    }
    if(-1 == closedir(processes)) {
        free(curr);
        return NULL;
    }
    return head;
}