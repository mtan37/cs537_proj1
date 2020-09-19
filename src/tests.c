#include "tests.h"
#include "processArgs.h"
#include "parser.h"
#include <stdio.h>
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
   
void printStatInfoList(StatInfo **statInfoList, int listLength){
    for (int i = 0; i < listLength; i++){
        printStatInfo(statInfoList[i]);
   }
}
