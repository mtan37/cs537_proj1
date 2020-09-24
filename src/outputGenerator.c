// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)
#include "outputGenerator.h"
/*
 * Print out header for flags that are set
 */
void printHeader(Flags *flags) {
    printf("%-5sPID  ","");
    if (1 == flags->flag_s) {
        printf("STATE ");
    }
    if (1 == flags->flag_U) {
        printf("USER_TIME ");
    }
    if (1 == flags->flag_S) {
        printf("SYSTEM_TIME ");
    }
    if (1 == flags->flag_v) {
        printf("VIRTUAL_MEMORY ");
    }
    if (1 == flags->flag_c) {
        printf("CMD_LINE%5s ","");
    }
    if (1 == flags->flag_m) {
        printf("MEM");
    }	
}

/*
 * generates the output based on given flags 
 */
void generateOutput(Flags *flags, int uid) {
    int needFreeListPid = 0;
    ProcessNode *head; //points to first process in list
    ProcessNode *curr; //points to whichever process we are on, starting with head
    if (1 == flags->flag_p) { //p flag is present
        head = malloc(sizeof(ProcessNode));
        curr = head;
        ProcessNode *tmpPtr;
        int i = 0;
	int counter = flags->length_p;
        while(i < counter) { //goes through entire list to create the ProcessNodes
            curr->pid = flags->content_p[i];
            curr->next = malloc(sizeof(ProcessNode));
            tmpPtr = curr;
            curr = curr->next;
            i++;
        }
        free(curr);
        tmpPtr->next = NULL;
    } else { // p flag is not present
        //use the process from getProcessesList(uid)
        head = getProcessesList(uid);
        if(head == NULL){
            printf("Current user doesn't own any processes\n");
            exit(1);
        }
        needFreeListPid = 1;
    }
    printHeader(flags); //call function from above to print header here
    curr = head;
    while(curr != NULL) {
        printf("\n");
        //pre-load info for the process to make sure it exist
        //stat info for current ProcessNode
        StatInfo *statInfoVar = statParser(curr->pid);
        //statm info for current ProcessNode
        StatmInfo *statmInfoVar = statmParser(curr->pid);
        //command line info for current ProcessNode
        CmdInfo *cmdInfoVar = cmdlineParser(curr->pid);
        if(NULL == statInfoVar || NULL == statmInfoVar || NULL == cmdInfoVar){
	        free(statInfoVar);
            free(statmInfoVar);
            free(cmdInfoVar);
            curr = curr->next;
            continue;
        }
        printf("%8s: ", curr->pid); //print out the pid of the process
        if (1 == flags->flag_s || 1 == flags->flag_U || 1 == flags->flag_S) { //gets correct info from statInfoVar if flagged
            if (1 == flags->flag_s) {
                printf("%-5s ", statInfoVar->flag_sField);
            }
		
            if (1 == flags->flag_U) {
                printf("%-9s ", statInfoVar->flag_UField);
            }
		
            if (1 == flags->flag_S) {
                printf("%-11s ", statInfoVar->flag_SField);
            }
        }
        
        if (1 == flags->flag_v) { //gets correct info from statmInfoVar if flagged
            printf("%-14s ", statmInfoVar->flag_vField);
        }

        if (1 == flags->flag_c) { //gets correct info from cmdInfoVar if flagged
            printf("[%-11s] ", cmdInfoVar->flag_cField);
        }
	    
        if (1 == flags->flag_m) {
            unsigned char *memContent = readMem(curr->pid, flags->addr_m, flags->length_m);
            if(memContent != NULL){
                printf("%lx: ",flags->addr_m);
                //print the mem content it in a loop
                for(int i = 0; i < flags->length_m;i++){
                    printf("%02x ", memContent[i]);
                }
            }
            else{
                printf("Requested mem range is not mapped\n");
            }
            free(memContent);
        }
        //go to the next ProcessNode in list
	    curr = curr->next;
        free(statInfoVar->flag_sField);
        free(statInfoVar->flag_UField);
        free(statInfoVar->flag_SField);
        free(statmInfoVar->flag_vField);
        free(cmdInfoVar->flag_cField);
        free(statInfoVar);
        free(statmInfoVar);
        free(cmdInfoVar);
    }
    printf("\n");
    //free the linked list struct is it is allocated in this function
    printf("the value of needFreeListPid%d\n", needFreeListPid);
    freeProcessList(head, needFreeListPid);
}

