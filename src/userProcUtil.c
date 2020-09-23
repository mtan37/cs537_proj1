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
 *  Return null if the file pointed at the file path doesn't exist
 */
FILE *fileOpener(const char *pid, int flag){
    char *path_tmp = calloc(1,BUFSIZE);
    //TODO: handling error for calloc
    strncpy(path_tmp,"/proc/\0",BUFSIZE);
    char *path = stringConcat(path_tmp, pid);
    free(path_tmp);
    path_tmp = path;//point path_tmp to path to use in later free function
    //flag = 1 is for opening stat file
    if(1 == flag){
        path = stringConcat(path,"/stat");
    }
    //flag = 2 is for opening statm file
    else if(2 == flag){
        path = stringConcat(path,"/statm");
    }
    //flag = 3 is for opening cmdline file 
    else if(3 == flag){
        path = stringConcat(path,"/cmdline");
    }
    //flag = 4 is for opening maps file 
    else if(4 == flag){
        path = stringConcat(path,"/maps");
    }
    //flag = 5 is for opening mems file 
    else if(5 == flag){
        path = stringConcat(path,"/mem");
    }
    else{
        printf("Error: Invalid filer opener flag: %d", flag);
        exit(1);
    }
        
    free(path_tmp);//re-free path_tmp that is currently pointing at the old path var
    if(5 == flag){
        int pid_int = atoi(pid);
        if(0 != pid_int){
            int ptraceReturn = ptrace(PTRACE_ATTACH, pid_int, 0, 0);
            if (ptraceReturn == -1){
               return NULL;
            }
            waitpid(pid_int, NULL, 0);
        }
        else{
            printf("Error: can't read non-int pid input");
            return NULL;
        }
    }
    //open and read file
	FILE *file = fopen(path,"r");
    if(file == NULL){//in the case of the file doesn't exist
        free(path);
        return NULL;
    }
    free(path);
    return file;
}

/*
 * Return the head of a linked list of all the processes owned by the uid
 */
ProcessNode* getProcessesList(unsigned int uid) {
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
    ProcessNode *end = NULL;
    processes = opendir(proc);
    if (processes == NULL) {
        free(curr);
        closedir(processes);
        return NULL;
    }

    while ((processInfo = readdir(processes)) != NULL) {
        char *processDirectory = stringConcat(proc, processInfo->d_name);
	    printf("%s\n",processDirectory);
        if (processDirectory == NULL) {
            free(curr);
            return NULL;
        }
        char *charPtr;
        if (0 != strtol(processInfo->d_name,&charPtr,10)
                && '\0' == *charPtr){
            subdirectory = opendir(processDirectory);
            if (NULL == subdirectory){
               continue; 
            }else{//only proceed if the subdirectory is opened successefully 
                uidLine = 0;
                fileName = stringConcat(processDirectory,"/status"); 
                uidFinder = fopen(fileName, "r");
                if (uidFinder != NULL){
                    while (uidLine < 9){
                        fgets(buf, BUFSIZE, uidFinder);
                        uidLine++;
                    }
                    fclose(uidFinder);

                    char *uidStore;
                    uidLine = 0;
                    
                    //skip the first header token
                    uidStore = strtok_r(buf, "\t", &charPtr);
                    uidStore = strtok_r(NULL, "\t", &charPtr);
                    printf("uid of the process: %s\n",uidStore);
                    //no check in place
                    //if status file is corrupted, the if will not be entered
                    if (uid == atoi(uidStore)){
                        curr->pid = malloc(sizeof(processInfo->d_name));
                        strcpy(curr->pid, processInfo->d_name);
                        curr->next = malloc(sizeof(ProcessNode));
                        printf("curr pid: %s\n", curr->pid);
                        end = curr;
                        curr = curr->next;
                        curr->pid = NULL;
                    }
                }
                free(fileName);
                if (-1 == closedir(subdirectory)){
                    free(curr->pid);
                    free(curr->next);
                    free(curr);
                    free(processDirectory);
                    return NULL;
                }
            }
        }
        free(processDirectory);
    }
    if(NULL != end){
        free(end->next);
        end->next = NULL; 
    }
    //out of the while reading loop
    if(-1 == closedir(processes)) {
        free(curr);
        return NULL;
    }
    return head;
}
