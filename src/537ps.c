#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processArgs.h"
#include "fileParser.h"
#include "userProcUtil.h"
#include "tests.h"
#include "memReader.h"
#include "outputGenerator.h"
const int debugg = 0;
int main(int argc, char **argv){
    if(!debugg){
        Flags *flagsVar = initFlags();
        //process the arguments
        processArguments(argc,argv,flagsVar);
        int uid = getuid();
        generateOutput(flagsVar, uid);     
    }
    else{
        printf("debug section\n");
        Flags *flagsVar = initFlags();
        //process the arguments
        processArguments(argc,argv,flagsVar);
        if(flagsVar->flag_p ==1){
            StatInfo **statInfoList = calloc(flagsVar->length_p,sizeof(void*));
            StatmInfo **statmInfoList = calloc(flagsVar->length_p,sizeof(void*));
            CmdInfo **cmdlineInfoList = calloc(flagsVar->length_p,sizeof(void*));
            printf("length_p at checkpoint#3333: %d\n",flagsVar->length_p);//DELETE
             
            printFlagsVar(flagsVar);
            for(int i = 0; i< (flagsVar->length_p); i++){        
                const char *pid = (flagsVar->content_p)[i];
                printf("read pid before give to parser: %s\n", pid); 
                statInfoList[i] = statParser(pid);
                printf("length_p at checkpoint#4444: %d\n",flagsVar->length_p);//DELETE
                statmInfoList[i] = statmParser(pid);
                printf("length_p at checkpoint#5555: %d\n",flagsVar->length_p);//DELETE
                cmdlineInfoList[i] = cmdlineParser(pid);
                printf("length_p at checkpoint#6666: %d\n",flagsVar->length_p);//DELETE
                if(flagsVar->flag_m ==1) { 
                    unsigned char *readMemResult = readMem(pid, flagsVar->addr_m, flagsVar->length_m);
                    if(readMemResult != NULL){
                        printf("%lx: ",flagsVar->addr_m);
                        //print the mem content it in a loop
                        for(int i = 0; i < flagsVar-> length_m;i++){
                            printf("%02x ", readMemResult[i]);
                        }
                        printf("\n");
                    }
                    else{
                        printf("Requested mem range is not mapped\n");
                    }
                } 
                printf("length_p at checkpoint#7777: %d\n",flagsVar->length_p);//DELETE
            }
            printStatInfoList(statInfoList, flagsVar->length_p);
            printStatmInfoList(statmInfoList, flagsVar->length_p);
            printCmdlineInfoList(cmdlineInfoList, flagsVar->length_p);
        }
            printFlagsVar(flagsVar);
            int uid = getuid();
            printCurrUserProcessList(uid);
    }
}

