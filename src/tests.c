#include "tests.h"
void printFlagsVar(Flags *flagsVar){
    //print out the flags
    printf("p flag is set to: %d\n", flagsVar->flag_p);
    printf("s flag is set to: %d\n", flagsVar->flag_s);
    printf("U flag is set to: %d\n", flagsVar->flag_U);
    printf("S flag is set to: %d\n", flagsVar->flag_S);
    printf("v flag is set to: %d\n", flagsVar->flag_v);
    printf("c flag is set to: %d\n", flagsVar->flag_c);
    //print out the length of the pid list
    printf("pid list length: %d\n", flagsVar->length_p);
    //loop through the pid list and print out the content
    for(int i=0; i < flagsVar->length_p; i++){
        if(flagsVar->length_p == 1){
            printf("Pid list:{%s}\n",flagsVar->content_p[i]);
        }
        else{
            if(i == 0)
                printf("Pid list:{%s,\n",flagsVar->content_p[i]);
            else if(i != (flagsVar->length_p-1))
                printf("      %s,\n",flagsVar->content_p[i]);
            else
                printf("      %s}\n",flagsVar->content_p[i]);
        }
    }
}

void printStatInfo(StatInfo *statInfo){
    printf("statInfo for process pid: %s\n", statInfo->pid);
    printf("    s - state info about the process: %s\n",statInfo->flag_sField);
    printf("    U - amount of user time consumed by the process: %s\n",statInfo->flag_UField);
    printf("    S - amount of system time consumed by the process: %s\n",statInfo->flag_SField);
}
void printStatmInfo(StatmInfo *statmInfo){
    printf("statmInfo for process pid: %s\n",statmInfo->pid);
    printf("    v - amount of virtual memory currently being used: %s\n",statmInfo->flag_vField);
}
void printCmdlineInfo(CmdInfo *cmdlineInfo){
     printf("cmdlineInfo for process pid: %s\n",cmdlineInfo->pid);
     printf("    c - command line that started the process: %s\n",cmdlineInfo->flag_cField);
}   
void printStatInfoList(StatInfo **statInfoList, int listLength){
    for (int i = 0; i < listLength; i++){
        printStatInfo(statInfoList[i]);
   }
}

void printStatmInfoList(StatmInfo **statmInfoList, int listLength){
    for (int i = 0; i < listLength; i++){
        printStatmInfo(statmInfoList[i]);
   }
}
void printCmdlineInfoList(CmdInfo **cmdlineInfoList, int listLength){ 
    for (int i = 0; i < listLength; i++){
        printCmdlineInfo(cmdlineInfoList[i]);
   }
}
void printCurrUserProcessList(int currUid){
    printf("goes into printCurrUserProcessList()\n");
    printf("uid: %d\n", currUid);
    ProcessNode *processList = getProcessesList(currUid);
    ProcessNode *currNode = processList;
    printf("Processes owned by user: %d\n", currUid);
    while(NULL != currNode){
        printf("    process pid: %s\n",currNode->pid);
        currNode = currNode->next; 
        free(processList);
        processList = currNode;
    }
}
