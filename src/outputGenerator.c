#include "outputGenerator.h"
void printHeader(Flags *flags) {
    //print out header
    if (1 == flags->flag_p) {
        printf("PID ");
    }
    if (1 == flags->flag_s) {
        printf("STATE ");
    }
    if (1 == flags->flag_U) {
        printf("USER TIME ");
    }
    if (1 == flags->flag_S) {
        printf("SYSTEM TIME ");
    }
    if (1 == flags->flag_v) {
        printf("VIRTUAL MEMORY ");
    }
    if (1 == flags->flag_c) {
        printf("CMD LINE ");
    }
    if (1 == flags->flag_m) {
        printf("MEM");
    }
    printf("\n");
	
}

void generateOutput(Flags *flags) {
    int needFreeList = 0;
    ProcessNode *head;
    ProcessNode *curr;
    if (1 == flags->flag_p) { //p flag is present
        ProcessNode *head = malloc(sizeof(ProcessNode));
        ProcessNode *curr = head;
        ProcessNode *tmpPtr;
        int i;
        while(i = 0; i < flags->content_p_size; i++){
            curr->pid = content_p[i]
            curr->next = malloc(sizeof(ProcessNode));
            tmpPtr = curr;
            curr = curr->next;
        }
        free(curr);
        tmpPtr->next = NULL
    } else { // p flag is not present
        //use the process from getProcessesList(uid)
        head = getProcessesList(uid);
        if(head == NULL){
            printf("Current user doesn't own any processes\n");
            exit(1);
        }
        curr = head;
        needFreeList = 1;
    }
    printHeader(flags);
    while(*head != NULL) {
        printf("%d: ",pid); //print out the pid of the process
        if (1 == flags->flag_s || 1 == flags->flag_U || 1 == flags->flag_S) {
            StatInfo *statInfoVar = statParser(pid);
            if (1 == flags->flag_s) {
                printf("%s ", statInfoVar->flag_sField);
            }
		
            if (1 == flags->flag_U) {
                printf("%s ", statInfoVar->flag_sField);
            }
		
            if (1 == flags->flag_S) {
                printf("%s ", statInfoVar->flag_sField);
            }
        }

        if (1 == flags->flag_v) {
            StatmInfo *statmInfoVar = statmParser(pid);
            printf("%s ", statmInfoVar->flag_vField);
        }

        if (1 == flags->flag_c) {
            CmdInfo *cmdInfoVar = cmdlineParser(pid);
            printf("%s ", cmdInfoVar->flag_cField);
        }
	    
        if (1 == flags->flag_m) {
            unsigned char *memContent = readMem(flags->pid, flags->addr_m, flags->length_m)
            if(memContent != NULL){
                printf("%lx: ",flagsVar->addr_m);
                //print the mem content it in a loop
                for(int i = 0; i < flagsVar-> length_m;i++){
                    printf("%02x ", memContent[i]);
                }
                printf("\n");
            }
            else{
                printf("Requested mem range is not mapped\n");
            }

        }
        printf("\n");
	*head = (*head)->next;
    }
    //free the linked list struct is it is allocated in this function
    if(1 == needFreeList){
        ProcessNode *next;
        while(NULL != head->next){
            next = *head->next;
            free(head);
            head = next;
        }
        free(head);
    }
}

